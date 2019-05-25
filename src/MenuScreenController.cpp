/*
 * Controller for menu screen
 */

#include "MenuScreenController.h"
#include "MenuScreen.h"
#include "Config.h"
#include "TemperatureProbe.h"
#include "PidTask.h"
#include "SerialTask.h"

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

template<typename T> T modify(T value, T delta, T min, T max);

void MenuScreenController::goLeft() {
    static MenuScreen &screen = MenuScreen::instance();
    static SerialTask &st = SerialTask::instance();
    static PidTask &pt = PidTask::instance();
    static TemperatureProbe & probe = TemperatureProbe::instance();

    if(!screen.getSelectorEditable()) {
        screen.moveSelectorDown();
        screen.render();
    } else {
        switch(screen.getSelectorPosition()) {
            case 0: pt.setKp(modify<double>(pt.getKp(), -1.0, 0.0, 100.0)); break;
            case 1: pt.setKi(modify<double>(pt.getKi(), -1.0, 0.0, 100.0)); break;
            case 2: pt.setKd(modify<double>(pt.getKd(), -1.0, 0.0, 100.0)); break;
            case 3: pt.setMaxPower(modify<int>(pt.getMaxPower(), -1, 0, 0)); break;
            case 4: break;
            case 5: probe.setCalibrationPoint25(modify<long>(probe.getCalibrationPoint25(), -1l, 0l, 1023l)); break;
            case 6: probe.setCalibrationPoint75(modify<long>(probe.getCalibrationPoint75(), -1l, 0l, 1023l)); break;
            case 7: st.toggle(); break;
            case 8:
                switch(st.getBaud()) {
                    case 1200l:   st.setBaud(1200l); break;
                    case 2400l:   st.setBaud(1200l); break;
                    case 4800l:   st.setBaud(2400l); break;
                    case 9600l:   st.setBaud(4800l); break;
                    case 19200l:  st.setBaud(9600l); break;
                    case 38400l:  st.setBaud(19200l); break;
                    case 57600l:  st.setBaud(38400l); break;
                    case 115200l: st.setBaud(57600l); break;
                    default:      st.setBaud(9600l); break;
                }
                break;
        }
        screen.renderMenuItem(screen.getSelectorPosition());
    }
}

void MenuScreenController::goRight() {
    static MenuScreen &screen = MenuScreen::instance();
    static SerialTask &st = SerialTask::instance();
    static PidTask &pt = PidTask::instance();
    static TemperatureProbe & probe = TemperatureProbe::instance();

    if(!screen.getSelectorEditable()) {
        screen.moveSelectorUp();
        screen.render();
    } else {
        switch(screen.getSelectorPosition()) {
            case 0: pt.setKp(modify<double>(pt.getKp(), 1.0, 0.0, 100.0)); break;
            case 1: pt.setKi(modify<double>(pt.getKi(), 1.0, 0.0, 100.0)); break;
            case 2: pt.setKd(modify<double>(pt.getKd(), 1.0, 0.0, 100.0)); break;
            case 3: pt.setMaxPower(modify<int>(pt.getMaxPower(), 1, 0, 0)); break;
            case 4: break;
            case 5: probe.setCalibrationPoint25(modify<long>(probe.getCalibrationPoint25(), 1l, 0l, 1023l)); break;
            case 6: probe.setCalibrationPoint75(modify<long>(probe.getCalibrationPoint75(), 1l, 0l, 1023l)); break;
            case 7: st.toggle(); break;
            case 8:
                switch(st.getBaud()) {
                    case 1200l:   st.setBaud(2400l); break;
                    case 2400l:   st.setBaud(4800l); break;
                    case 4800l:   st.setBaud(9600l); break;
                    case 9600l:   st.setBaud(19200l); break;
                    case 19200l:  st.setBaud(38400l); break;
                    case 38400l:  st.setBaud(57600l); break;
                    case 57600l:  st.setBaud(115200l); break;
                    case 115200l: st.setBaud(115200l); break;
                    default:      st.setBaud(9600l); break;
                }
                break;
        }
        screen.renderMenuItem(screen.getSelectorPosition());
    }
}

void MenuScreenController::click() {
    static MenuScreen &screen = MenuScreen::instance();
    if(screen.getSelectorPosition() == 9) {
        Config::save();
    } else {
        if(screen.getSelectorEditable()) {
            screen.setSelectorEditable(false);
        } else {
            screen.setSelectorEditable(true);
        }
        screen.renderSelector();
    }
}

/*
 * Helper functions
 */
template<typename T> T modify(T value, T delta, T min, T max) {
    value += delta;
    if(value < min) {
        return min;
    }
    if(value > max) {
        return max;
    }
    return value;
}