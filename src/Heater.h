/*
 * Driver for the heating element
 */

#ifndef __HEATER_H__
#define __HEATER_H__

#include "Constants.h"
#include <IoAbstraction.h>

class Heater : public Executable {
    public:
        static inline Heater & instance() FORCE_INLINE;

        Heater();
        void exec() override;

        inline void setDuration(int, int) FORCE_INLINE;
        inline void setActive(bool) FORCE_INLINE;

    private:
        int duration;
        int frame;
        bool active;
};

Heater & Heater::instance() {
    static Heater one;
    return one;
}

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

#endif