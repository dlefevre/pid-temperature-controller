/*
 * Menu screen implementation
 */

#include "MenuScreen.h"
#include "Config.h"
#include <LiquidCrystal.h>
#include "PidTask.h"
#include "TemperatureProbe.h"
#include "SerialTask.h"

void MenuScreen::renderLine(int line, const char *title, const char *val) {
    static char buffer[21];
    char *ptr = buffer;

    do {
        *(ptr++) = *(title++);
    } while(*title != '\0');
    
    int n = 18 - (ptr - buffer) + strlen(val);
    for(int i=0; i<n;  ++i)
        *ptr++ = ' ';
    
    do {
        *(ptr++) = *(val++);
    } while(*val != '\0');
    *ptr = '\0';

    lcd.setCursor(line, 2);
    lcd.print(buffer);
}

/*
 * Constructor
 */
MenuScreen::MenuScreen() {
    setSelectorMax(10);
}

/*
void MenuScreen::renderSelector() {

}
 * Render screen
 */
void MenuScreen::render() {
    for(int i=0; i<4; ++i) {
        renderMenuItem(i);
    }
    renderSelector();
}

/*
 * Render a single menu item (identified by the line on the screen)line
 */
void MenuScreen::renderMenuItem(int line) {
    static PidTask & pt = PidTask::instance();
    static TemperatureProbe & probe = TemperatureProbe::instance();
    static SerialTask & st = SerialTask::instance();

    switch(firstVisibleLine + line) {
        case 0: renderLine(line, "Kp", fmtDec(pt.getKp())); break;
        case 1: renderLine(line, "Ki", fmtDec(pt.getKi())); break;
        case 2: renderLine(line, "Kd", fmtDec(pt.getKd())); break;
        case 3: renderLine(line, "PID Max.", fmtWhole(pt.getMaxPower())); break;
        case 4: renderLine(line, "Direct Max.", fmtWhole(0)); break;
        case 5: renderLine(line, "Cal. 25", fmtDec(probe.getCalibrationPoint25())); break;
        case 6: renderLine(line, "Cal. 75", fmtDec(probe.getCalibrationPoint75())); break;
        case 7: renderLine(line, "Serial", st.isEnabled() ? "On" : "Off");
        case 8: renderLine(line, "Baud", fmtWhole(st.getBaud()));
        case 9: renderLine(line, "----- Save -----", "");
    }
}
