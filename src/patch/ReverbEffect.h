#include "../../Patch.h"
#include "../freeverb/revmodel.hpp"
#include "../delay/MultiTapDelay.h"


class ReverbEffect : public Effect {
public:
    ReverbEffect();
    ~ReverbEffect() override;
    void processEffect(int16_t* effectBuffer) override;

private:
    revmodel* revModel;
    revmodel* bloomRevModel;

    float reverbWet; // 0.0 to 1.0
    float reverbDry; // 0.0 to 1.0
};
