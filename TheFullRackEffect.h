#include <Audio.h>
#include "patch.h"
#include "revmodel.hpp"


class TheFullRackEffect: public Effect {
  public:
    TheFullRackEffect();
    void processEffect(int16_t * effectBuffer);

  private:
    bool distortion;
    bool chorus;
    bool delay;
    bool reverb;
    revmodel* revModel;
    
    float gain; // Range from 0.0 to 10.0
    int level; // Range from 0 to 127

    float reverbWet; // 0.0 to 1.0
    float reverbDry; // 0.0 to 1.0
};
