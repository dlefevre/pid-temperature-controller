/*
 * Base class for LCD implementation
 */

#ifndef __ABSTRACTSCREEN_H__
#define __ABSTRACTSCREEN_H__

#include "Constants.h"
#include <LiquidCrystal.h>
#include <IoAbstraction.h>

class AbstractScreen : public Executable {
    public:
        AbstractScreen();
        virtual void render() = 0;
        inline void exec() override FORCE_INLINE;

        void setSelectorPosition(int);
        void setSelectorEditable(bool);
        int getSelectorPosition();
        bool getSelectorEditable();
        void moveSelectorUp();
        void moveSelectorDown();
        void renderSelector();

    protected:
        LiquidCrystal lcd;
        int selectorPosition;
        int selectorMax;
        bool selectorEditable;
        int firstVisibleLine;

        void setSelectorMax(int);
};

/*
 * Periodic rendering
 */
void AbstractScreen::exec() {
    render();
}

/* 
 * Helper functions for formatting
 */
char * fmtDec(int whole, int fraction);
char * fmtDec(long value);
char * fmtDec(double value);
char * fmtTime(int hours, int minutes, int seconds);
char * fmtTime(unsigned long time);
char * fmtWhole(int value);

#endif