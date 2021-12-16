/**
 * Copyright (c) 2017. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <gtest/gtest.h>

#include <wrench-dev.h>

#include <nlohmann/json.hpp>

#include "../../include/TestWithFork.h"
#include "../../include/UniqueTmpPathPrefix.h"

#include <fstream>

#include <algorithm>

WRENCH_LOG_CATEGORY(bandwidth_meter_service_test, "Log category for BandwidthMeterServiceTest");


/**********************************************************************/
/**                    BandwidthMeterServiceTest                     **/
/**********************************************************************/

class BandwidthMeterServiceTest : public ::testing::Test {

public:
    std::shared_ptr<wrench::StorageService> client_storage_service;
    std::shared_ptr<wrench::StorageService> server_storage_service;
    std::shared_ptr<wrench::Workflow> workflow;

    void do_BandwidthMeterCreationDestruction_test();

protected:
    BandwidthMeterServiceTest() {

        // platform for Link Usage
        std::string xml = "<?xml version='1.0'?>"
                          "<!DOCTYPE platform SYSTEM \"http://simgrid.gforge.inria.fr/simgrid/simgrid.dtd\">"
                          "<platform version=\"4.1\"> "
                          "   <zone id=\"AS0\" routing=\"Full\"> "
                          "       <host id=\"host1\" speed=\"1f\" core=\"10\"> "
                          "         <prop id=\"ram\" value=\"10B\"/>"
                          "         <disk id=\"large_disk\" read_bw=\"100000TBps\" write_bw=\"100000TBps\">"
                          "                            <prop id=\"size\" value=\"5000GiB\"/>"
                          "                            <prop id=\"mount\" value=\"/\"/>"
                          "         </disk>"
                          "       </host>"
                          "       <host id=\"host2\" speed=\"1f\" core=\"20\"> "
                          "          <prop id=\"ram\" value=\"20B\"/> "
                          "          <disk id=\"large_disk1\" read_bw=\"100000TBps\" write_bw=\"100000TBps\">"
                          "                            <prop id=\"size\" value=\"5000GiB\"/>"
                          "                            <prop id=\"mount\" value=\"/\"/>"
                          "       </disk>"
                          "       </host>"
                          "       <link id=\"1\" bandwidth=\"1Gbps\" latency=\"1us\"/>"
                          "       <route src=\"host1\" dst=\"host2\"> <link_ctn id=\"1\"/> </route>"
                          "   </zone> "
                          "</platform>";
        FILE *platform_file = fopen(platform_file_path.c_str(), "w");
        fprintf(platform_file, "%s", xml.c_str());
        fclose(platform_file);

    }

    std::string platform_file_path = UNIQUE_TMP_PATH_PREFIX + "platform.xml";

};


/**********************************************************************/
/**   BASIC CREATION/DESTRUCTION TEST                                **/
/**********************************************************************/
class BasicCreationDestructionTestWMS : public wrench::ExecutionController {
public:
    BasicCreationDestructionTestWMS(BandwidthMeterServiceTest *test,
                                    std::string &hostname) :
            wrench::ExecutionController(hostname, "test") {
        this->test = test;
    }

private:
    BandwidthMeterServiceTest *test;
    std::shared_ptr<wrench::DataFile> file;

    int main() {
        // Linknames
        const std::vector<std::string> linknames = wrench::Simulation::getLinknameList();
        const double TWO_SECOND_PERIOD = 2.0;
        const double FOUR_SECOND_PERIOD = 4.0;

        // Create a bandwidth meter service using the simple constructor
        // Testing bad constructor invocations
        try {
            this->createBandwidthMeter({}, TWO_SECOND_PERIOD);
            auto bogus_linknames = linknames;
            this->createBandwidthMeter(linknames, 0.0001);
            bogus_linknames.push_back("bogus_link");
            this->createBandwidthMeter(bogus_linknames, 5.0);
            throw std::runtime_error("Bad invocation of simple constructor should have thrown");
        } catch (std::invalid_argument &e) {
            // expected
        }

        auto bm1 = this->createBandwidthMeter(linknames, TWO_SECOND_PERIOD);


        // Create a bandwidth meter service using the complex constructor
        // Testing bad constructor invocations
        try {
            this->createBandwidthMeter({});
            std::map<std::string, double> measurement_periods;
            for (auto const &l : linknames) {
                measurement_periods[l] = 0.005;
            }
            this->createBandwidthMeter(measurement_periods);
            measurement_periods.clear();
            measurement_periods["bogus_link"] = 0.1;
            this->createBandwidthMeter(measurement_periods);
            throw std::runtime_error("Bad invocation of complex constructor should have thrown");
        } catch (std::invalid_argument &e) {
            // expected
        }

        std::map<std::string, double> measurement_periods;
        for (auto const &l : linknames) {
            measurement_periods[l] = FOUR_SECOND_PERIOD;
        }

        auto bm2 = this->createBandwidthMeter(measurement_periods);

        //Setting up storage services to accommodate data transfer.
        auto data_manager = this->createDataMovementManager();
        //copying file to force link usage.
        auto file = *(this->test->workflow->getFileMap().begin());
        data_manager->doSynchronousFileCopy(file.second,
                                            wrench::FileLocation::LOCATION(this->test->client_storage_service),
                                            wrench::FileLocation::LOCATION(this->test->server_storage_service));

        // Terminating the Bandwidth Meter Services
        bm1->stop();
        wrench::Simulation::sleep(1.0);
        bm2->kill();
        return 0;
    }
};

TEST_F(BandwidthMeterServiceTest, BasicCreationDestruction) {
    DO_TEST_WITH_FORK(do_BandwidthMeterCreationDestruction_test);
}

void BandwidthMeterServiceTest::do_BandwidthMeterCreationDestruction_test() {
    auto simulation = wrench::Simulation::createSimulation();
    int argc = 1;
    auto argv = (char **)calloc(argc, sizeof(char *));
    argv[0] = strdup("unit_test");
//    argv[1] = strdup("--wrench-full-log");

    EXPECT_NO_THROW(simulation->init(&argc, argv));

    EXPECT_NO_THROW(simulation->instantiatePlatform(platform_file_path));

    // get the single host
    std::string host = wrench::Simulation::getHostnameList()[0];
    std::shared_ptr<wrench::ExecutionController> wms = nullptr;;

    client_storage_service = simulation->add(new wrench::SimpleStorageService("host1", {"/"}, {}));
    server_storage_service = simulation->add(new wrench::SimpleStorageService("host2", {"/"}, {}));

    const double GB = 1000.0 * 1000.0 * 1000.0;
    //std::shared_ptr<wrench::DataFile> file = new wrench::DataFile("test_file", 10*GB);
    auto link_usage_workflow = wrench::Workflow::createWorkflow();
    std::shared_ptr<wrench::WorkflowTask> single_task;
    single_task = link_usage_workflow->addTask("dummy_task",1,1,1,8*GB);
    single_task->addInputFile(link_usage_workflow->addFile("test_file", 10*GB));


    EXPECT_NO_THROW(wms = simulation->add(
            new BasicCreationDestructionTestWMS(
                    this,
                    host)));

    simulation->add(new wrench::FileRegistryService("host1"));
    for (auto const &file : link_usage_workflow->getInputFiles()) {
        simulation->stageFile(file, client_storage_service);
    }

    EXPECT_NO_THROW(simulation->launch());

    link_usage_workflow->clear();

    for (int i=0; i < argc; i++)
        free(argv[i]);
    free(argv);
}

