/*
 * Screen implementation for the PID mode
 */

#ifndef __MENUSCREEN_H__
#define __MENUSCREEN_H__

#include <LiquidCrystal.h>
#include "AbstractScreen.h"
#include "Constants.h"

class MenuScreen : public AbstractScreen {
    public:
        static inline MenuScreen& instance() FORCE_INLINE;

        MenuScreen();
        void render() override;
        void renderMenuItem(int);
        void renderLine(int, const char *, const char *);
        
    private:
};

/*
 * Fetch and/or create instance
 */
MenuScreen& MenuScreen::instance() {
    static MenuScreen one;
    return one;
}

#endif