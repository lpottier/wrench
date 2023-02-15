/**
 * Copyright (c) 2017-2021. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <utility>
#include <wrench/failure_causes/InvalidDirectoryPath.h>
#include <wrench/failure_causes/FileNotFound.h>
#include <wrench/failure_causes/StorageServiceNotEnoughSpace.h>

#include <wrench/services/storage/simple/SimpleStorageServiceNonBufferized.h>
#include <wrench/services/ServiceMessage.h>
#include "wrench/services/storage/StorageServiceMessage.h"
#include <wrench/simgrid_S4U_util/S4U_Mailbox.h>
#include <wrench/logging/TerminalOutput.h>
#include <wrench/simgrid_S4U_util/S4U_Simulation.h>
#include <wrench/data_file/DataFile.h>
#include <wrench/exceptions/ExecutionException.h>
#include <wrench/simulation/SimulationTimestampTypes.h>
#include <wrench/services/storage/storage_helpers/FileLocation.h>
#include <wrench/services/memory/MemoryManager.h>

WRENCH_LOG_CATEGORY(wrench_core_simple_storage_service_non_bufferized,
                    "Log category for Simple Storage Service Non Bufferized");

namespace wrench {

    /**
     * @brief Cleanup method
     *
     * @param has_returned_from_main: whether main() returned
     * @param return_value: the return value (if main() returned)
     */
    void SimpleStorageServiceNonBufferized::cleanup(bool has_returned_from_main, int return_value) {
    }

    /**
     * @brief Public constructor
     *
     * @param hostname: the name of the host on which to start the service
     * @param mount_points: the set of mount points
     * @param property_list: a property list ({} means "use all defaults")
     * @param messagepayload_list: a message payload list ({} means "use all defaults")
     */
    SimpleStorageServiceNonBufferized::SimpleStorageServiceNonBufferized(const std::string &hostname,
                                                                         std::set<std::string> mount_points,
                                                                         WRENCH_PROPERTY_COLLECTION_TYPE property_list,
                                                                         WRENCH_MESSAGE_PAYLOADCOLLECTION_TYPE messagepayload_list) : SimpleStorageService(hostname, std::move(mount_points), std::move(property_list), std::move(messagepayload_list),
                                                                                                                                                           "_" + std::to_string(SimpleStorageService::getNewUniqueNumber())) {

        this->buffer_size = 0;
    }

    /**
     * @brief Process a transaction completion
     * @param transaction: the transaction
     */
    void SimpleStorageServiceNonBufferized::processTransactionCompletion(const std::shared_ptr<Transaction> &transaction) {

        if (transaction->src_location) {
            transaction->src_location->getStorageService()->file_systems[transaction->src_location->getMountPoint()]->decrementNumRunningTransactionsForFileInDirectory(
                    transaction->src_location->getFile(), transaction->src_location->getAbsolutePathAtMountPoint());
        }

        // If I was the source and the destination was bufferized, I am the one creating the file there! (yes,
        // this is ugly and lame, and one day we'll clean the storage service implementation
        if (transaction->src_location != nullptr and
            transaction->src_location->getStorageService() == shared_from_this() and
            transaction->dst_location != nullptr and
            transaction->dst_location->getStorageService()->isBufferized()) {
            transaction->dst_location->getStorageService()->file_systems[transaction->dst_location->getMountPoint()]->storeFileInDirectory(transaction->dst_location->getFile(), transaction->dst_location->getAbsolutePathAtMountPoint(), true);
        }

        // Send back the relevant ack if this was a read
        if (transaction->dst_location == nullptr) {
            //            WRENCH_INFO("Sending back an ack for a successful file read");
            S4U_Mailbox::dputMessage(transaction->mailbox, new StorageServiceAckMessage(transaction->src_location));
        } else if (transaction->src_location == nullptr) {
            WRENCH_INFO("File %s stored", transaction->dst_location->getFile()->getID().c_str());
            this->file_systems[transaction->dst_location->getMountPoint()]->storeFileInDirectory(
                    transaction->dst_location->getFile(), transaction->dst_location->getAbsolutePathAtMountPoint(), true);
            // Deal with time stamps, previously we could test whether a real timestamp was passed, now this.
            // Maybe no corresponding timestamp.
            //            WRENCH_INFO("Sending back an ack for a successful file read");
            S4U_Mailbox::dputMessage(transaction->mailbox, new StorageServiceAckMessage(transaction->dst_location));
        } else {
            if (transaction->dst_location->getStorageService() == shared_from_this()) {
                WRENCH_INFO("File %s stored", transaction->dst_location->getFile()->getID().c_str());
                this->file_systems[transaction->dst_location->getMountPoint()]->storeFileInDirectory(
                        transaction->dst_location->getFile(), transaction->dst_location->getAbsolutePathAtMountPoint(), true);
                try {
                    this->simulation->getOutput().addTimestampFileCopyCompletion(
                            Simulation::getCurrentSimulatedDate(), transaction->dst_location->getFile(), transaction->src_location, transaction->dst_location);
                } catch (invalid_argument &ignore) {
                }
            }

            //            WRENCH_INFO("Sending back an ack for a file copy");
            S4U_Mailbox::dputMessage(
                    transaction->mailbox,
                    new StorageServiceFileCopyAnswerMessage(
                            transaction->src_location,
                            transaction->dst_location,
                            nullptr,
                            false,
                            true,
                            nullptr,
                            this->getMessagePayloadValue(
                                    SimpleStorageServiceMessagePayload::FILE_COPY_ANSWER_MESSAGE_PAYLOAD)));
        }
    }

    /**
     * @brief Process a transaction failure
     * @param transaction: the transaction
     */
    void SimpleStorageServiceNonBufferized::processTransactionFailure(const std::shared_ptr<Transaction> &transaction) {
        throw std::runtime_error("SimpleStorageServiceNonBufferized::processTransactionFailure(): not implemented");
    }


    /**
     * @brief Main method of the daemon
     *
     * @return 0 on termination
     */
    int SimpleStorageServiceNonBufferized::main() {
        TerminalOutput::setThisProcessLoggingColor(TerminalOutput::COLOR_CYAN);
        std::string message = "Simple Storage Service (Non-Bufferized) " + this->getName() + "  starting on host " + this->getHostname();
        WRENCH_INFO("%s", message.c_str());

        for (auto const &mp: this->file_systems) {
            if (not mp.second->isInitialized()) {
                mp.second->init();
            }
        }

        // In case this was a restart!
        this->stream_to_transactions.clear();
        this->pending_transactions.clear();
        this->running_transactions.clear();

        for (auto const &fs: this->file_systems) {
            message = "  - mount point " + fs.first + ": " +
                      std::to_string(fs.second->getFreeSpace()) + "/" +
                      std::to_string(fs.second->getTotalCapacity()) + " Bytes";
            WRENCH_INFO("%s", message.c_str());
        }

        //        WRENCH_INFO("STREAMS PENDING: %zu", this->pending_transactions.size());
        //        WRENCH_INFO("STREAMS RUNNING: %zu", this->pending_transactions.size());

        // If writeback device simulation is activated
        if (Simulation::isPageCachingEnabled()) {
            //  Find the "memory" disk (we know there is one)
            auto host = S4U_Simulation::get_host_or_vm_by_name(this->getHostname());
            simgrid::s4u::Disk *memory_disk = nullptr;
            for (auto const &d: host->get_disks()) {
                // Get the disk's mount point
                const char *p = d->get_property("mount");
                if (!p) {
                    continue;
                }
                if (!strcmp(p, "/memory")) {
                    memory_disk = d;
                    break;
                }
            }

            // Start periodical flushing via a memory manager
            this->memory_manager = MemoryManager::initAndStart(this->simulation, memory_disk, 0.4, 5, 30, this->hostname);
        }

        /** Main loop **/
        bool comm_ptr_has_been_posted = false;
        simgrid::s4u::CommPtr comm_ptr;
        std::unique_ptr<SimulationMessage> simulation_message;
        while (true) {

            S4U_Simulation::computeZeroFlop();

            this->startPendingTransactions();

            // Create an async recv if needed
            if (not comm_ptr_has_been_posted) {
                try {
                    comm_ptr = this->mailbox->get_async<void>((void **) (&(simulation_message)));
                } catch (simgrid::NetworkFailureException &e) {
                    // oh well
                    continue;
                }
                comm_ptr_has_been_posted = true;
            }

            // Create all activities to wait on
            std::vector<simgrid::s4u::ActivityPtr> pending_activities;
            pending_activities.emplace_back(comm_ptr);
            for (auto const &transaction: this->running_transactions) {
                pending_activities.emplace_back(transaction->stream);
            }

            // Wait one activity to complete
            int finished_activity_index;
            try {
                finished_activity_index = (int) simgrid::s4u::Activity::wait_any(pending_activities);
            } catch (simgrid::NetworkFailureException &e) {
                // the comm failed
                comm_ptr_has_been_posted = false;
                continue;// oh well
            } catch (simgrid::Exception &e) {
                // This likely doesn't happen, but let's keep it here for now
                for (int i = 1; i < (int) pending_activities.size(); i++) {
                    if (pending_activities.at(i)->get_state() == simgrid::s4u::Activity::State::FAILED) {
                        auto finished_transaction = this->running_transactions[i - 1];
                        this->stream_to_transactions.erase(finished_transaction->stream);
                        processTransactionFailure(finished_transaction);
                        continue;
                    }
                }
                continue;
            } catch (std::exception &e) {
                continue;
            }

            // It's a communication
            if (finished_activity_index == 0) {
                comm_ptr_has_been_posted = false;
                if (not processNextMessage(simulation_message.get())) break;
            } else if (finished_activity_index > 0) {
                auto finished_transaction = this->running_transactions.at(finished_activity_index - 1);
                this->running_transactions.erase(this->running_transactions.begin() + finished_activity_index - 1);
                this->stream_to_transactions.erase(finished_transaction->stream);
                processTransactionCompletion(finished_transaction);
            } else if (finished_activity_index == -1) {
                throw std::runtime_error("wait_any() returned -1. Not sure what to do with this. ");
            }
        }

        WRENCH_INFO("Simple Storage Service (Non-Bufferized) %s on host %s cleanly terminating!",
                    this->getName().c_str(),
                    S4U_Simulation::getHostName().c_str());

        return 0;
    }

    /**
     * @brief Process a received control message
     *
     * @return false if the daemon should terminate
     */
    bool SimpleStorageServiceNonBufferized::processNextMessage(SimulationMessage *message) {

        WRENCH_INFO("Got a [%s] message", message->getName().c_str());

        if (auto msg = dynamic_cast<ServiceStopDaemonMessage *>(message)) {
            return processStopDaemonRequest(msg->ack_mailbox);

        } else if (auto msg = dynamic_cast<StorageServiceFreeSpaceRequestMessage *>(message)) {
            return processFreeSpaceRequest(msg->answer_mailbox);

        } else if (auto msg = dynamic_cast<StorageServiceFileDeleteRequestMessage *>(message)) {
            return processFileDeleteRequest(msg->location, msg->answer_mailbox);

        } else if (auto msg = dynamic_cast<StorageServiceFileLookupRequestMessage *>(message)) {
            return processFileLookupRequest(msg->location, msg->answer_mailbox);

        } else if (auto msg = dynamic_cast<StorageServiceFileWriteRequestMessage *>(message)) {
            return processFileWriteRequest(msg->location, msg->answer_mailbox,
                                           msg->requesting_host, msg->buffer_size);

        } else if (auto msg = dynamic_cast<StorageServiceFileReadRequestMessage *>(message)) {
            return processFileReadRequest(msg->location,
                                          msg->num_bytes_to_read, msg->answer_mailbox, msg->requesting_host);

        } else if (auto msg = dynamic_cast<StorageServiceFileCopyRequestMessage *>(message)) {
            if (msg->src->getStorageService() != this->getSharedPtr<StorageService>()) {
                return processFileCopyRequestIAmNotTheSource(msg->src, msg->dst, msg->answer_mailbox);
            } else {
                return processFileCopyRequestIAmTheSource(msg->src, msg->dst, msg->answer_mailbox);
            }

        } else {
            throw std::runtime_error(
                    "SimpleStorageServiceNonBufferized::processNextMessage(): Unexpected [" + message->getName() + "] message");
        }
    }

    /**
     * @brief Handle a file write request
     *
     * @param location: the location to write the file to
     * @param answer_mailbox: the mailbox to which the reply should be sent
     * @param requesting_host: the requesting host
     * @param buffer_size: the buffer size to use
     * @return true if this process should keep running
     */
    bool SimpleStorageServiceNonBufferized::processFileWriteRequest(const std::shared_ptr<FileLocation> &location,
                                                                    simgrid::s4u::Mailbox *answer_mailbox, simgrid::s4u::Host *requesting_host,
                                                                    double buffer_size) {

        if (buffer_size >= 1.0) {
            throw std::runtime_error("SimpleStorageServiceNonBufferized::processFileWriteRequest(): Cannot process a write requests with a non-zero buffer size");
        }

        // Figure out whether this succeeds or not
        std::shared_ptr<FailureCause> failure_cause = nullptr;

        auto fs = this->file_systems[location->getMountPoint()].get();
        auto file = location->getFile();

        // If the file is not already there, do a capacity check/update
        // (If the file is already there, then there will just be an overwrite. Note that
        // if the overwrite fails, then the file will disappear, which is expected)

        bool file_already_there = fs->doesDirectoryExist(location->getAbsolutePathAtMountPoint()) and fs->isFileInDirectory(file, location->getAbsolutePathAtMountPoint());
        if ((not file_already_there) and (not fs->reserveSpace(file, location->getAbsolutePathAtMountPoint()))) {
            try {
                S4U_Mailbox::dputMessage(
                        answer_mailbox,
                        new StorageServiceFileWriteAnswerMessage(
                                location,
                                false,
                                std::shared_ptr<FailureCause>(
                                        new StorageServiceNotEnoughSpace(
                                                file,
                                                this->getSharedPtr<SimpleStorageService>())),
                                nullptr,
                                this->getMessagePayloadValue(
                                        SimpleStorageServiceMessagePayload::FILE_WRITE_ANSWER_MESSAGE_PAYLOAD)));
            } catch (wrench::ExecutionException &e) {
                return true;
            }
            return true;
        }

        // At this point we're good
        if (not fs->doesDirectoryExist(location->getAbsolutePathAtMountPoint())) {
            fs->createDirectory(location->getAbsolutePathAtMountPoint());
        }

        // Reply with a "go ahead, send me the file" message
        S4U_Mailbox::dputMessage(
                answer_mailbox,
                new StorageServiceFileWriteAnswerMessage(
                        location,
                        true,
                        nullptr,
                        nullptr,
                        this->getMessagePayloadValue(
                                SimpleStorageServiceMessagePayload::FILE_WRITE_ANSWER_MESSAGE_PAYLOAD)));

        // Create the streaming activity
        auto me_host = simgrid::s4u::this_actor::get_host();
        simgrid::s4u::Disk *me_disk = fs->getDisk();

        // Create a Transaction
        auto transaction = std::make_shared<Transaction>(
                nullptr,
                requesting_host,
                nullptr,
                location,
                me_host,
                me_disk,
                answer_mailbox,
                file->getSize());

        // Add it to the Pool of pending data communications
        this->pending_transactions.push_back(transaction);


        return true;
    }

    /**
     * @brief Handle a file read request
     * @param location: the file's location
     * @param num_bytes_to_read: the number of bytes to read
     * @param answer_mailbox: the mailbox to which the answer should be sent
     * @param requesting_host: the requesting_host
     * @return
     */
    bool SimpleStorageServiceNonBufferized::processFileReadRequest(
            const std::shared_ptr<FileLocation> &location,
            double num_bytes_to_read,
            simgrid::s4u::Mailbox *answer_mailbox,
            simgrid::s4u::Host *requesting_host) {

        // Figure out whether this succeeds or not
        std::shared_ptr<FailureCause> failure_cause = nullptr;

        LogicalFileSystem *fs = nullptr;
        auto file = location->getFile();

        //        if ((this->file_systems.find(location->getMountPoint()) == this->file_systems.end()) or
        if (not this->file_systems[location->getMountPoint()]->doesDirectoryExist(
                    location->getAbsolutePathAtMountPoint())) {
            failure_cause = std::shared_ptr<FailureCause>(
                    new InvalidDirectoryPath(
                            this->getSharedPtr<SimpleStorageService>(),
                            location->getMountPoint() + "/" +
                                    location->getAbsolutePathAtMountPoint()));
        } else {
            fs = this->file_systems[location->getMountPoint()].get();

            if (not fs->isFileInDirectory(file, location->getAbsolutePathAtMountPoint())) {
                WRENCH_INFO(
                        "Received a read request for a file I don't have (%s)", location->toString().c_str());
                failure_cause = std::shared_ptr<FailureCause>(new FileNotFound(location));
            }
        }

        bool success = (failure_cause == nullptr);

        // If a success, create the chunk_receiving mailbox

        // Send back the corresponding ack, asynchronously and in a "fire and forget" fashion
        S4U_Mailbox::dputMessage(
                answer_mailbox,
                new StorageServiceFileReadAnswerMessage(
                        location,
                        success,
                        failure_cause,
                        nullptr,// non-bufferized = no chunk-receiving mailbox
                        buffer_size,
                        this->getMessagePayloadValue(
                                SimpleStorageServiceMessagePayload::FILE_READ_ANSWER_MESSAGE_PAYLOAD)));

        // If success, then follow up with sending the file (ASYNCHRONOUSLY!)
        if (success) {
            // Make the file un-evictable
            location->getStorageService()->file_systems[location->getMountPoint()]->incrementNumRunningTransactionsForFileInDirectory(
                    location->getFile(), location->getAbsolutePathAtMountPoint());

            fs->updateReadDate(location->getFile(), location->getAbsolutePathAtMountPoint());

            // Create the streaming activity
            auto me_host = simgrid::s4u::this_actor::get_host();
            simgrid::s4u::Disk *me_disk = fs->getDisk();

            // Create a Transaction
            auto transaction = std::make_shared<Transaction>(
                    location,
                    me_host,
                    me_disk,
                    nullptr,
                    requesting_host,
                    nullptr,
                    answer_mailbox,
                    num_bytes_to_read);

            // Add it to the Pool of pending data communications
            //            this->transactions[sg_iostream] = transaction;
            this->pending_transactions.push_back(transaction);
        }

        return true;
    }

    /**
     * @brief Handle a file copy request
     * @param src_location: the source location
     * @param dst_location: the destination location
     * @param answer_mailbox: the mailbox to which the answer should be sent
     * @return
     */
    bool SimpleStorageServiceNonBufferized::processFileCopyRequestIAmNotTheSource(
            const std::shared_ptr<FileLocation> &src_location,
            const std::shared_ptr<FileLocation> &dst_location,
            simgrid::s4u::Mailbox *answer_mailbox) {

        WRENCH_INFO("FileCopyRequest: %s -> %s",
                    src_location->toString().c_str(),
                    dst_location->toString().c_str());

        auto src_host = simgrid::s4u::Host::by_name(src_location->getStorageService()->getHostname());
        auto dst_host = simgrid::s4u::Host::by_name(dst_location->getStorageService()->getHostname());
        // TODO: This disk identification is really ugly and likely slow
        simgrid::s4u::Disk *src_disk = nullptr;
        auto src_location_sanitized_mount_point = FileLocation::sanitizePath(src_location->getMountPoint() + "/");
        for (auto const &d: src_host->get_disks()) {
            if (src_location_sanitized_mount_point == FileLocation::sanitizePath(std::string(d->get_property("mount")) + "/")) {
                src_disk = d;
            }
        }
        if (src_disk == nullptr) {
            throw std::runtime_error("SimpleStorageServiceNonBufferized::processFileCopyRequestIAmNotTheSource(): source disk not found - internal error");
        }
        simgrid::s4u::Disk *dst_disk = nullptr;
        auto dst_location_sanitized_mount_point = FileLocation::sanitizePath(dst_location->getMountPoint() + "/");
        for (auto const &d: dst_host->get_disks()) {
            if (dst_location_sanitized_mount_point == FileLocation::sanitizePath(std::string(d->get_property("mount")) + "/")) {
                dst_disk = d;
            }
        }
        if (dst_disk == nullptr) {
            throw std::runtime_error("SimpleStorageServiceNonBufferized::processFileCopyRequestIAmNotTheSource(): destination disk not found - internal error");
        }

        auto file = src_location->getFile();

        bool src_has_the_file;
        bool src_could_be_contacted = true;
        std::shared_ptr<FailureCause> src_could_not_be_contacted_failure_cause;


        try {
            src_has_the_file = src_location->getStorageService()->lookupFile(src_location);
        } catch (wrench::ExecutionException &e) {
            src_could_be_contacted = false;
            src_could_not_be_contacted_failure_cause = e.getCause();
        }

        // If the src could not be contacted, send back an error
        if (not src_could_be_contacted) {
            try {
                S4U_Mailbox::putMessage(
                        answer_mailbox,
                        new StorageServiceFileCopyAnswerMessage(
                                src_location,
                                dst_location,
                                nullptr, false,
                                false,
                                src_could_not_be_contacted_failure_cause,
                                this->getMessagePayloadValue(
                                        SimpleStorageServiceMessagePayload::FILE_COPY_ANSWER_MESSAGE_PAYLOAD)));

            } catch (ExecutionException &e) {
                return true;
            }
            return true;
        }

        // If the src doesn't have the file, return an error
        if (not src_has_the_file) {
            try {
                S4U_Mailbox::putMessage(
                        answer_mailbox,
                        new StorageServiceFileCopyAnswerMessage(
                                src_location,
                                dst_location,
                                nullptr, false,
                                false,
                                std::shared_ptr<FailureCause>(
                                        new FileNotFound(
                                                src_location)),
                                this->getMessagePayloadValue(
                                        SimpleStorageServiceMessagePayload::FILE_COPY_ANSWER_MESSAGE_PAYLOAD)));

            } catch (ExecutionException &e) {
                return true;
            }
            return true;
        }

        auto fs = this->file_systems[dst_location->getMountPoint()].get();

        // If file is not already here, reserve space for it
        bool file_is_already_here = fs->isFileInDirectory(dst_location->getFile(), dst_location->getAbsolutePathAtMountPoint());
        if ((not file_is_already_here) and (not fs->reserveSpace(dst_location->getFile(), dst_location->getAbsolutePathAtMountPoint()))) {
            this->simulation->getOutput().addTimestampFileCopyFailure(Simulation::getCurrentSimulatedDate(), file, src_location, dst_location);
            try {
                S4U_Mailbox::putMessage(
                        answer_mailbox,
                        new StorageServiceFileCopyAnswerMessage(
                                src_location,
                                dst_location,
                                nullptr, false,
                                false,
                                std::shared_ptr<FailureCause>(
                                        new StorageServiceNotEnoughSpace(
                                                file,
                                                this->getSharedPtr<SimpleStorageService>())),
                                this->getMessagePayloadValue(
                                        SimpleStorageServiceMessagePayload::FILE_COPY_ANSWER_MESSAGE_PAYLOAD)));
            } catch (ExecutionException &e) {
                return true;
            }
            return true;
        }

        src_location->getStorageService()->file_systems[src_location->getMountPoint()]->incrementNumRunningTransactionsForFileInDirectory(
                src_location->getFile(), src_location->getAbsolutePathAtMountPoint());

        // At this point, there is enough space
        // Create a Transaction
        auto transaction = std::make_shared<Transaction>(
                src_location,
                src_host,
                src_disk,
                dst_location,
                dst_host,
                dst_disk,
                answer_mailbox,
                file->getSize());

        this->pending_transactions.push_back(transaction);

        return true;
    }


    /**
     * @brief Handle a file copy request
     * @param src_location: the source location
     * @param dst_location: the destination location
     * @param answer_mailbox: the mailbox to which the answer should be sent
     * @return
     */
    bool SimpleStorageServiceNonBufferized::processFileCopyRequestIAmTheSource(
            const std::shared_ptr<FileLocation> &src_location,
            const std::shared_ptr<FileLocation> &dst_location,
            simgrid::s4u::Mailbox *answer_mailbox) {

        WRENCH_INFO("FileCopyRequest: %s -> %s",
                    src_location->toString().c_str(),
                    dst_location->toString().c_str());

        // TODO: This code is duplicated with the IAmNotTheSource version of this method
        auto src_host = simgrid::s4u::Host::by_name(src_location->getStorageService()->getHostname());
        auto dst_host = simgrid::s4u::Host::by_name(dst_location->getStorageService()->getHostname());
        // TODO: This disk identification is really ugly and likely slow
        simgrid::s4u::Disk *src_disk = nullptr;
        auto src_location_sanitized_mount_point = FileLocation::sanitizePath(src_location->getMountPoint() + "/");
        for (auto const &d: src_host->get_disks()) {
            if (src_location_sanitized_mount_point == FileLocation::sanitizePath(std::string(d->get_property("mount")) + "/")) {
                src_disk = d;
            }
        }
        if (src_disk == nullptr) {
            throw std::runtime_error("SimpleStorageServiceNonBufferized::processFileCopyRequestIAmTheSource(): source disk not found - internal error");
        }
        simgrid::s4u::Disk *dst_disk = nullptr;
        auto dst_location_sanitized_mount_point = FileLocation::sanitizePath(dst_location->getMountPoint() + "/");
        for (auto const &d: dst_host->get_disks()) {
            if (dst_location_sanitized_mount_point == FileLocation::sanitizePath(std::string(d->get_property("mount")) + "/")) {
                dst_disk = d;
            }
        }
        if (dst_disk == nullptr) {
            throw std::runtime_error("SimpleStorageServiceNonBufferized::processFileCopyRequestIAmTheSource(): destination disk not found - internal error");
        }

        auto file = src_location->getFile();

        auto my_fs = this->file_systems[src_location->getMountPoint()].get();

        // Do I have the file
        if (not my_fs->isFileInDirectory(src_location->getFile(), src_location->getAbsolutePathAtMountPoint())) {
            try {
                S4U_Mailbox::putMessage(
                        answer_mailbox,
                        new StorageServiceFileCopyAnswerMessage(
                                src_location,
                                dst_location,
                                nullptr, false,
                                false,
                                std::shared_ptr<FailureCause>(
                                        new FileNotFound(
                                                src_location)),
                                this->getMessagePayloadValue(
                                        SimpleStorageServiceMessagePayload::FILE_COPY_ANSWER_MESSAGE_PAYLOAD)));

            } catch (ExecutionException &e) {
                return true;
            }
            return true;
        }

        // At this point, I have the file

        // Can file fit at the destination?
        auto dst_file_system = dst_location->getStorageService()->file_systems[dst_location->getMountPoint()].get();
        bool file_already_at_destination = dst_file_system->isFileInDirectory(dst_location->getFile(), dst_location->getAbsolutePathAtMountPoint());

        // If not already at destination make space for it, and if not possible, then return an error
        if (not file_already_at_destination) {
            if (not dst_file_system->reserveSpace(dst_location->getFile(), dst_location->getAbsolutePathAtMountPoint())) {
                try {
                    S4U_Mailbox::putMessage(
                            answer_mailbox,
                            new StorageServiceFileCopyAnswerMessage(
                                    src_location,
                                    dst_location,
                                    nullptr, false,
                                    false,
                                    std::shared_ptr<FailureCause>(
                                            new StorageServiceNotEnoughSpace(dst_location->getFile(),
                                                                             dst_location->getStorageService())),
                                    this->getMessagePayloadValue(
                                            SimpleStorageServiceMessagePayload::FILE_COPY_ANSWER_MESSAGE_PAYLOAD)));

                } catch (ExecutionException &e) {
                    return true;
                }
                return true;
            }
        }

        // At this point we're all good
        uint64_t transfer_size;
        transfer_size = (uint64_t) (file->getSize());

        src_location->getStorageService()->file_systems[src_location->getMountPoint()]->incrementNumRunningTransactionsForFileInDirectory(
                src_location->getFile(), src_location->getAbsolutePathAtMountPoint());

        // Create a Transaction
        auto transaction = std::make_shared<Transaction>(
                src_location,
                src_host,
                src_disk,
                dst_location,
                dst_host,
                dst_disk,
                answer_mailbox,
                transfer_size);

        // Add it to the Pool of pending data communications
        this->pending_transactions.push_back(transaction);

        return true;
    }

    /**
* @brief Start pending file transfer threads if any and if possible
*/
    void SimpleStorageServiceNonBufferized::startPendingTransactions() {
        while ((not this->pending_transactions.empty()) and
               (this->running_transactions.size() < this->num_concurrent_connections)) {
            //            WRENCH_INFO("Starting pending transaction for file %s",
            //                        this->transactions[this->pending_sg_iostreams.at(0)]->file->getID().c_str());

            auto transaction = this->pending_transactions.front();
            this->pending_transactions.pop_front();

            auto sg_iostream = simgrid::s4u::Io::streamto_init(transaction->src_host,
                                                               transaction->src_disk,
                                                               transaction->dst_host,
                                                               transaction->dst_disk)
                                       ->set_size((uint64_t) (transaction->transfer_size));

            transaction->stream = sg_iostream;

            this->stream_to_transactions[sg_iostream] = transaction;
            this->running_transactions.push_back(transaction);
            sg_iostream->vetoable_start();
        }
    }

    /**
* @brief Get the load (number of concurrent reads) on the storage service
* @return the load on the service
*/
    double SimpleStorageServiceNonBufferized::getLoad() {
        return (double) this->running_transactions.size() + (double) this->pending_transactions.size();
    }


}// namespace wrench