#include "../../patch.h"
#include "../delay/MultiTapDelay.h"


class RepeaterEffect : public Effect {
public:
    RepeaterEffect();
    ~RepeaterEffect() override;
    void processEffect(int16_t* effectBuffer, Controls* controls) override;
    int repeatLength;
    int repeatMin;
    int repeatMax;

private:
    MultiTapDelay* delayEffect;
};
