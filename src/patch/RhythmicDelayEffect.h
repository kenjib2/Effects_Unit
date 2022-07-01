#include "../../patch.h"
#include "../delay/MultiTapDelay.h"


class RhythmicDelayEffect : public Effect {
public:
    bool reverse = false;
    float level = 0.2;
    float feedback = 0.2;
    int primaryDelay = 12000;

    RhythmicDelayEffect();
    ~RhythmicDelayEffect() override;
    void processEffect(int16_t* effectBuffer, Controls* controls) override;

private:
    MultiTapDelay* delayEffect;
};
