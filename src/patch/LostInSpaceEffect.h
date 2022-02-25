#include <Audio.h>
#include "../../Patch.h"
#include "../freeverb/revmodel.hpp"
#include "../delay/delay.h"
#include "../chorus/MonoChorusEngine.h"
#include "../fx/Distortion.h"


class LostInSpaceEffect: public Effect {
  public:
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
    Delay* delayEffect;
    revmodel* revModel;

    float reverbWet; // 0.0 to 1.0
    float reverbDry; // 0.0 to 1.0
};
