/*
 * Screen implementation for the thermometer mode (can be used for calibrating)
 */

#include "PidModeScreen.h"
#include "TemperatureProbe.h"

// Buffer for sprintf
char buf[21];

/*
 * Constructor
 */
PidModeScreen::PidModeScreen() {

}

/*
 * Render set point
 */
void PidModeScreen::renderSetPoint() {
  
    // TODO: Fetch and convert setpoint

    lcd.setCursor(2, 0);
    lcd.print("S:");
    lcd.print(fmtDec(0));
}

/*
 * Render Temperature
 */
void PidModeScreen::renderTemperature() {
    static TemperatureProbe &probe = TemperatureProbe::instance();

    lcd.setCursor(13, 0);
    lcd.print("T:");
    lcd.print(fmtDec(probe.getTemperature()));
}

/*
 * Render alarm
 */
void PidModeScreen::renderAlarm() {
    // TODO: Fetch alarm time
    lcd.setCursor(2, 1);
    lcd.print("A: ");
    lcd.print(fmtTime(0));
}

/*
 * Render screen
 */
void PidModeScreen::render() {
    lcd.setCursor(0, 0);
    lcd.print("*");

    renderSetPoint();
    renderTemperature();
    renderAlarm();

    lcd.setCursor(2, 2);
    lcd.print("M: PID");
    lcd.setCursor(2, 3);
    lcd.print("I: Active @ 0%  ");
}