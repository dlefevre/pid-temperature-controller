/**
 * PID task
 */

#include "PidTask.h"
#include "Config.h"
#include "TemperatureProbe.h"
#include "Heater.h"

/*
 * Return the sole instance
 */
PidTask & PidTask::instance() {
    static PidTask one;
    return one;
}

/*
 * Constructor
 */
PidTask::PidTask() :
    setPointLong(50000L),
    setPoint(50.0),
    kp(Config::getPidKp()),
    ki(Config::getPidKi()),
    kd(Config::getPidKd()),
    maxPower(Config::getPidMaxPower()),
    pid(&input, &output, &setPoint, kp, ki, kd, P_ON_M, DIRECT) {
    pid.SetOutputLimits(0.0, (double)HEATING_WINDOW * maxPower / 100.0);
}

/*
 * Main loop
 */
void PidTask::exec() {
    static TemperatureProbe &probe = TemperatureProbe::instance();
    static Heater &heater = Heater::instance();

    if(active) {
        input = (double)probe.getTemperature() / 1000.0;
        pid.Compute();
        heater.setDuration((int)output, HEATING_WINDOW);
    }
}

/*
 * Set the value for Kp
 */
void PidTask::setKp(double value) {
    kp = value;
    pid.SetTunings(kp, ki, kd);
    Config::setPidKp(kp);
}

/*
 * Set the value for Ki
 */
void PidTask::setKi(double value) {
    ki = value;
    pid.SetTunings(kp, ki, kd);
    Config::setPidKi(ki);
}

/*
 * Set the value for Kd
 */
void PidTask::setKd(double value) {
    kd = value;
    pid.SetTunings(kp, ki, kd);
    Config::setPidKd(value);
}

/*
 * Activate or disable the Pid controller
 */
void PidTask::toggle() {
    static Heater &heater = Heater::instance();
    active = !active;
    pid.SetMode(active ? AUTOMATIC : MANUAL);
    heater.setActive(active);
}

/*
 * Update the maximum power for the heating element.
 */
void PidTask::setMaxPower(int max) {
    maxPower = max;
    Config::setPidMaxPower(maxPower);
    pid.SetOutputLimits(0.0, HEATING_WINDOW * maxPower / 100);
}