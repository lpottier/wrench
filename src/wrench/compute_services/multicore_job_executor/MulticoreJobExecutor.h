/**
 * Copyright (c) 2017. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef WRENCH_MULTICORETASKEXECUTOR_H
#define WRENCH_MULTICORETASKEXECUTOR_H


#include <queue>
#include "workflow/WorkflowTask.h"
#include "compute_services/ComputeService.h"
#include "helper_daemons/sequential_task_executor/SequentialTaskExecutor.h"
#include "simulation/SimulationMessage.h"

namespace wrench {

		class Simulation;


		/**  @brief Implementation of a Compute Service abstraction that
		 *   runs on a multi-core host.
		 */
		class MulticoreJobExecutor : public ComputeService, public S4U_DaemonWithMailbox {

		public:
				enum Property {
					STOP_DAEMON_MESSAGE_PAYLOAD,
				};

		private:

				std::map<MulticoreJobExecutor::Property, std::string> default_property_values =
								{{MulticoreJobExecutor::Property::STOP_DAEMON_MESSAGE_PAYLOAD, "1024"},
								};

		public:
				MulticoreJobExecutor(Simulation *simulation, std::string hostname,
														 std::map<MulticoreJobExecutor::Property, std::string> = {},
														 int num_worker_threads = -1, double ttl = -1.0,
														 PilotJob *pj = nullptr, std::string suffix="");

				// Stopping the service
				void stop();

				// Running jobs
				void runStandardJob(StandardJob *job);
				void runPilotJob(PilotJob *job);

				// Getting information
				unsigned long getNumCores();
				unsigned long getNumIdleCores();
				double getTTL();
				double getCoreFlopRate();

				// Setting/Getting property
				void setProperty(MulticoreJobExecutor::Property, std::string);
				std::string getProperty(MulticoreJobExecutor::Property);
		private:

				std::map<MulticoreJobExecutor::Property, std::string> property_list;

				std::string hostname;
				int num_worker_threads; // total threads to run tasks from standard jobs
				double ttl;
				bool has_ttl;
				double death_date;
				PilotJob *containing_pilot_job;

				unsigned int num_available_worker_threads; // number of worker threads that can currently be
				// used to run tasks from standard jobs

				// Vector of worker threads
				std::vector<std::unique_ptr<SequentialTaskExecutor>> sequential_task_executors;

				// Vector of idle worker threads available to run tasks from standard jobs
				std::set<SequentialTaskExecutor *> idle_sequential_task_executors;
				// Vector of worker threads currencly running tasks from standard jobs
				std::set<SequentialTaskExecutor *> busy_sequential_task_executors;

				// Queue of pending jobs (standard or pilot) that haven't began executing
				std::queue<WorkflowJob *> pending_jobs;

				// Set of currently running (standard or pilot) jobs
				std::set<WorkflowJob *> running_jobs;

				// Queue of standard job tasks waiting for execution
				std::queue<WorkflowTask *> pending_tasks;

				// Set of currently running standard job tasks
				std::set<WorkflowTask *> running_tasks;

				int main();

				// Helper functions to make main() a bit more palatable
				void initialize();
				void terminate();
				void terminateAllWorkerThreads();
				void terminateAllPilotJobs();
				void failCurrentStandardJobs();
				void processTaskCompletion(WorkflowTask *, SequentialTaskExecutor *);
				void processPilotJobCompletion(PilotJob *job);
				bool processNextMessage(double timeout);
				bool dispatchNextPendingTask();
				bool dispatchNextPendingJob();
		};
};


#endif //WRENCH_MULTICORETASKEXECUTOR_H
