/*
 * Screen implementation for the thermometer mode (can be used for calibrating)
 */

#ifndef __THERMOMETERMODESCREEN_H__
#define __THERMOMETERMODESCREEN_H__

#include <LiquidCrystal.h>
#include "AbstractScreen.h"
#include "Constants.h"

class ThermometerModeScreen : public AbstractScreen {
    public:
        static ThermometerModeScreen& instance();

        ThermometerModeScreen();
        void render() override;
};

#endif