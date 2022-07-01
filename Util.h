#ifndef UTIL_H
#define UTIL_H


#include "Arduino.h"
#include <math.h>
#include <LittleFS.h>


const float EPSILON = 0.000001;

float scaleLinToExp(int input, int rangeMin, int rangeMax); 
int16_t linearInterpolation(int16_t* buffer, int bufferSize, float floatIndex);
void printDirectory(LittleFS_QSPIFlash &fs);


#endif // #ifdef UTIL_H
