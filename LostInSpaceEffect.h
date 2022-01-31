#include <Audio.h>
#include "Patch.h"


class LostInSpaceEffect: public Effect {
  public:
    LostInSpaceEffect();
    void processEffect(int16_t * effectBuffer);
};
