/*
 * Read analog values from the PT100 probe, smoothen out any noise and
 * manage the interpollation to degrees Celcius.
 */ 

#include "TemperatureProbe.h"

#include "Config.h"

/*
 * Constructor, sets the pin
 */
TemperatureProbe::TemperatureProbe() : 
  raw(DEFAULT_VALUE),
  smooth(SMOOTHING_WEIGHTING_FACTOR, DEFAULT_VALUE * 1000) {
}

/*
 * Main loop for scheduler
 */
void TemperatureProbe::exec() {
    raw = analogRead(TEMPERATURE_PROBE_PIN);
    smooth.Filter(raw);
}

/*
 * Return interpollated temperature value (degrees celcius * 1000)
 */
long TemperatureProbe::getTemperature() {
    long x0 = (long)Config::getProbeCalibrationPoint25();
    long x1 = (long)Config::getProbeCalibrationPoint75();
    long x  = (long)smooth.Current();

    return (25000L * (x1 - x) + 75000L * (x - x0)) / (x1 - x0);
}

/*
 * Return the unsmoothed raw analog value
 */
int TemperatureProbe::getUnfilteredRaw() {
    return raw;
}

/*
 * Return the smoothed raw analog value
 */
int TemperatureProbe::getFilteredRaw() {
    return smooth.Current();
}
