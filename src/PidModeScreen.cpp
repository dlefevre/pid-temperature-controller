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
    lcd.print(F("S:"));
    lcd.print(fmtDec(pi.getSetPoint()));
}

/*
 * Render Temperature
 */
void PidModeScreen::renderTemperature() {
    static TemperatureProbe &probe = TemperatureProbe::instance();

    lcd.setCursor(13, 0);
    lcd.print(F("T:"));
    lcd.print(fmtDec(probe.getTemperature()));
}

/*
 * Render alarm
 */
void PidModeScreen::renderAlarm() {
    static Alarm & alarm = Alarm::instance();

    lcd.setCursor(2, 1);
    lcd.print(F("A: "));
    lcd.print(fmtTime(alarm.getTime()));
}

/*
 * Render screen
 */
void PidModeScreen::render() {
    static Heater &heater = Heater::instance();
    static PidTask &pt = PidTask::instance();

    renderSetPoint();
    renderTemperature();
    renderAlarm();
    renderSelector();

    lcd.setCursor(2, 2);
    lcd.print(F("M: PID"));

    lcd.setCursor(2, 3);
    if(heater.isActive()) {
        lcd.print(F("I: "));
        if(pt.isActive()) {
            lcd.print(F("running @"));
        } else {
            lcd.print(F("manual @ "));
        }
        lcd.print(fmtDec(heater.getPower()));
        lcd.print("%");
    } else {
        lcd.print(F("I: disabled       "));
    }
    
}