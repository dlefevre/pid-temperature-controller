/*
 * Screen implementation for the thermometer mode (can be used for calibrating)
 */

#include "ThermometerModeScreen.h"
#include "TemperatureProbe.h"

/*
 * Fetch and/or create instance
 */
ThermometerModeScreen & ThermometerModeScreen::instance() {
    static ThermometerModeScreen one;
    return one;
}

/*
 * Constructor
 */
ThermometerModeScreen::ThermometerModeScreen() {
    setSelectorMax(2);
    setSelectorPosition(2);
}

/*
 * Render screen
 */
void ThermometerModeScreen::render() {
    TemperatureProbe &probe = TemperatureProbe::instance();
    
    lcd.setCursor(2, 0);
    lcd.print(F("T:"));
    lcd.print(fmtDec(probe.getTemperature()));
    lcd.print(F("     "));
    lcd.setCursor(2, 1);
    lcd.print(F("R: "));
    lcd.print(probe.getFilteredRaw());
    lcd.print(F("     "));
    lcd.setCursor(2, 2);
    lcd.print(F("M: Thermometer"));

    renderSelector();
}