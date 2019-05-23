/*
 * PID Temperature Controller for a RIMS setup.
 */

#include <Wire.h>
#include <IoAbstraction.h>
#include "Controller.h"
#include "TemperatureProbe.h"
#include "Constants.h"
#include "Config.h"
#include "Buttons.h"
#include "Alarm.h"

Controller &controller = Controller::instance();

/*
 * Handler for rotary encoder movement
 */
void handleRotate(int newValue) {
    static int oldValue = 1;

    newValue = !newValue ? 255 : (newValue - 1) % 255 + 1;
    if(newValue / 255 <= 1) {
        switches.getEncoder()->setCurrentReading(newValue);
    } 
    
    int diff = newValue - oldValue;
    if((diff > 0 && diff < 100) || diff < -100 ) {
        controller.encoderRight();
    } else if (diff < 0 || diff > 100) {
        controller.encoderLeft();
    }

   oldValue = newValue;
}

/*
 * Handler for rotary encoder push action
 */
void handleClick(uint8_t pin, bool held) {
    if(!held) {
        controller.encoderPressed();
    }
}

/*
 * Sketch setup
 */
void setup() {
    analogReference(EXTERNAL);

    // Set up serial console
    if(Config::getSerialOn()) {
        Serial.begin(Config::getSerialBaud());
        Serial.println("PID Temperature Controller");
    }

    // Set up rotary encoder
    switches.initialise(ioUsingArduino(), INPUT_PULLUP);
    setupRotaryEncoderWithInterrupt(ENCODER_S1, ENCODER_S2, handleRotate);
    switches.changeEncoderPrecision(256,1);
    switches.addSwitch(ENCODER_KEY, handleClick, NO_REPEAT);

    // Schedule analog buttons
    Buttons &buttons = Buttons::instance();
    taskManager.scheduleFixedRate(10, &buttons);

    // Start reading from the PT100 probe.
    TemperatureProbe &probe = TemperatureProbe::instance();
    taskManager.scheduleFixedRate(10, &probe);

    // Schedule the alarm
    Alarm &alarm = Alarm::instance();
    taskManager.scheduleFixedRate(1000, &alarm);

    // Switch to first screen
    controller.switchToPID();
}

void loop() {
    taskManager.runLoop();
}
