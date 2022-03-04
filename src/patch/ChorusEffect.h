#ifndef CHORUS_EFFECT_H
#define CHORUS_EFFECT_H


#include "../../patch.h"
#include "../fx/Modulation.h"
#include "../delay/Delay.h"


const int NUM_CHORUS_BUFFERS = 4;
const int CHORUS_LFO_WAVEFORM = 0;
const int MAX_CHORUS_DELAY = 2500;


class ChorusEffect : public Effect {
public:
    int delayLengths[NUM_CHORUS_BUFFERS];  // Between 820 and 2050
    float delayLevels[NUM_CHORUS_BUFFERS];  // Between 0.f and 1.f
    float delayRates[NUM_CHORUS_BUFFERS];  // In Hz
    float delayDepths[NUM_CHORUS_BUFFERS];  // Between 0.f and 1.f

    ChorusEffect();
    ~ChorusEffect() override;
    void processEffect(int16_t* effectBuffer) override;

private:
    Delay* delayBuffer[NUM_CHORUS_BUFFERS];
    Modulation* delayModulation[NUM_CHORUS_BUFFERS];
};


#endif	// #ifndef CHORUS_EFFECT_H