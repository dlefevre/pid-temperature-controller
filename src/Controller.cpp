/*
 * Contoller used to swap screens and reconnect the rotary encoder
 * to the appropriate callbacks.
 */

#include "Controller.h"
#include "PidModeScreen.h"
#include <IoAbstraction.h>
#include "Alarm.h"

void Controller::switchToPID(){
    static PidModeScreen &screen = PidModeScreen::instance();
    taskManager.scheduleFixedRate(500, &screen);

    currentScreenController = &pidScreenController;

    previousScreen = currentScreen;
    currentScreen = pid;
}

void Controller::switchToDirect() {
    previousScreen = currentScreen;
    currentScreen = direct;
}

void Controller::switchToMenu() {
    previousScreen = currentScreen;
    currentScreen = menu;
}

void Controller::switchToThermometer() {
    previousScreen = currentScreen;
    currentScreen = thermometer;
}

void Controller::encoderLeft() {
    currentScreenController->goLeft();
}

void Controller::encoderRight() {
    currentScreenController->goRight();
}

void Controller::encoderPressed() {
    currentScreenController->click();
}

void Controller::button1Pressed() {
    Serial.print("button 1");
    Serial.println();
}

void Controller::button2Pressed() {
    static Alarm & alarm = Alarm::instance();
    alarm.toggle();
}

void Controller::button3Pressed() {

}

void Controller::button4Pressed() {
    if(currentScreen != menu) {
        switchToMenu();
    } else {
        switch(previousScreen) {
            case pid: switchToPID(); break;
            case direct: switchToDirect(); break;
            case thermometer: switchToThermometer(); break;
            default: switchToPID(); break;
        }
    }
}