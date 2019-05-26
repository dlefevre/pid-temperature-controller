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
        static MenuScreen& instance();

        MenuScreen();
        void render() override;
        void renderMenuItem(int);
        void renderLine(int, const char *, const char *);
        
    private:
};

#endif