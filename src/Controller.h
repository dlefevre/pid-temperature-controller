/*
 * Contoller used to swap screens and reconnect the rotary encoder
 * to the appropriate callbacks.
 */

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "Constants.h"

class Controller {
    public:
        static inline Controller& instance() FORCE_INLINE;

        void switchToPID();
        void switchToDirect();
        void switchToMenu();

        void encoderLeft();
        void encoderRight();
        void encoderPressed();

    private:
};

Controller& Controller::instance() {
    static Controller one;
    return one;
}

#endif