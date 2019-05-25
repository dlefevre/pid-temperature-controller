/*
 * Read analog values from the PT100 probe, smoothen out any noise and
 * manage the interpollation to degrees Celcius.
 */ 

#ifndef __TEMPERATUREPROBE_H__
#define __TEMPERATUREPROBE_H__

#include "Constants.h"
#include <IoAbstraction.h>
#include <Filter.h>

class TemperatureProbe : public Executable {
    public:
        static inline TemperatureProbe& instance() FORCE_INLINE;

        TemperatureProbe();
        long getTemperature();        // Return temperature in degrees Celcius * 1000
        int getUnfilteredRaw();      // Return raw unfiltered analog value.
        int getFilteredRaw();        // Return smoothed raw value.
        inline void exec() override FORCE_INLINE;
        inline long getCalibrationPoint25() FORCE_INLINE;
        inline long getCalibrationPoint75() FORCE_INLINE;
        void setCalibrationPoint25(long);
        void setCalibrationPoint75(long);
        
    private:
        int raw;                           // Raw analog value
        ExponentialFilter<long> smooth;    // First level of smoothing to filter out noise
        long x0, x1;
};

TemperatureProbe& TemperatureProbe::instance() {
    static TemperatureProbe one;
    return one;
}

long TemperatureProbe::getCalibrationPoint25() {
    return x0;
}

long TemperatureProbe::getCalibrationPoint75() {
    return x1;
}

#endif
