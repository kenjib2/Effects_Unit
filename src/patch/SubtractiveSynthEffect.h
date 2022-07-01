#include <Audio.h>
#include "../../patch.h"


class SubtractiveSynthEffect: public Effect {
  public:
    SubtractiveSynthEffect();
    void processEffect(int16_t * effectBuffer, Controls* controls) override;
};
