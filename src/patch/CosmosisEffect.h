#include "../../patch.h"
#include "../fx/Modulation.h"
#include "../delay/MultiTapDelay.h"


const int NUM_COSMOSIS_BUFFERS = 1;
const int NUM_COSMOSIS_TAPS = 1;


class CosmosisEffect : public Effect {
public:
    float paramDryLevel = 0.8f;
    float paramWetLevel = 0.8f;
    int primaryDelays[NUM_COSMOSIS_BUFFERS];  // Between 820 and 2050
    // Try feedback and reverse?

    CosmosisEffect();
    ~CosmosisEffect() override;
    void processEffect(int16_t* effectBuffer) override;

private:
    MultiTapDelay* delayBuffer[NUM_COSMOSIS_BUFFERS];
    Modulation* delayModulation[NUM_COSMOSIS_BUFFERS];
};
