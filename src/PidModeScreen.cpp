/*
 * Screen implementation for the thermometer mode (can be used for calibrating)
 */

#include "PidModeScreen.h"
#include "TemperatureProbe.h"
#include "Alarm.h"
#include "PidTask.h"
#include "Heater.h"

/*
 * Fetch and/or create instance
 */
PidModeScreen& PidModeScreen::instance() {
    static PidModeScreen one;
    return one;
}

/*
 * Constructor
 */
PidModeScreen::PidModeScreen() {
    setSelectorMax(2);
}

/*
 * Render set point
 */
void PidModeScreen::renderSetPoint() {
    static PidTask &pi = PidTask::instance();
    lcd.setCursor(2, 0);
    lcd.print("S:");
    lcd.print(fmtDec(pi.getSetPoint()));
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
    static Alarm & alarm = Alarm::instance();

    lcd.setCursor(2, 1);
    lcd.print("A: ");
    lcd.print(fmtTime(alarm.getTime()));
}

/*
 * Render screen
 */
void PidModeScreen::render() {
    static Heater &heater = Heater::instance();

    renderSetPoint();
    renderTemperature();
    renderAlarm();
    renderSelector();

    lcd.setCursor(2, 2);
    lcd.print("M: PID");

    lcd.setCursor(2, 3);
    if(heater.isActive()) {
        lcd.print("I: running @");
        lcd.print(fmtDec(heater.getPower()));
        lcd.print("%");
    } else {
        lcd.print("I: disabled       ");
    }
    
}