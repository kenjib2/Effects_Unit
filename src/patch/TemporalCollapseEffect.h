#include <Audio.h>
#include "../../patch.h"
#include "../delay/Delay.h"
#include "../fx/BitCrusher.h"


class TemporalCollapseEffect: public Effect {
  public:
    TemporalCollapseEffect();
    ~TemporalCollapseEffect();
    void processEffect(int16_t * effectBuffer) override;

  private:
    Delay* delayEffect;
    BitCrusher* bitCrusherEffect;
};
