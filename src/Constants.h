/*
 * Hardcoded configuration values
 */

#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

// Analog pins
#define TEMPERATURE_PROBE_PIN A0
#define BUTTONS_PIN           A1
// Parameters for temperature probe smoothing
#define SMOOTHING_WEIGHTING_FACTOR 5
#define DEFAULT_VALUE 255L

// Digital pins for rotary encoder
#define ENCODER_S1  2
#define ENCODER_S2  3
#define ENCODER_KEY 4

// LCD pins
#define LCD_RS 5
#define LCD_EN 6
#define LCD_D4 7
#define LCD_D5 8
#define LCD_D6 9
#define LCD_D7 10

// Some magic macros
#define FORCE_INLINE __attribute__((always_inline))

// Default values for configuration
#define DEFAULT_PROBECALIBRATIONPOINT25 266
#define DEFAULT_PROBECALIBRATIONPOINT75 763
#define DEFAULT_PIDKp 2
#define DEFAULT_PIDKi 5
#define DEFAULT_PIDkd 1
#define DEFAULT_PIDMAXPOWER 75
#define DEFAULT_DIRECTMAXPOWER 75
#define DEFAULT_SERIALON true
#define DEFAULT_SERIALBAUD 115200L

#endif