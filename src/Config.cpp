/*
 * Configuration management and persistence
 */

#include "Config.h"

#include <EEPROMex.h> 

byte expectedId[3] = {'P', 'I', 'D'};

bool Config::loaded = false;
bool Config::initialized = false;
int Config::probeCalibrationPoint25;
int Config::probeCalibrationPoint75;
double Config::pidKp;
double Config::pidKi;
double Config::pidKd;
int Config::pidMaxPower;
bool Config::serialOn;
long Config::serialBaud;

/*
 * Save changes to EEPROM
 */
void Config::save() {
    int address = 0;

    for(int i=0; i<3; ++i) {
        EEPROM.updateByte(address++, expectedId[i]);
    }

    EEPROM.updateByte(address++, (byte)serialOn);
    EEPROM.updateLong(address, serialBaud);             address += sizeof(long);
    EEPROM.updateInt(address, probeCalibrationPoint25); address += sizeof(int);   
    EEPROM.updateDouble(address, pidKp);                address += sizeof(double); 
    EEPROM.updateDouble(address, pidKi);                address += sizeof(double); 
    EEPROM.updateDouble(address, pidKd);                address += sizeof(double); 
    EEPROM.updateInt(address, pidMaxPower);             address += sizeof(int);
}

/*
 * Load from EEPROM
 */
void Config::load() {
    int address = 0;
    
    initialized = true;
    for(int i=0; i<3; ++i) {
        int b = EEPROM.readByte(address++);
        initialized = initialized && expectedId[i] == b;
    }
    
    serialOn   = (bool)EEPROM.readByte(address++);
    serialBaud = EEPROM.readLong(address);
    address += sizeof(long);
    
    probeCalibrationPoint25 = EEPROM.readInt(address);    address += sizeof(int);   
    probeCalibrationPoint75 = EEPROM.readInt(address);    address += sizeof(int);
    pidKp                   = EEPROM.readDouble(address); address += sizeof(double); 
    pidKi                   = EEPROM.readDouble(address); address += sizeof(double); 
    pidKd                   = EEPROM.readDouble(address); address += sizeof(double);
    pidMaxPower             = EEPROM.readInt(address);    address += sizeof(int);
    
    loaded = true;
}

/*
 * Initialize configuration variables
 */
void Config::initialize() {
    probeCalibrationPoint25 = DEFAULT_PROBECALIBRATIONPOINT25;
    probeCalibrationPoint75 = DEFAULT_PROBECALIBRATIONPOINT75;
    pidKp = DEFAULT_PIDKp;
    pidKi = DEFAULT_PIDKi;
    pidKd = DEFAULT_PIDkd;
    pidMaxPower = DEFAULT_PIDMAXPOWER;
    serialOn = DEFAULT_SERIALON;
    serialBaud = DEFAULT_SERIALBAUD;

    initialized = true;
}

/*
 * Trigger a load if necessary.
 */
void Config::verify() {
    if(initialized) {
        return;
    }
    if(!loaded) {
        load();
    }
    if(!initialized) {
        initialize();
    }
}

int Config::getProbeCalibrationPoint25() {
    verify();
    return probeCalibrationPoint25;
}

int Config::getProbeCalibrationPoint75() {
    verify();
    return probeCalibrationPoint75;
}

double Config::getPidKp() {
    verify();
    return pidKp;
}

double Config::getPidKi() {
    verify();
    return pidKi;
}

double Config::getPidKd() {
    verify();
    return pidKd;
}

int Config::getPidMaxPower() {
    verify();
    return pidMaxPower;
}

bool Config::getSerialOn() {
    verify();
    return serialOn;
}

long Config::getSerialBaud() {
    verify();
    return serialBaud;
}

void Config::setProbeCalibrationPoint25(int value) {
    probeCalibrationPoint25 = value;
}

void Config::setprobeCalibrationPoint75(int value) {
    probeCalibrationPoint75 = value;
}

void Config::setPidKp(double value) {
    pidKp = value;
}

void Config::setPidKi(double value) {
    pidKi = value;
}

void Config::setPidKd(double value) {
    pidKd = value;
}

void Config::setPidMaxPower(int value) {
    pidMaxPower = value;
}

void Config::setSerialOn(bool value) {
    serialOn = value;
}

void Config::setSerialBaud(long value) { 
    serialBaud = value;
}
