/*
 * Manage serial data
 */

#include "SerialTask.h"

SerialTask::SerialTask() :
    enabled(Config::getSerialOn()),
    baud(Config::getSerialBaud()) {
    if(enabled) {
        Serial.begin(baud);
    }
}

/*
 * Scheduled loop.
 */
void SerialTask::exec() {

}

/*
 * Turn the serial communication on and off
 */
void SerialTask::toggle() {
    if(enabled) {
        Serial.end();
    } else {
        Serial.begin(baud);
    }
    enabled = !enabled;
    Config::setSerialOn(enabled);
}