/**
 * Copyright (c) 2017-2021. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <gtest/gtest.h>
#include <wrench-dev.h>

#include "../../include/TestWithFork.h"
#include "../../include/UniqueTmpPathPrefix.h"

class SimulationOutputTest : public ::testing::Test {

public:
    std::shared_ptr<wrench::Workflow> workflow;
    /*    std::shared_ptr<wrench::DataFile> input_file;
    std::shared_ptr<wrench::DataFile> output_file1;
    std::shared_ptr<wrench::DataFile> output_file2;
    std::shared_ptr<wrench::DataFile> output_file3;
    std::shared_ptr<wrench::DataFile> output_file4;
    std::shared_ptr<wrench::WorkflowTask> task1;
    std::shared_ptr<wrench::WorkflowTask> task2;
    std::shared_ptr<wrench::WorkflowTask> task3;
    std::shared_ptr<wrench::WorkflowTask> task4;
    std::shared_ptr<wrench::WorkflowTask> task5;
    std::shared_ptr<wrench::WorkflowTask> task6;*/
    wrench::ComputeService *compute_service = nullptr;
    wrench::StorageService *storage_service = nullptr;

    void do_emptyTrace_test();

protected:
    ~SimulationOutputTest() {
        workflow->clear();
        wrench::Simulation::removeAllFiles();
    }

    SimulationOutputTest() {
        // Create the simplest workflow
        workflow = wrench::Workflow::createWorkflow();

        //      // Create the files
        //      input_file = wrench::Simulation::addFile("input_file", 10);
        //      output_file1 = wrench::Simulation::addFile("output_file1", 10);
        //      output_file2 = wrench::Simulation::addFile("output_file2", 10);
        //      output_file3 = wrench::Simulation::addFile("output_file3", 10);
        //      output_file4 = wrench::Simulation::addFile("output_file4", 10);
        //
        //      // Create the tasks
        //      task1 = workflow->addTask("task_1_10s_1core", 10.0, 1, 1, 0.0);
        //      task2 = workflow->addTask("task_2_10s_1core", 10.0, 1, 1, 0.0);
        //      task3 = workflow->addTask("task_3_10s_2cores", 10.0, 2, 2, 0.0);
        //      task4 = workflow->addTask("task_4_10s_2cores", 10.0, 2, 2, 0.0);
        //      task5 = workflow->addTask("task_5_30s_1_to_3_cores", 30.0, 1, 3, 0.0);
        //      task6 = workflow->addTask("task_6_10s_1_to_2_cores", 12.0, 1, 2, 0.0);
        //      task1->setClusterID("ID1");
        //      task2->setClusterID("ID1");
        //      task3->setClusterID("ID1");
        //      task4->setClusterID("ID2");
        //      task5->setClusterID("ID2");
        //
        //      // Add file-task1 dependencies
        //      task1->addInputFile(input_file);
        //      task2->addInputFile(input_file);
        //      task3->addInputFile(input_file);
        //      task4->addInputFile(input_file);
        //      task5->addInputFile(input_file);
        //      task6->addInputFile(input_file);
        //
        //      task1->addOutputFile(output_file1);
        //      task2->addOutputFile(output_file2);
        //      task3->addOutputFile(output_file3);
        //      task4->addOutputFile(output_file4);
        //      task5->addOutputFile(output_file3);
        //      task6->addOutputFile(output_file4);
        //
        //      workflow->addControlDependency(task4, task5);

        // Create a platform file
        std::string xml = "<?xml version='1.0'?>"
                          "<!DOCTYPE platform SYSTEM \"https://simgrid.org/simgrid.dtd\">"
                          "<platform version=\"4.1\"> "
                          "   <zone id=\"AS0\" routing=\"Full\"> "
                          "       <host id=\"DualCoreHost\" speed=\"1f\" core=\"2\"/> "
                          "       <host id=\"QuadCoreHost\" speed=\"1f\" core=\"4\"/> "
                          "       <link id=\"1\" bandwidth=\"5000GBps\" latency=\"0us\"/>"
                          "       <route src=\"DualCoreHost\" dst=\"QuadCoreHost\"> <link_ctn id=\"1\"/> </route>"
                          "   </zone> "
                          "</platform>";
        FILE *platform_file = fopen(platform_file_path.c_str(), "w");
        fprintf(platform_file, "%s", xml.c_str());
        fclose(platform_file);
    }

    std::string platform_file_path = UNIQUE_TMP_PATH_PREFIX + "platform.xml";
};

/**********************************************************************/
/**            EMPTY SIMULATION OUTPUT                               **/
/**********************************************************************/

class EmptySimulationOutputWMS : public wrench::ExecutionController {

public:
    EmptySimulationOutputWMS(SimulationOutputTest *test,
                             std::string &hostname) : wrench::ExecutionController(hostname, "test"), test(test) {
    }

private:
    SimulationOutputTest *test;

    int main() override {

#ifdef WRENCH_INTERNAL_EXCEPTIONS
        try {
            this->getSimulation()->getOutput().addTimestampTaskStart(0.0, nullptr);
            this->getSimulation()->getOutput().addTimestampTaskCompletion(0.0, nullptr);
            this->getSimulation()->getOutput().addTimestampTaskTermination(0.0, nullptr);
            this->getSimulation()->getOutput().addTimestampTaskFailure(0.0, nullptr);
            throw std::runtime_error("Should have caught exception!");
        } catch (std::exception &ignore) {
        }
#endif

        // do nothing

        return 0;
    }
};

TEST_F(SimulationOutputTest, EmptySimulationOutputTest) {
    DO_TEST_WITH_FORK(do_emptyTrace_test);
}

void SimulationOutputTest::do_emptyTrace_test() {

    // Create and initialize a simulation
    auto simulation = wrench::Simulation::createSimulation();
    int argc = 1;
    auto argv = (char **) calloc(argc, sizeof(char *));
    argv[0] = strdup("unit_test");

    ASSERT_NO_THROW(simulation->init(&argc, argv));

    // Setting up the platform
    ASSERT_NO_THROW(simulation->instantiatePlatform(platform_file_path));

    // Get a hostname
    std::string hostname = wrench::Simulation::getHostnameList()[0];


    // Create a WMS
    std::shared_ptr<wrench::ExecutionController> wms = nullptr;

    ASSERT_NO_THROW(wms = simulation->add(
                            new EmptySimulationOutputWMS(this, hostname)));

    ASSERT_NO_THROW(simulation->launch());

    // Get the number of task1 completions
    std::vector<wrench::SimulationTimestamp<wrench::SimulationTimestampTaskCompletion> *> trace;
    trace = simulation->getOutput().getTrace<wrench::SimulationTimestampTaskCompletion>();
    ASSERT_EQ(0, trace.size());


    for (int i = 0; i < argc; i++)
        free(argv[i]);
    free(argv);
}
