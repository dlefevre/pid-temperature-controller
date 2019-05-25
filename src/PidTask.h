/*
 * Specialized task for driving the PID
 */

#ifndef __PIDTASK_H__
#define __PIDTASK_H__

#include "Constants.h"
#include "PID_v1.h"
#include "IoAbstraction.h"

class PidTask : public Executable {
    public:
        static inline PidTask & instance() FORCE_INLINE;

        PidTask();
        void setKp(double);
        void setKi(double);
        void setKd(double);
        inline double getKp() FORCE_INLINE;
        inline double getKi() FORCE_INLINE;
        inline double getKd() FORCE_INLINE;
        inline int getMaxPower() FORCE_INLINE;
        void setMaxPower(int);
        inline void setSetPoint(long) FORCE_INLINE;
        inline long getSetPoint() FORCE_INLINE;
        void toggle();
        inline bool isActive() FORCE_INLINE;

        void exec() override;


    private:
        long   setPointLong;
        double setPoint;
        double input;
        double output;
        double kp;
        double ki;
        double kd;
        bool   active;
        int    maxPower;
                
        PID pid;

};

PidTask & PidTask::instance() {
    static PidTask one;
    return one;
}

/*
 * Define the setpoint (degrees Celcius * 1000)
 */
void PidTask::setSetPoint(long value) {
    setPointLong = value;
    setPoint = (double)value / 1000;
}

/*
 * Retrieve the current setPoint (degrees Celcius * 1000)
 */
long PidTask::getSetPoint() {
    return setPointLong;
}

bool PidTask::isActive() {
    return active;
}

double PidTask::getKp() {
    return kp;
}

double PidTask::getKi() {
    return ki;
}

double PidTask::getKd() {
    return kd;
}

int PidTask::getMaxPower() {
    return maxPower;
}

#endif