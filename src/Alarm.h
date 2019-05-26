/*
 * Alarm implementation
 */

#ifndef __ALARM_H__
#define __ALARM_H__

#include "Constants.h"
#include <IoAbstraction.h>

class Alarm : public Executable {
    public:
        static Alarm & instance();

        inline void setTime(unsigned long) FORCE_INLINE;
        inline unsigned long getTime() FORCE_INLINE;
        inline void toggle() FORCE_INLINE;

        void exec() override;

    private:
        unsigned long time;
        bool enabled;
};

void Alarm::setTime(unsigned long val) {
    time = val;
}

unsigned long Alarm::getTime() {
    return time;
}

void Alarm::toggle() {
    enabled = !enabled;
}

#endif