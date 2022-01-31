#include <Audio.h>
#include "patch.h"


class TemporalCollapseEffect: public Effect {
  public:
    TemporalCollapseEffect();
    void processEffect(int16_t * effectBuffer);
};
