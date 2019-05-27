/*
 * Abstract LCD class
 */

#include "AbstractScreen.h"
#include "Config.h"
#include "LcdContainer.h"

static char buf[10];

/*
 * Constructor
 */
AbstractScreen::AbstractScreen() : lcd(LcdContainer::instance().getLCD()) {
}

/*
 * Format a whole number (positive only)
 */
char * fmtWhole(long value) {
    char * ptr = &buf[9];

    *(ptr) = '\0';
    do {
        *(--ptr) = value % 10 + '0';
        value /= 10;
    } while(value > 0);
    
    return ptr;
}

/*
 * Format a decimal number xx.x
 */
char * fmtDec(int whole, int fraction) {
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
char * fmtDec(long value) {
    return fmtDec(value / 1000, value % 1000 / 100);
}

/*
 * Format a regular double
 */
char * fmtDec(double value) {
    return fmtDec((long)value, (long)(value * 10) % 10);
}

/*
 * Return a formatted string hh::mm::ss
 */
char * fmtTime(int hours, int minutes, int seconds) {
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
char * fmtTime(unsigned long time) {
    return fmtTime(time / 3600, time % 3600 / 60, time % 60);
}

/*
 * Set the cursor position
 */
void AbstractScreen::setSelectorPosition(int pos) {
    selectorPosition = pos;
    if(selectorPosition < firstVisibleLine) {
        firstVisibleLine = selectorPosition;
    } else if (selectorPosition > firstVisibleLine + 3) {
        firstVisibleLine = selectorPosition - 3;
    }
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
        if(selectorPosition < firstVisibleLine) {
            firstVisibleLine = selectorPosition;
        }
    }
}

/*
 * Move the selector up
 */
void AbstractScreen::moveSelectorUp() {
    if(selectorPosition < selectorMax) {
        ++selectorPosition;
        if(selectorPosition > firstVisibleLine + 3) {
            firstVisibleLine = selectorPosition - 3;
        }
    }
}

/*
 * Set the maximum position
 */
void AbstractScreen::setSelectorMax(int max) {
    selectorMax = max;
}

/*
 * Render cursor
 */
void AbstractScreen::renderSelector() {
    for(int i=0; i<4; ++i) {
        lcd.setCursor(0, i);
        if(i == selectorPosition - firstVisibleLine) {
            lcd.print(selectorEditable ? ">>" : "* ");
        } else {
            lcd.print("  ");
        }
    }
    
}

/*
 * Clear screen
 */
void AbstractScreen::clear() {
    lcd.clear();
}