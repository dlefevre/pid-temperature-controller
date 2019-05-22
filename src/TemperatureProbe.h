/*
 * Read analog values from the PT100 probe, smoothen out any noise and
 * manage the interpollation to degrees Celcius.
 */ 

#ifndef __TEMPERATUREPROBE_H__
#define __TEMPERATUREPROBE_H__

#include <IoAbstraction.h>
#include <Filter.h>
#include "Constants.h"

class TemperatureProbe : public Executable {
    public:
        static inline TemperatureProbe& instance() FORCE_INLINE;

        TemperatureProbe();
        long getTemperature();        // Return temperature in degrees Celcius * 1000
        int getUnfilteredRaw();      // Return raw unfiltered analog value.
        int getFilteredRaw();        // Return smoothed raw value.
        inline void exec() override FORCE_INLINE;
        
    private:
        int raw;                           // Raw analog value
        ExponentialFilter<long> smooth;    // First level of smoothing to filter out noise
};

TemperatureProbe& TemperatureProbe::instance() {
    static TemperatureProbe one;
    return one;
}

#endif
