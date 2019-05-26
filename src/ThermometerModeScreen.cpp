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
    lcd.print("T:");
    lcd.print(fmtDec(probe.getTemperature()));
    lcd.print("     ");
    lcd.setCursor(2, 1);
    lcd.print("R: ");
    lcd.print(probe.getFilteredRaw());
    lcd.print("     ");
    lcd.setCursor(2, 2);
    lcd.print("M: Thermometer");

    renderSelector();
}