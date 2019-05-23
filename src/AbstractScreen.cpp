/*
 * Abstract LCD class
 */

#include "AbstractScreen.h"

/*
 * Constructor
 */
AbstractScreen::AbstractScreen() : 
    lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7) {
    lcd.begin(4,20); 
}

/*
 * default.
 */
void AbstractScreen::render() {
}

/*
 * Format a deciman number xx.x
 */
char * AbstractScreen::fmtDec(int whole, int fraction) {
    char * ptr = buf;
    int mag = 100;

    if(whole < 100) {
        *(ptr++) = ' ';
        mag = 10;
    }
    if(whole < 10) {
        *(ptr++) = ' ';
        mag = 1;
    }

    while(mag > 0) {
        *(ptr++) = (whole / mag) + '0';
        whole %= mag;
        mag /= 10;
    }
    
    *(ptr++) = '.';
    *(ptr++) = fraction + '0';
    *(ptr++) = '\0';

    return buf;
}

/*
 * Convert value * 1000 to a whole and fractional part,
 * and return a formatted string
 */
char * AbstractScreen::fmtDec(long value) {
    return fmtDec(value / 1000, value % 1000 / 100);
}

/*
 * Return a formatted string hh::mm::ss
 */
char * AbstractScreen::fmtTime(int hours, int minutes, int seconds) {
    char * ptr = buf;

    if(hours > 99) {
        *(ptr++) = '*';
        *(ptr++) = '*';
    } else {
        *(ptr++) = hours / 10 + '0';
        *(ptr++) = hours % 10 + '0';
    }

    *(ptr++) = ':';
    *(ptr++) = minutes / 10 + '0';
    *(ptr++) = minutes % 10 + '0';
    *(ptr++) = ':';
    *(ptr++) = seconds / 10 + '0';
    *(ptr++) = seconds % 10 + '0';
    *(ptr++) = '\0';

    return buf;
}

/*
 * Convert seconds to a formatted string.
 */
char * AbstractScreen::fmtTime(long time) {
    return fmtTime(time / 3600, time % 3600 / 60, time % 60);
}

/*
 * Set the cursor position
 */
void AbstractScreen::setSelectorPosition(int pos) {
    selectorPosition = pos;
}

/*
 * Define if it should be rendered as an editable field
 */
void AbstractScreen::setSelectorEditable(bool editable) {
    selectorEditable = editable;
}

/*
 * Check if a selector is editable
 */
bool AbstractScreen::getSelectorEditable() {
    return selectorEditable;
}

/*
 * Retrieve the selector's position
 */
int AbstractScreen::getSelectorPosition() {
    return selectorPosition;
}

/*
 * Move the selector down
 */
void AbstractScreen::moveSelectorDown() {
    if(selectorPosition > 0) {
        --selectorPosition;
    }
}

/*
 * Move the selector up
 */
void AbstractScreen::moveSelectorUp() {
    if(selectorPosition < selectorMax) {
        ++selectorPosition;
    }
}

/*
 * Set the maximum position
 */
void AbstractScreen::setSelectorMax(int max) {
    selectorMax = max;
}
