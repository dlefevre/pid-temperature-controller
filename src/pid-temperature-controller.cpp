/*
 * PID Temperature Controller for a RIMS setup.
 */

#include <Wire.h>
#include <IoAbstraction.h>
#include "Controller.h"
#include "TemperatureProbe.h"
#include "Constants.h"

void setup() {
    Serial.begin(115200);

    TemperatureProbe &probe = TemperatureProbe::instance();
    taskManager.scheduleFixedRate(10, &probe);

    Controller &controller = Controller::instance();
    controller.switchToPID();
}

void loop() {
    taskManager.runLoop();
}
