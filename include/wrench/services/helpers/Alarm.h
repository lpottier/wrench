/**
 * Copyright (c) 2017. The WRENCH Team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */



#ifndef WRENCH_ALARM_H
#define WRENCH_ALARM_H


#include <string>
#include <memory>
#include <wrench/services/Service.h>
#include <simulation/SimulationMessage.h>

namespace wrench {

    /***********************/
    /** \cond INTERNAL     */
    /***********************/

    /**
     * @brief A daemon that sends a message to a mailbox after some specified amount of time and then terminates
     */

    class Alarm: public Service {

        friend class S4U_Daemon;

    public:

        ~Alarm();

        Alarm(double date, std::string hostname, std::string reply_mailbox_name,
              SimulationMessage* msg, std::string suffix);

        double date;
        std::string reply_mailbox_name;
        std::unique_ptr<SimulationMessage> msg;

        int main() override;

        void kill();

    };

    /***********************/
    /** \endcond           */
    /***********************/

}


#endif //WRENCH_ALARM_H
