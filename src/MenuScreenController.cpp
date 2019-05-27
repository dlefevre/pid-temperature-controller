/*
 * Controller for menu screen
 */

#include "MenuScreenController.h"
#include "MenuScreen.h"
#include "Config.h"
#include "TemperatureProbe.h"
#include "PidTask.h"
#include "SerialTask.h"

static void updateItem(MenuScreen &, short);

/*
 * Assumed menu structure:
 *  - Kp
 *  - Ki
 *  - Kd
 *  - Maximum PID power
 *  - Maximum direct power
 *  - Calibration value @ 25 degrees Celcius
 *  - Calibration value @ 75 degrees Celcius
 *  - Enable/Disable Serial console
 *  - Set Baud rate
 */

void MenuScreenController::goLeft() {
    static MenuScreen &screen = MenuScreen::instance();

    if(!screen.getSelectorEditable()) {
        screen.moveSelectorDown();
        screen.render();
    } else {
        updateItem(-1);
    }
}

void MenuScreenController::goRight() {
    static MenuScreen &screen = MenuScreen::instance();

    if(!screen.getSelectorEditable()) {
        screen.moveSelectorUp();
        screen.render();
    } else {
        updateItem(1);
    }
}

void MenuScreenController::click() {
    static MenuScreen &screen = MenuScreen::instance();
    if(screen.getSelectorPosition() == 8) {
        Config::save();
    } else {
        if(screen.getSelectorEditable()) {
            screen.setSelectorEditable(false);
        } else {
            screen.setSelectorEditable(true);
            multiplier = 1;
        }
        screen.renderSelector();
    }
}

void MenuScreenController::longClick() {
    static MenuScreen &screen = MenuScreen::instance();
    if(screen.getSelectorEditable()) {
        multiplier = 100;
    }
}

/*
 * Helper functions
 */
template<typename T> T MenuScreenController::modify(T value, T delta, T min, T max) {
    value += delta * multiplier;
    if(value < min) {
        return min;
    }
    if(value > max) {
        return max;
    }
    return value;
}


void MenuScreenController::updateItem(short sign) {
    static MenuScreen & screen = MenuScreen::instance();
    static SerialTask &st = SerialTask::instance();
    static PidTask &pt = PidTask::instance();
    static TemperatureProbe & probe = TemperatureProbe::instance();
    static const long bauds[] = {9600l, 9600l, 19200l, 38400l, 57600l, 115200l, 115200l};

    switch(screen.getSelectorPosition()) {
        case 0: pt.setKp((double)modify((long)(pt.getKp() * 1024), 100l * sign, 0l, 1000000l) / 1024.0); break;
        case 1: pt.setKi((double)modify((long)(pt.getKi() * 1024), 100l * sign, 0l, 1000000l) / 1024.0); break;
        case 2: pt.setKd((double)modify((long)(pt.getKd() * 1024), 100l * sign, 0l, 1000000l) / 1024.0); break;
        case 3: pt.setMaxPower(modify(pt.getMaxPower(), 1 * sign, 0, 100)); break;
        case 4: probe.setCalibrationPoint25(modify(probe.getCalibrationPoint25(), 1l * sign, 0l, 1023l)); break;
        case 5: probe.setCalibrationPoint75(modify(probe.getCalibrationPoint75(), 1l * sign, 0l, 1023l)); break;
        case 6: st.toggle(); break;
        case 7:
            long currentBaud = st.getBaud();
            long newBaud = 9600;
            for(int i=1; i<=5; ++i) {
                if(bauds[i] == currentBaud) {
                    newBaud = bauds[i + sign];
                    break;
                }
            }
            st.setBaud(newBaud);
            break;
    }
    screen.renderMenuItem(screen.getSelectorPosition());
}
