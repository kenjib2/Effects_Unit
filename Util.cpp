#include <math.h>


float scaleLinToExp(int input, int rangeMin, int rangeMax) {
  float retVal = (float)(input - rangeMin) / (rangeMax - rangeMin);
  retVal = powf(retVal, 2);
  retVal = retVal * (rangeMax - rangeMin) + rangeMin;
  return retVal;
}
