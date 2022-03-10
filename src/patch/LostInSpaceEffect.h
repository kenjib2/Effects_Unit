#include <Audio.h>
#include "../../Patch.h"
#include "../freeverb/revmodel.hpp"
#include "../delay/Delay.h"
#include "../delay/MultiTapDelay.h"
#include "../chorus/MonoChorusEngine.h"
#include "../fx/Distortion.h"
#include "../fx/PitchShift.h"


class LostInSpaceEffect: public Effect {
  public:
    int primaryDelay;
    float delayLevel;
    LostInSpaceEffect();
    ~LostInSpaceEffect() override;
    void processEffect(int16_t * effectBuffer) override;

  private:
    bool distortion;
    bool chorus;
    bool delay;
    bool reverb;
    Distortion* distortionEffect;
    MonoChorusEngine* chorusEngine;
    MultiTapDelay* shortReflections;
    MultiTapDelay* longReflections;
    Delay* shimmerDelay;
    revmodel* revModel;
    revmodel* bloomRevModel;
    PitchShift* shimmerPitch;

    float reverbWet; // 0.0 to 1.0
    float reverbDry; // 0.0 to 1.0
};
