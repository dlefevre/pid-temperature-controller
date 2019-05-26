/*
 * Controller actions for Thermometer Screen
 */

#ifndef __THERMOMETERSCREENCONTROLLER_H__
#define __THERMOMETERSCREENCONTROLLER_H__

#include "Constants.h"
#include "AbstractScreenController.h"

class ThermometerScreenController : public AbstractScreenController {
    public:
        void goLeft() override;
        void goRight() override;
        void click() override;
};

#endif
