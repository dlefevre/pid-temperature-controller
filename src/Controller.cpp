/*
 * Contoller used to swap screens and reconnect the rotary encoder
 * to the appropriate callbacks.
 */

#include "Controller.h"
#include "PidModeScreen.h"
#include <IoAbstraction.h>

void Controller::switchToPID(){
    PidModeScreen &screen = PidModeScreen::instance();
    taskManager.scheduleFixedRate(500, &screen);
}

void Controller::switchToDirect() {

}

void Controller::switchToMenu() {

}

void Controller::encoderLeft() {

}

void Controller::encoderRight() {

}

void Controller::encoderPressed() {

}