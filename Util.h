#ifndef UTIL_H
#define UTIL_H


#include "Arduino.h"
#include <math.h>


unsigned const int DEBOUNCE_DELAY = 50;
const float EPSILON = 0.000001;

float scaleLinToExp(int input, int rangeMin, int rangeMax); 
int16_t linearInterpolation(int16_t* buffer, int bufferSize, float floatIndex);


#endif // #ifdef UTIL_H