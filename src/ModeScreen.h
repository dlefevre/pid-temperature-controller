/*
 * Switch between modes.
 */

#ifndef __MODESCREEN_H__
#define __MODESCREEN_H__

#include <LiquidCrystal.h>
#include "AbstractScreen.h"
#include "Constants.h"

class ModeScreen : public AbstractScreen {
    public:
        static ModeScreen& instance();
        ModeScreen();
        void render() override;
};

#endif