/*
 * Configuration management and persistence
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "Constants.h"

class Config {
    public:
        static int getProbeCalibrationPoint25();
        static int getProbeCalibrationPoint75();
        static double getPidKp();
        static double getPidKi();
        static double getPidKd();
        static int getPidMaxPower();
        static int getDirectMaxPower();
        static bool getSerialOn();
        static long getSerialBaud();

        static void setProbeCalibrationPoint25(int);
        static void setprobeCalibrationPoint75(int);
        static void setPidKp(double);
        static void setPidKi(double);
        static void setPidKd(double);
        static void setPidMaxPower(int);
        static void setDirectMaxPower(int);
        static void setSerialOn(bool);
        static void setSerialBaud(long); 

    private:
        static void save();
        static void load();
        static void initialize();
        static void verify();

        static int probeCalibrationPoint25;
        static int probeCalibrationPoint75;
        static double pidKp;
        static double pidKi;
        static double pidKd;
        static int pidMaxPower;
        static int directMaxPower;
        static bool serialOn;
        static long serialBaud;

        static bool loaded;
        static bool initialized;
};

#endif