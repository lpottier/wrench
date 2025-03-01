/**
 * Copyright (c) 2017-2021. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 */

#include "wrench/services/compute/cloud/CloudComputeServiceMessage.h"
#include <iostream>
#include <utility>

namespace wrench {

    /**
     * @brief Constructor
     *
     * @param payload: the message size in bytes
     */
    CloudComputeServiceMessage::CloudComputeServiceMessage(sg_size_t payload) : ComputeServiceMessage(payload) {
    }

    /**
     * @brief Constructor
     *
     * @param answer_commport: the commport to which to send the answer
     * @param payload: the message size in bytes
     *
     */
    CloudComputeServiceGetExecutionHostsRequestMessage::CloudComputeServiceGetExecutionHostsRequestMessage(
            S4U_CommPort *answer_commport, sg_size_t payload) : CloudComputeServiceMessage(payload) {
#ifdef WRENCH_INTERNAL_EXCEPTIONS
        if (answer_commport == nullptr) {
            throw std::invalid_argument(
                    "CloudComputeServiceGetExecutionHostsRequestMessage::CloudComputeServiceGetExecutionHostsRequestMessage(): "
                    "Invalid arguments");
        }
#endif
        this->answer_commport = answer_commport;
    }

    /**
     * @brief Constructor
     *
     * @param execution_hosts: the hosts available for running virtual machines
     * @param payload: the message size in bytes
     */
    CloudComputeServiceGetExecutionHostsAnswerMessage::CloudComputeServiceGetExecutionHostsAnswerMessage(
            std::vector<std::string> &execution_hosts, sg_size_t payload) : CloudComputeServiceMessage(payload), execution_hosts(execution_hosts) {}

    /**
     * @brief Constructor
     *
     * @param answer_commport: the commport to which to send the answer
     * @param num_cores: the number of cores the service can use (use ComputeService::ALL_CORES to use all cores
     *                   available on the host)
     * @param ram_memory: the VM's RAM memory_manager_service capacity (use ComputeService::ALL_RAM to use all RAM available on the
     *                    host, this can be lead to an out of memory_manager_service issue)
     * @param physical_host: the physical execution host ("" means "pick a name for me")
     * @param property_list: a property list for the BareMetalComputeService that will run on the VM ({} means "use all defaults")
     * @param messagepayload_list: a message payload list for the BareMetalComputeService that will run on the VM ({} means "use all defaults")
     * @param payload: the message size in bytes
     *
     */
    CloudComputeServiceCreateVMRequestMessage::CloudComputeServiceCreateVMRequestMessage(
            S4U_CommPort *answer_commport,
            unsigned long num_cores,
            sg_size_t ram_memory,
            const std::string &physical_host,
            WRENCH_PROPERTY_COLLECTION_TYPE property_list,
            WRENCH_MESSAGE_PAYLOAD_COLLECTION_TYPE messagepayload_list,
            sg_size_t payload) : CloudComputeServiceMessage(payload) {
#ifdef WRENCH_INTERNAL_EXCEPTIONS
        if ((answer_commport == nullptr) || (ram_memory < 0.0)) {
            //        std::cerr << answer_commport << " - " << pm_hostname << " - " << vm_name << std::endl;
            throw std::invalid_argument(
                    "CloudComputeServiceCreateVMRequestMessage::CloudComputeServiceCreateVMRequestMessage(): Invalid arguments");
        }
#endif
        this->answer_commport = answer_commport;
        this->num_cores = num_cores;
        this->ram_memory = ram_memory;
        this->physical_host = physical_host;
        this->property_list = std::move(property_list);
        this->messagepayload_list = std::move(messagepayload_list);
    }

    /**
     * @brief Constructor
     *
     * @param success: whether the VM creation was successful or not
     * @param vm_name: the name of the created VM (if success)
     * @param failure_cause: the cause of the failure (or nullptr if success)
     * @param payload: the message size in bytes
     */
    CloudComputeServiceCreateVMAnswerMessage::CloudComputeServiceCreateVMAnswerMessage(bool success,
                                                                                       std::string &vm_name,
                                                                                       std::shared_ptr<FailureCause> failure_cause,
                                                                                       sg_size_t payload) : CloudComputeServiceMessage(payload), success(success), vm_name(vm_name),
                                                                                                         failure_cause(std::move(failure_cause)) {}

    /**
     * @brief Constructor
     *
     * @param answer_commport: the commport to which to send the answer
     * @param vm_name: the name of the VM host
     * @param send_failure_notifications: whether to send job failure notifications
     * @param termination_cause: termination cause (for failure notifications)
     * @param payload: the message size in bytes
     *
     */
    CloudComputeServiceShutdownVMRequestMessage::CloudComputeServiceShutdownVMRequestMessage(
            S4U_CommPort *answer_commport,
            const std::string &vm_name,
            bool send_failure_notifications,
            ComputeService::TerminationCause termination_cause,
            sg_size_t payload) : CloudComputeServiceMessage(payload) {
#ifdef WRENCH_INTERNAL_EXCEPTIONS
        if ((answer_commport == nullptr) || vm_name.empty()) {
            throw std::invalid_argument(
                    "CloudComputeServiceShutdownVMRequestMessage::CloudComputeServiceShutdownVMRequestMessage(): Invalid arguments");
        }
#endif
        this->answer_commport = answer_commport;
        this->vm_name = vm_name;
        this->send_failure_notifications = send_failure_notifications;
        this->termination_cause = termination_cause;
    }

    /**
     * @brief Constructor
     *
     * @param success: whether the VM shutdown succeeded
     * @param failure_cause: the cause of the failure (or nullptr if success)
     * @param payload: the message size in bytes
     */
    CloudComputeServiceShutdownVMAnswerMessage::CloudComputeServiceShutdownVMAnswerMessage(bool success,
                                                                                           std::shared_ptr<FailureCause> failure_cause,
                                                                                           sg_size_t payload) : CloudComputeServiceMessage(payload), success(success), failure_cause(std::move(failure_cause)) {}

    /**
     * @brief Constructor
     *
     * @param answer_commport: the commport to which to send the answer
     * @param vm_name: the name of the VM host
     * @param payload: the message size in bytes
     *
     */
    CloudComputeServiceStartVMRequestMessage::CloudComputeServiceStartVMRequestMessage(
            S4U_CommPort *answer_commport,
            const std::string &vm_name,
            sg_size_t payload) : CloudComputeServiceMessage(payload) {
#ifdef WRENCH_INTERNAL_EXCEPTIONS
        if ((answer_commport == nullptr) || vm_name.empty()) {
            throw std::invalid_argument(
                    "CloudComputeServiceStartVMRequestMessage::CloudComputeServiceStartVMRequestMessage(): Invalid arguments");
        }
#endif
        this->answer_commport = answer_commport;
        this->vm_name = vm_name;
    }

    /**
     * @brief Constructor
     *
     * @param success: whether the VM start succeeded
     * @param cs: the BareMetalComputeService exposed by the started VM (or nullptr if not success)
     * @param failure_cause: the cause of the failure (or nullptr if success)
     * @param payload: the message size in bytes
     */
    CloudComputeServiceStartVMAnswerMessage::CloudComputeServiceStartVMAnswerMessage(bool success,
                                                                                     std::shared_ptr<BareMetalComputeService> cs,
                                                                                     std::shared_ptr<FailureCause> failure_cause,
                                                                                     sg_size_t payload) : CloudComputeServiceMessage(payload), success(success), cs(std::move(cs)),
                                                                                                       failure_cause(std::move(failure_cause)) {}

    /**
     * @brief Constructor
     *
     * @param answer_commport: the commport to which to send the answer
     * @param vm_name: the name of the VM host
     * @param payload: the message size in bytes
     *
     */
    CloudComputeServiceSuspendVMRequestMessage::CloudComputeServiceSuspendVMRequestMessage(
            S4U_CommPort *answer_commport,
            const std::string &vm_name,
            sg_size_t payload) : CloudComputeServiceMessage(payload) {
#ifdef WRENCH_INTERNAL_EXCEPTIONS
        if ((answer_commport == nullptr) || vm_name.empty()) {
            throw std::invalid_argument(
                    "CloudComputeServiceSuspendVMRequestMessage::CloudComputeServiceSuspendVMRequestMessage(): Invalid arguments");
        }
#endif
        this->answer_commport = answer_commport;
        this->vm_name = vm_name;
    }

    /**
     * @brief Constructor
     *
     * @param success: whether the VM suspend succeeded
     * @param failure_cause: a failure cause (or nullptr if success)
     * @param payload: the message size in bytes
     */
    CloudComputeServiceSuspendVMAnswerMessage::CloudComputeServiceSuspendVMAnswerMessage(bool success,
                                                                                         std::shared_ptr<FailureCause> failure_cause,
                                                                                         sg_size_t payload) : CloudComputeServiceMessage(payload), success(success), failure_cause(std::move(failure_cause)) {}

    /**
     * @brief Constructor
     *
     * @param answer_commport: the commport to which to send the answer
     * @param vm_name: the name of the VM host
     * @param payload: the message size in bytes
     *
     */
    CloudComputeServiceResumeVMRequestMessage::CloudComputeServiceResumeVMRequestMessage(
            S4U_CommPort *answer_commport,
            const std::string &vm_name,
            sg_size_t payload) : CloudComputeServiceMessage(payload) {
#ifdef WRENCH_INTERNAL_EXCEPTIONS
        if ((answer_commport == nullptr) || vm_name.empty()) {
            throw std::invalid_argument(
                    "CloudComputeServiceResumeVMRequestMessage::CloudComputeServiceResumeVMRequestMessage(): Invalid arguments");
        }
#endif
        this->answer_commport = answer_commport;
        this->vm_name = vm_name;
    }

    /**
     * @brief Constructor
     *
     * @param success: whether the VM resume succeeded
     * @param failure_cause: a failure cause (or nullptr if success)
     * @param payload: the message size in bytes
     */
    CloudComputeServiceResumeVMAnswerMessage::CloudComputeServiceResumeVMAnswerMessage(bool success,
                                                                                       std::shared_ptr<FailureCause> failure_cause,
                                                                                       sg_size_t payload) : CloudComputeServiceMessage(payload), success(success), failure_cause(std::move(failure_cause)) {}


    /**
     * @brief Constructor
     *
     * @param answer_commport: the commport to which to send the answer
     * @param vm_name: the name of the VM host
     * @param payload: the message size in bytes
     *
     */
    CloudComputeServiceDestroyVMRequestMessage::CloudComputeServiceDestroyVMRequestMessage(
            S4U_CommPort *answer_commport,
            const std::string &vm_name,
            sg_size_t payload) : CloudComputeServiceMessage(payload) {
#ifdef WRENCH_INTERNAL_EXCEPTIONS
        if ((answer_commport == nullptr) || vm_name.empty()) {
            throw std::invalid_argument(
                    "CloudComputeServiceDestroyVMRequestMessage::CloudComputeServiceDestroyVMRequestMessage(): Invalid arguments");
        }
#endif
        this->answer_commport = answer_commport;
        this->vm_name = vm_name;
    }

    /**
     * @brief Constructor
     *
     * @param success: whether the VM was destroyed successfully
     * @param failure_cause: a failure cause (or nullptr if success)
     * @param payload: the message size in bytes
     */
    CloudComputeServiceDestroyVMAnswerMessage::CloudComputeServiceDestroyVMAnswerMessage(bool success,
                                                                                         std::shared_ptr<FailureCause> failure_cause,
                                                                                         sg_size_t payload) : CloudComputeServiceMessage(payload), success(success), failure_cause(std::move(failure_cause)) {}


}// namespace wrench
