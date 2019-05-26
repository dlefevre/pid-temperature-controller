/*
 * Extends on the AnalogButtons library to manage the four buttons on the box.
 */

#include "Buttons.h"

#include "Controller.h"

void button1Pressed();
void button2Pressed();
void button3Pressed();
void button4Pressed();

/*
 * Return the sole instance
 */
Buttons & Buttons::instance() {
    static Buttons one;
    return one;
}

/*
 * Constructor 
 */
Buttons::Buttons() : 
    AnalogButtons(BUTTONS_PIN, INPUT, BUTTONS_DBFM, BUTTONS_MARGIN),
    button1(BUTTONS_VALUE_1, &button1Pressed),
    button2(BUTTONS_VALUE_2, &button2Pressed),
    button3(BUTTONS_VALUE_3, &button3Pressed),
    button4(BUTTONS_VALUE_4, &button4Pressed) {
    add(button1);
    add(button2);
    add(button3);
    add(button4);
}

/*
 * Loop for scheduler
 */
void Buttons::exec() {
    check();
}

/*
 * Helper functions for handlers
 */

void button1Pressed() {
    static Controller &controller = Controller::instance();
    controller.button1Pressed();
}

void button2Pressed() {
    static Controller &controller = Controller::instance();
    controller.button2Pressed();
}

void button3Pressed() {
    static Controller &controller = Controller::instance();
    controller.button3Pressed();
}

void button4Pressed() {
    static Controller &controller = Controller::instance();
    controller.button4Pressed();
}
