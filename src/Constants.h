/*
 * Hardcoded configuration values
 */

#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

// Temperature pin
#define TEMPERATURE_PROBE_PIN A0

// Parameters for analog buttons
#define BUTTONS_PIN     A1
#define BUTTONS_DBFM    2
#define BUTTONS_MARGIN  25
#define BUTTONS_VALUE_1 1023
#define BUTTONS_VALUE_2 849
#define BUTTONS_VALUE_3 714
#define BUTTONS_VALUE_4 615

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

// Other pins
#define HEATER_PIN 11
#define ACTIVE_PIN 12
#define PIEZO_PIN 13

// Some magic macros
#define FORCE_INLINE __attribute__((always_inline))

// Default values for configuration
#define DEFAULT_PROBECALIBRATIONPOINT25 271
#define DEFAULT_PROBECALIBRATIONPOINT75 769
#define DEFAULT_PIDKp 2
#define DEFAULT_PIDKi 5
#define DEFAULT_PIDkd 1
#define DEFAULT_PIDMAXPOWER 80
#define DEFAULT_SERIALON true
#define DEFAULT_SERIALBAUD 115200L

// Heating window
#define HEATING_WINDOW 2000

// Minimal screen refresh timeout
#define SCREEN_REFRESH 500

#endif