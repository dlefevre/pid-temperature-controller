/*
 * Controller for Pid screen
 */

#include "PidScreenController.h"

#include "PidModeScreen.h"
#include "Alarm.h"
#include "PidTask.h"


void PidScreenController::goLeft() {
    static PidModeScreen &screen = PidModeScreen::instance();
    if(!screen.getSelectorEditable()) {
        screen.moveSelectorDown();
        screen.renderSelector();
    } else {
        switch(screen.getSelectorPosition()) {
            case 0: 
                static PidTask &pt = PidTask::instance();
                if(pt.getSetPoint() > 0) {
                    pt.setSetPoint(pt.getSetPoint() - 500);
                    screen.renderSetPoint();
                }
                break;
            case 1:
                static Alarm &alarm = Alarm::instance();
                if(alarm.getTime() >= 60) { 
                    alarm.setTime(alarm.getTime() - 60);
                    screen.renderAlarm();
                }
                break;
        }
    }
}

void PidScreenController::goRight() {
    static PidModeScreen &screen = PidModeScreen::instance();
    if(!screen.getSelectorEditable()) {
        screen.moveSelectorUp();
        screen.renderSelector();
    } else {
        switch(screen.getSelectorPosition()) {
            case 0: 
                static PidTask &pt = PidTask::instance();
                if(pt.getSetPoint() < 90000) {
                    pt.setSetPoint(pt.getSetPoint() + 500);
                    screen.renderSetPoint();
                }
                break;
            case 1:
                static Alarm & alarm = Alarm::instance();
                alarm.setTime(alarm.getTime() + 60);
                screen.renderAlarm();
                break;
        }
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
