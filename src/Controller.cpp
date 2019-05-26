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
 * Cancel the scheduled task that refreshes the screen.
 */
void Controller::cancelScreenTask() {
    if(screenTask) {
        taskManager.cancelTask(screenTask);
        screenTask = 0;
    }
}

/*
 * Schedule a new task for refreshing the screen
 */
void Controller::scheduleScreen(AbstractScreen &screen) {
    cancelScreenTask();
    screen.clear();
    screen.render();
    screenTask = taskManager.scheduleFixedRate(SCREEN_REFRESH, &screen);
}

void Controller::switchToPID(){
    static PidModeScreen &screen = PidModeScreen::instance();
    
    scheduleScreen(screen);
    currentScreenController = &pidScreenController;

    previousScreen = currentScreen;
    currentScreen = pid;
}

void Controller::switchToMode() {
    static ModeScreen &screen = ModeScreen::instance();

    scheduleScreen(screen);
    currentScreenController = &modeScreenController;

    previousScreen = currentScreen;
    currentScreen = mode;
}

void Controller::switchToMenu() {
    static MenuScreen &screen = MenuScreen::instance();

    scheduleScreen(screen);
    currentScreenController = &menuScreenController;

    previousScreen = currentScreen;
    currentScreen = menu;
}

void Controller::switchToThermometer() {
    static ThermometerModeScreen &screen = ThermometerModeScreen::instance();

    scheduleScreen(screen);
    currentScreenController = &thermometerScreenController;
    
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
    static LcdContainer &container = LcdContainer::instance();
    container.getLCD().begin(4,20);
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