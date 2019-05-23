/*
 * Alarm implementation
 */

#include "Alarm.h"

void Alarm::exec() {
    if(enabled) {
        if(time > 0) {
            --time;
        } else {
            tone(PIEZO_PIN, 3000, 700);
        }
    }
}