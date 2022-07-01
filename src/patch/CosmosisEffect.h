#include "../../patch.h"
#include "../fx/Modulation.h"
#include "../delay/Delay.h"


const int NUM_COSMOSIS_BUFFERS = 3;
const int COSMOSIS_LFO_WAVEFORM = 0;
const int MAX_COSMOSIS_DELAY = 8000;


class CosmosisEffect : public Effect {
public:
    float paramDryLevel = 1.f;
    float paramWetLevel = 1.f;
    int delayLengths[NUM_COSMOSIS_BUFFERS];  // Between 820 and 2050

    CosmosisEffect();
    ~CosmosisEffect() override;
    void processEffect(int16_t* effectBuffer, Controls* controls) override;

private:
    Delay* delayBuffer[NUM_COSMOSIS_BUFFERS];
    Modulation* delayModulation[NUM_COSMOSIS_BUFFERS];
};
