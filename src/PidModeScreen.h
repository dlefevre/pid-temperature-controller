/*
 * Screen implementation for the PID mode
 */

#ifndef __PIDMODESCREEN_H__
#define __PIDMODESCREEN_H__

#include <LiquidCrystal.h>
#include "AbstractScreen.h"
#include "Constants.h"

class PidModeScreen : public AbstractScreen {
    public:
        static inline PidModeScreen& instance() FORCE_INLINE;

        PidModeScreen();
        void render() override;
        inline void renderSetPoint() FORCE_INLINE;
        inline void renderTemperature() FORCE_INLINE;
        inline void renderAlarm() FORCE_INLINE;
        
    private:

};

/*
 * Fetch and/or create instance
 */
PidModeScreen& PidModeScreen::instance() {
    static PidModeScreen one;
    return one;
}

#endif