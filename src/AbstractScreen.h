/*
 * Base class for LCD implementation
 */

#ifndef __ABSTRACTSCREEN_H__
#define __ABSTRACTSCREEN_H__

#include <LiquidCrystal.h>
#include <IoAbstraction.h>
#include "Constants.h"

class AbstractScreen : public Executable {
    public:
        AbstractScreen();
        virtual void render();
        inline void exec() override FORCE_INLINE;

        void setSelectorPosition(int);
        void setSelectorEditable(bool);
        int getSelectorPosition();
        bool getSelectorEditable();
        void moveSelectorUp();
        void moveSelectorDown();

    protected:
        LiquidCrystal lcd;
        int selectorPosition;
        int selectorMax;
        bool selectorEditable;

        char * fmtDec(int whole, int fraction);
        char * fmtDec(long value);
        char * fmtTime(int hours, int minutes, int seconds);
        char * fmtTime(long time);

        void setSelectorMax(int);
    
    private:
        char buf[21];
};

/*
 * Periodic rendering
 */
void AbstractScreen::exec() {
    render();
}

#endif