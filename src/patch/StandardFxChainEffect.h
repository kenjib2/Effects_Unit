#include <Audio.h>
#include "../../patch.h"
#include "../freeverb/revmodel.hpp"
#include "../delay/Delay.h"
#include "../chorus/MonoChorusEngine.h"
#include "../fx/Distortion.h"


class StandardFxChainEffect : public Effect {
  public:
      StandardFxChainEffect();
    ~StandardFxChainEffect() override;
    void processEffect(int16_t * effectBuffer, Controls* controls) override;

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
