/*
 * Basic class for setting up the serial console and for sending periodic output.
 */

#ifndef __SERIALTASK_H__
#define __SERIALTASK_H__

#include <IoAbstraction.h>
#include "Config.h"

class SerialTask : public Executable {
    public:
        static SerialTask & instance();

        void exec() override;

        inline bool isEnabled() FORCE_INLINE;
        void toggle();
        inline long getBaud() FORCE_INLINE;
        inline void setBaud(long) FORCE_INLINE;

        SerialTask();

    private:
        bool enabled;
        long baud;

        long setPoint;
        long temperature;
        long power;
        int maxPower;
};

bool SerialTask::isEnabled() {
    return enabled;
}

long SerialTask::getBaud() {
    return baud;
}

void SerialTask::setBaud(long val) {
    baud = val;
    Config::setSerialBaud(val);
}

#endif