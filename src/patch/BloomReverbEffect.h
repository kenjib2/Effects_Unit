#include "../../Patch.h"
#include "../freeverb/revmodel.hpp"


class BloomReverbEffect : public Effect {
public:
    BloomReverbEffect();
    ~BloomReverbEffect() override;
    void processEffect(int16_t* effectBuffer) override;

private:
    revmodel* revModel;
    revmodel* bloomRevModel;

    float reverbWet; // 0.0 to 1.0
    float reverbDry; // 0.0 to 1.0
};
