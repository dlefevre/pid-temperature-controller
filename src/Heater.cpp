/*
 * Heater driver
 */

#include "Heater.h"

#include "Config.h"

/*
 * Return the sole instance
 */
Heater & Heater::instance() {
    static Heater one;
    return one;
}

/*
 * Constructor
 */
Heater::Heater() {
    pinMode(HEATER_PIN, OUTPUT);
}

/*
 * Schedulers main loop;
 */
void Heater::exec() {
    if(active) {
        int pos = millis() % frame;
        if(pos < duration) {
            PORTB = PORTB | B10000000;
        } else {
            PORTB = PORTB & B01111111;
        }
    } else {
        PORTB = PORTB & B01111111;
    }
}

/*
 * Calculate and return the total power
 */
long Heater::getPower() {
    return (long)duration * 100000 / frame;
}