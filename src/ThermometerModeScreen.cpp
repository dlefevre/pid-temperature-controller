/*
 * Screen implementation for the thermometer mode (can be used for calibrating)
 */

#include "ThermometerModeScreen.h"
#include "TemperatureProbe.h"

/*
 * Constructor
 */
ThermometerModeScreen::ThermometerModeScreen() {

}

/*
 * Render screen
 */
void ThermometerModeScreen::render() {
    // TemperatureProbe &probe = TemperatureProbe::instance();

    // int realraw = probe.getUnfilteredRaw();
    // raw = probe.getFilteredRaw();
    // temperature = probe.getTemperature();
    // fraction = (temperature % 1000) / 100;
    // temperature /= 1000;
    
    // char buf[10];
    // sprintf(buf, "  Raw:     %4d     ", realraw);
    // lcd.setCursor(0, 0);
    // lcd.print(buf);
    // sprintf(buf, "  Smooth:  %4d     ", raw);
    // lcd.setCursor(0, 1);
    // lcd.print(buf);
    // sprintf(buf, "  Temp:    %4d.", temperature);
    // lcd.setCursor(0, 2);
    // lcd.print(buf);
    // sprintf(buf, "%1d  ", fraction);
    // lcd.print(buf);
}