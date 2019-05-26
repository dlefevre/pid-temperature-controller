/*
 * Controller for mode selection screen
 */

#include "ModeScreenController.h"
#include "ModeScreen.h"
#include "Controller.h"

void ModeScreenController::goLeft() {
    ModeScreen &screen = ModeScreen::instance();
    screen.moveSelectorDown();
    screen.renderSelector();
}

void ModeScreenController::goRight() {
    ModeScreen &screen = ModeScreen::instance();
    screen.moveSelectorUp();
    screen.renderSelector();
}

void ModeScreenController::click() {
    ModeScreen &screen = ModeScreen::instance();
    Controller &controller = Controller::instance();

    switch(screen.getSelectorPosition()) {
        case 0: controller.switchToPID(); break;
        case 1: controller.switchToThermometer(); break;
        default: controller.switchToPID(); break;
    }
}