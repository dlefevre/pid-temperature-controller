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
int Config::directMaxPower;
bool Config::serialOn;
long Config::serialBaud;

/*
 * Save changes to EEPROM
 */
void Config::save() {

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
    directMaxPower            = EEPROM.readInt(address);    address += sizeof(int);
    
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
    directMaxPower = DEFAULT_DIRECTMAXPOWER;
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

int Config::getDirectMaxPower() {
    verify();
    return directMaxPower;
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
    save();
}

void Config::setprobeCalibrationPoint75(int value) {
    probeCalibrationPoint75 = value;
    save();
}

void Config::setPidKp(double value) {
    pidKp = value;
    save();
}

void Config::setPidKi(double value) {
    pidKi = value;
    save();
}

void Config::setPidKd(double value) {
    pidKd = value;
    save();
}

void Config::setPidMaxPower(int value) {
    pidMaxPower = value;
    save();
}

void Config::setDirectMaxPower(int value) {
    directMaxPower = value;
    save();
}

void Config::setSerialOn(bool value) {
    serialOn = value;
    save();
}

void Config::setSerialBaud(long value) { 
    serialBaud = value;
    save();
}
