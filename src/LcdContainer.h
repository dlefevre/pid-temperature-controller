/*
 * Container class for the LCD screen (for easy sharing between screens)
 */

#ifndef __LCDCONTAINER_H__
#define __LCDCONTAINER_H__

#include "Constants.h"
#include <LiquidCrystal.h>

class LcdContainer {
    private:
        LiquidCrystal lcd;

    public:
        // Initialize LCD
        LcdContainer() : lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7) {
            lcd.begin(4,20);
        }

        // Return reference to container instance
        static LcdContainer & instance() {
            static LcdContainer one;
            return one;
        }

        // Return reference to LiquidCrystal instance
        LiquidCrystal & getLCD() {
            return lcd;
        }
};

#endif
