/*
 * Manage serial data
 */

#include "SerialTask.h"
#include "Heater.h"
#include "PidTask.h"
#include "TemperatureProbe.h"

char * format(long);

SerialTask & SerialTask::instance() {
    static SerialTask one;
    return one;
}

SerialTask::SerialTask() :
    enabled(Config::getSerialOn()),
    baud(Config::getSerialBaud()) {
    if(enabled) {
        Serial.begin(baud);
    }
}

/*
 * Scheduled loop.
 */
void SerialTask::exec() {
    static Heater & heater = Heater::instance();
    static PidTask & pt = PidTask::instance();
    static TemperatureProbe & probe = TemperatureProbe::instance();
    static int count = -1;
    
    if(enabled) {
        setPoint = pt.getSetPoint();
        temperature = probe.getTemperature();
        power = heater.getPower();
        maxPower = pt.getMaxPower();

        count = (count + 1) % 20;

        Serial.print("{\"t\":");
        Serial.print(millis());
        Serial.print(",");
        if(!count)
            Serial.print("\"ng\":2,\"lu\":1,");
        Serial.print("\"g\":[{");
        if(!count)
            Serial.print("\"t\":\"Temperature\",\"xvy\":0,\"pd\":1000,\"sz\":2,\"l\":[\"Setpoint\",\"Temperature\"],\"c\":[\"green\",\"orange\"],");
        Serial.print("\"d\":[");
        Serial.print(format(pt.getSetPoint()));
        Serial.print(",");
        Serial.print(format(probe.getTemperature()));
        Serial.print("]},{");
        if(!count)
            Serial.print("\"t\":\"Heat output\",\"xvy\":0,\"pd\":1000,\"sz\":2,\"l\":[\"Power\",\"Maximum power\"],\"c\":[\"green\",\"orange\"],");
        Serial.print("\"d\":[");
        Serial.print(format(heater.getPower()));
        Serial.print(",");
        Serial.print(pt.getMaxPower());
        Serial.println(".00000000]}]}#");
    }
}

/*
 * Turn the serial communication on and off
 */
void SerialTask::toggle() {
    if(enabled) {
        Serial.end();
    } else {
        Serial.begin(baud);
    }
    enabled = !enabled;
    Config::setSerialOn(enabled);
}

/*
 * Helper functions
 */
char * format(long value) {
    static char buffer[15];
    int whole = value / 1000;
    int fraction = value % 1000;

    // Determine whole part (reversed)
    char *tmp = buffer + 5;
    char *rev = tmp;
    do {
        *(++rev) = whole % 10 + '0';
        whole /= 10;
    } while(whole > 0);

    // Reverse 
    char *ptr = buffer;
    do {
        *(ptr++) = *(rev--);
    } while(rev != tmp);

    // Add fraction
    *(ptr++) = '.';
    *(ptr++) = fraction / 100 + '0';
    *(ptr++) = fraction % 100 / 10 + '0';
    *(ptr++) = fraction % 10 + '0';
    for(int i=0; i<5; ++i)
        *(ptr++) = '0';


    *ptr = '\0';
    return buffer;
}

void printTempConfig() {

}

void printPowerConfig() {

}

void printGlobalConfig() {
    Serial.print("\"ng\":2,\"lu\":1,");
}