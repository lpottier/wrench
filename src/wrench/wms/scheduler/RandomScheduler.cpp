/**
 * Copyright (c) 2017. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * @brief wrench::RandomScheduler implements a simple random scheduler
 */

#include <xbt.h>

#include "simgrid_S4U_util/S4U_Mailbox.h"
#include "wms/scheduler/RandomScheduler.h"

XBT_LOG_NEW_DEFAULT_CATEGORY(random_scheduler, "Log category for Random Scheduler");

namespace wrench {

	/**
	 * Schedule and run a set of ready tasks in available compute resources
	 *
	 * @param ready_tasks is a vector of ready tasks
	 * @param compute_services is a vector of available compute resources
	 * @param callback_mailbox is the name of the mailbox
	 */
	void RandomScheduler::runTasks(std::vector<WorkflowTask *> ready_tasks,
	                               std::vector<std::unique_ptr<ComputeService>> &compute_services,
	                               std::string callback_mailbox) {

		if (ready_tasks.size() > 0) {
			XBT_INFO("There are %ld ready tasks", ready_tasks.size());
		}
		for (int i = 0; i < ready_tasks.size(); i++) {
			XBT_INFO("Submitting task %s for execution", ready_tasks[i]->id.c_str());

			// schedule task to first available compute resource
			for (int j = 0; j < compute_services.size(); j++) {
				if (compute_services[j]->hasIdleCore()) {
					ready_tasks[i]->setScheduled();
					compute_services[j]->runTask(ready_tasks[i], callback_mailbox);
					break;
				}
			}
		}

		// Wait for a task completion
		XBT_INFO("Waiting for a task to complete...");
		std::unique_ptr<SimulationMessage> message = S4U_Mailbox::get(callback_mailbox);
		std::unique_ptr<TaskDoneMessage> m(static_cast<TaskDoneMessage *>(message.release()));

		XBT_INFO("Notified that task %s has completed", m->task->id.c_str());
	}
}