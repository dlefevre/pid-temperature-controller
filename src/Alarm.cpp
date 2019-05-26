/*
 * Alarm implementation
 */

#include "Alarm.h"

/*
 * Get the sole instance
 */
Alarm & Alarm::instance() {
    static Alarm one;
    return one;
}

/*
 * Scheduled loop
 */
void Alarm::exec() {
    if(enabled) {
        if(time > 0) {
            --time;
        } else {
            tone(PIEZO_PIN, 3000, 700);
        }
    }
}