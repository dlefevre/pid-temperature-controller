/*
 * Contoller used to swap screens and reconnect the rotary encoder
 * to the appropriate callbacks.
 */

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "Constants.h"
#include "PidScreenController.h"
#include "MenuScreenController.h"

class Controller {
    public:
        static inline Controller& instance() FORCE_INLINE;

        void switchToPID();
        void switchToDirect();
        void switchToThermometer();
        void switchToMenu();

        void encoderLeft();
        void encoderRight();
        void encoderPressed();

        void button1Pressed();
        void button2Pressed();
        void button3Pressed();
        void button4Pressed();

    private:
        enum Screen {pid, direct, thermometer, menu, mode};
        Screen currentScreen;
        Screen previousScreen;

        AbstractScreenController * currentScreenController;
        PidScreenController pidScreenController;
        MenuScreenController menuScreenController;

        uint8_t screenTask;
        void cancelScreenTask();
        void scheduleScreen(AbstractScreen &);
};

Controller& Controller::instance() {
    static Controller one;
    return one;
}

#endif