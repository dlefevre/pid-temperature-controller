/*
 * Manage serial data
 */

#include "SerialTask.h"
#include "Heater.h"
#include "PidTask.h"
#include "TemperatureProbe.h"

static char * format(long);
#ifdef MONITOR_RAM
static int freeRam();
#endif
static void setKp(CommandParameter &);
static void setKi(CommandParameter &);
static void setKd(CommandParameter &);
static void setMax(CommandParameter &);
static void setSetPoint(CommandParameter &);
static void setX0(CommandParameter &);
static void setX1(CommandParameter &);
static void setPidEnabled(CommandParameter &);
static void setPidDisabled(CommandParameter &);
static void setPidManual(CommandParameter &);
static void setPower(CommandParameter &);
static void save(CommandParameter &);

SerialTask & SerialTask::instance() {
    static SerialTask one;
    return one;
}

SerialTask::SerialTask() :
    enabled(Config::getSerialOn()),
    baud(Config::getSerialBaud()) {
    // Enable Serial communication
    if(enabled) {
        Serial.begin(baud);
    }

    // Set up command handler
    ch.AddCommand(F("kp"), setKp);
    ch.AddCommand(F("ki"), setKi);
    ch.AddCommand(F("kd"), setKd);
    ch.AddCommand(F("max"), setMax);
    ch.AddCommand(F("sp"), setSetPoint);
    ch.AddCommand(F("x0"), setX0);
    ch.AddCommand(F("x1"), setX1);
    ch.AddCommand(F("pe"), setPidEnabled);
    ch.AddCommand(F("pd"), setPidDisabled);
    ch.AddCommand(F("pm"), setPidManual);
    ch.AddCommand(F("pow"), setPower);
    ch.AddCommand(F("save"), save);
}

/*
 * Print plotter data
 */
void SerialTask::printPlotterData() {
    static Heater & heater = Heater::instance();
    static PidTask & pt = PidTask::instance();
    static TemperatureProbe & probe = TemperatureProbe::instance();
    static int count = -1;

    count = (count + 1) % 20;

    Serial.print(F("{\"t\":"));
    Serial.print(millis());
    Serial.print(F(","));
    if(!count)
        Serial.print(F("\"ng\":2,\"lu\":1,"));
    Serial.print(F("\"g\":[{"));
    if(!count)
        Serial.print(F("\"t\":\"Temperature\",\"xvy\":0,\"pd\":1000,\"sz\":2,\"l\":[\"Setpoint\",\"Temperature\"],\"c\":[\"green\",\"orange\"],"));
    Serial.print(F("\"d\":["));
    Serial.print(format(pt.getSetPoint()));
    Serial.print(F(","));
    Serial.print(format(probe.getTemperature()));
    Serial.print(F("]},{"));
    if(!count)
        Serial.print(F("\"t\":\"Heat output\",\"xvy\":0,\"pd\":1000,\"sz\":2,\"l\":[\"Power\",\"Maximum power\"],\"c\":[\"green\",\"orange\"],"));
    Serial.print(F("\"d\":["));
    Serial.print(format(heater.getPower()));
    Serial.print(F(","));
    Serial.print(pt.getMaxPower());
    Serial.println(F(".00000000]}]}#"));
}

/*
 * Scheduled loop.
 */
void SerialTask::exec() {
    if(enabled) {
        printPlotterData();
#ifdef MONITOR_RAM
        Serial.print(F("Available SRAM: "));
        Serial.println(freeRam());
#endif
    }
    ch.Process();
}

/*
 * Turn the serial communication on and off
 */
void SerialTask::toggle() {
    Config::setSerialOn(enabled);
    if(enabled) {
        Serial.end();
    } else {
        Serial.begin(baud);
    }
    enabled = !enabled;
}

/*
 * Helper functions
 */
static char * format(long value) {
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

#ifdef MONITOR_RAM
static int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}
#endif

static void setKp(CommandParameter &p) {
    PidTask &pid = PidTask::instance();
    pid.setKp((double)p.NextParameterAsLong((long)pid.getKp() * 1000l) / 1000.0);
}

static void setKi(CommandParameter &p) {
    PidTask &pid = PidTask::instance();
    pid.setKi((double)p.NextParameterAsLong((long)pid.getKi() * 1000l) / 1000.0);
}

static void setKd(CommandParameter &p) {
    PidTask &pid = PidTask::instance();
    pid.setKd((double)p.NextParameterAsLong((long)pid.getKd() * 1000l) / 1000.0);
}

static void setMax(CommandParameter &p) {
    PidTask &pid = PidTask::instance();
    pid.setMaxPower((int)(p.NextParameterAsLong((long)pid.getMaxPower() * 1000) / 1000l));
}

static void setSetPoint(CommandParameter &p) {
    PidTask &pid = PidTask::instance();
    pid.setSetPoint(p.NextParameterAsLong(pid.getSetPoint()));
}

static void setX0(CommandParameter &p) {
    TemperatureProbe &probe = TemperatureProbe::instance();
    probe.setCalibrationPoint25(p.NextParameterAsLong(probe.getCalibrationPoint25()));
}

static void setX1(CommandParameter &p) {
    TemperatureProbe &probe = TemperatureProbe::instance();
    probe.setCalibrationPoint75(p.NextParameterAsLong(probe.getCalibrationPoint75()));
}

static void setPidEnabled(CommandParameter &p) {
    PidTask &pt = PidTask::instance();
    if(!pt.isActive()) {
        pt.toggle();
    }
}

static void setPidDisabled(CommandParameter &p) {
    PidTask &pt = PidTask::instance();
    Heater &heater = Heater::instance();
    if(pt.isActive()) {
        pt.toggle();
    } else if(heater.isActive()) {
        heater.setActive(false);
    }
}

static void setPidManual(CommandParameter &p) {
    Heater &heater = Heater::instance();
    setPidDisabled(p);
    heater.setActive(true); // setPidDisabled implicitly disables the heater as well.
}

static void setPower(CommandParameter &p) {
    Heater &heater = Heater::instance();
    int frame = (int)HEATING_WINDOW;
    int duration = p.NextParameterAsLong(0l) * frame / 100000l;
    heater.setDuration(duration, frame);
}

static void save(CommandParameter &p) {
    Config::save();
}