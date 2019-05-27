/*
 * Contoller used to swap screens and reconnect the rotary encoder
 * to the appropriate callbacks.
 */

#include "Controller.h"
#include "PidModeScreen.h"
#include "MenuScreen.h"
#include "ModeScreen.h"
#include "ThermometerModeScreen.h"
#include <IoAbstraction.h>
#include "Alarm.h"
#include "PidTask.h"
#include "LcdContainer.h"

/*
 * Return the sole instance
 */
Controller& Controller::instance() {
    static Controller one;
    return one;
}

/*
 * Schedule a new task for refreshing the screen
 */
void Controller::scheduleScreen(AbstractScreen &screen, AbstractScreenController &controller, Screen id) {
    if(screenTask != 0xFF) {
        taskManager.cancelTask(screenTask);
    }

    screen.clear();
    screen.render();

    screenTask = taskManager.scheduleFixedRate(SCREEN_REFRESH, &screen);
    currentScreenController = &controller;
    
    previousScreen = currentScreen;
    currentScreen = id;
}

void Controller::switchToPID(){
    scheduleScreen(PidModeScreen::instance(), pidScreenController, pid);
}

void Controller::switchToMode() {
    scheduleScreen(ModeScreen::instance(), modeScreenController, mode);
}

void Controller::switchToMenu() {
    scheduleScreen(MenuScreen::instance(), menuScreenController, menu);
}

void Controller::switchToThermometer() {
    scheduleScreen(ThermometerModeScreen::instance(), thermometerScreenController, thermometer);
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

void Controller::encoderLongPressed() {
    currentScreenController->longClick();
}

void Controller::button1Pressed() {
    static PidTask &pt = PidTask::instance();
    pt.toggle();
}

void Controller::button2Pressed() {
    static Alarm & alarm = Alarm::instance();
    alarm.toggle();
}

void Controller::button3Pressed() {
    LcdContainer::instance().getLCD().begin(4,20);
}

void Controller::button4Pressed() {
    if(currentScreen != menu) {
        switchToMenu();
    } else {
        switch(previousScreen) {
            case pid: switchToPID(); break;
            case mode: switchToMode(); break;
            case thermometer: switchToThermometer(); break;
            default: switchToPID(); break;
        }
    }
}