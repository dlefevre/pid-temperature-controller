/*
 * Driver for the heating element
 */

#ifndef __HEATER_H__
#define __HEATER_H__

#include "Constants.h"
#include <IoAbstraction.h>

class Heater : public Executable {
    public:
        static Heater & instance();

        Heater();
        void exec() override;

        inline void setDuration(int, int) FORCE_INLINE;
        inline void setActive(bool) FORCE_INLINE;
        long getPower();
        inline bool isActive();


    private:
        int duration;
        int frame;
        bool active;
};

/*
 * Set the duration and the total timeframe
 */
void Heater::setDuration(int newDuration, int newFrame) {
    duration = newDuration;
    frame = newFrame;
}

/*
 * Set the heater to active/inactive (align it to the PID)
 */
void Heater::setActive(bool val) {
    active = val;
    digitalWrite(ACTIVE_PIN, active ? HIGH : LOW);
}

/*
 * return the heater's state
 */
bool Heater::isActive() {
    return active;
}

#endif