#include "../../patch.h"
#include "../fx/Modulation.h"
#include "../delay/MultiTapDelay.h"


const int NUM_COSMOSIS_BUFFERS = 3;
const int NUM_COSMOSIS_TAPS = 0;
const int COSMOSIS_LFO_WAVEFORM = 0;
const int MAX_COSMOSIS_DELAY = 8000;


class CosmosisEffect : public Effect {
public:
    float paramDryLevel = 1.f;
    float paramWetLevel = 1.f;
    int primaryDelays[NUM_COSMOSIS_BUFFERS];  // Between 820 and 2050

    CosmosisEffect();
    ~CosmosisEffect() override;
    void processEffect(int16_t* effectBuffer) override;

private:
    MultiTapDelay* delayBuffer[NUM_COSMOSIS_BUFFERS];
    Modulation* delayModulation[NUM_COSMOSIS_BUFFERS];
};
