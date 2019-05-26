/*
 * Abstract base class for screen controllers
 */

#ifndef __ABSTRACTSCREENCONTROLLER_H__
#define __ABSTRACTSCREENCONTROLLER_H__

#include "Constants.h"
#include "AbstractScreen.h"

class AbstractScreenController {
    public:
        AbstractScreenController();

        virtual void goLeft() = 0;
        virtual void goRight() = 0;
        virtual void click() = 0;
        virtual void longClick() {};

};

#endif
