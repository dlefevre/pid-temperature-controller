/*
 * Contoller used to swap screens and reconnect the rotary encoder
 * to the appropriate callbacks.
 */

#include "Controller.h"
#include "PidModeScreen.h"
#include "MenuScreen.h"
#include <IoAbstraction.h>
#include "Alarm.h"
#include "PidTask.h"

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

void Controller::switchToDirect() {
    previousScreen = currentScreen;
    currentScreen = direct;
}

void Controller::switchToMenu() {
    static MenuScreen &screen = MenuScreen::instance();

    scheduleScreen(screen);
    currentScreenController = &menuScreenController;

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
    static PidTask &pt = PidTask::instance();
    pt.toggle();
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