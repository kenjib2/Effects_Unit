#ifndef TEENSY_PINS_H
#define TEENSY_PINS_H


#include "Arduino.h"


// Rotary Encoder
const int PIN_ENCODER_A = 27;
const int PIN_ENCODER_B = 28;
const int PIN_ENCODER_CLICK = 29;

// Buttons
const int PIN_BUTTON_BLUE = 30;
const int PIN_BUTTON_RED = 31;
const int PIN_BUTTON_YELLOW = 32;
const int PIN_BUTTON_GREEN = 33;


// Analog Multiplexer for knobs
const int PIN_MULTI_E = 36;
const int PIN_MULTI_S0 = 37;
const int PIN_MULTI_S1 = 38;
const int PIN_MULTI_S2 = 39;
const int PIN_MULTI_S3 = 40;
const int PIN_MULTI_SIG = A17;


// TFT Display
const int PIN_DISPLAY_CLK = 13;
const int PIN_DISPLAY_MOSI = 11;
const int PIN_DISPLAY_DC = 24;
const int PIN_DISPLAY_RST = 25;
const int PIN_DISPLAY_CS = 26;

// Random Seed
const int PIN_RANDOM_SEED = A0;


#endif // #ifndef TEENSY_PINS_H
