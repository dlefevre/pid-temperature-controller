/*
 * Screen for switching between modes
 */

#include "ModeScreen.h"

ModeScreen & ModeScreen::instance() {
    static ModeScreen one;
    return one;
}

ModeScreen::ModeScreen() {
    setSelectorMax(1);
}

void ModeScreen::render() {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print(F("PID"));
    lcd.setCursor(2, 1);
    lcd.print(F("Thermometer"));

    renderSelector();
}