/*
 * Extends on the AnalogButtons library to manage the four buttons on the box.
 */

#ifndef __BUTTONS_H__
#define __BUTTONS_H__

#include "Constants.h"
#include <IoAbstraction.h>
#include "AnalogButtons.h"
#include "Config.h"

class Buttons : public AnalogButtons, public Executable {
    public:
        static inline Buttons & instance() FORCE_INLINE;
        Buttons();

        inline void exec() override FORCE_INLINE;

    private:
        Button button1;
        Button button2;
        Button button3;
        Button button4;
};

Buttons & Buttons::instance() {
    static Buttons one;
    return one;
}

#endif