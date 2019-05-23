/*
 * Controller for Pid screen
 */

#include "PidScreenController.h"

#include "PidModeScreen.h";

PidScreenController::PidScreenController() {
}

void PidScreenController::goLeft() {
    Serial.print("go left");
    Serial.println();
    static PidModeScreen &screen = PidModeScreen::instance();
    if(!screen.getSelectorEditable()) {
        screen.moveSelectorDown();
        screen.renderSelector();
    }
}

void PidScreenController::goRight() {
    Serial.print("go right");
    Serial.println();
    static PidModeScreen &screen = PidModeScreen::instance();
    if(!screen.getSelectorEditable()) {
        screen.moveSelectorUp();
        screen.renderSelector();
    }
}

void PidScreenController::click() {
    static PidModeScreen &screen = PidModeScreen::instance();
    if(screen.getSelectorEditable()) {
        screen.setSelectorEditable(false);
    } else {
        screen.setSelectorEditable(true);
    }
    screen.renderSelector();
}
