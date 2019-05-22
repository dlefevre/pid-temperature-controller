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
        static inline ThermometerModeScreen& instance() FORCE_INLINE;

        ThermometerModeScreen();
        void render() override;
        
    private:
        static ThermometerModeScreen *pInstance;

        long raw;
        long temperature;
        int fraction;
};

/*
 * Fetch and/or create instance
 */
ThermometerModeScreen& ThermometerModeScreen::instance() {
    static ThermometerModeScreen one;
    return one;
}

#endif