/*
 * Contoller used to swap screens and reconnect the rotary encoder
 * to the appropriate callbacks.
 */

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "Constants.h"
#include "PidScreenController.h"
#include "MenuScreenController.h"
#include "ModeScreenController.h"
#include "ThermometerScreenController.h"

class Controller {
    public:
        static Controller& instance();

        void switchToPID();
        void switchToMode();
        void switchToThermometer();
        void switchToMenu();

        void encoderLeft();
        void encoderRight();
        void encoderPressed();
        void encoderLongPressed();

        void button1Pressed();
        void button2Pressed();
        void button3Pressed();
        void button4Pressed();

    private:
        enum Screen {pid, thermometer, menu, mode};
        Screen currentScreen;
        Screen previousScreen;

        AbstractScreenController * currentScreenController;
        PidScreenController pidScreenController;
        MenuScreenController menuScreenController;
        ModeScreenController modeScreenController;
        ThermometerScreenController thermometerScreenController;

        uint8_t screenTask = 0xFF;
        void scheduleScreen(AbstractScreen &, AbstractScreenController &, Screen);
};

#endif