#include "../../patch.h"
#include "../delay/MultiTapDelay.h"


class RepeaterEffect : public Effect {
public:
    RepeaterEffect();
    ~RepeaterEffect() override;
    void processEffect(int16_t* effectBuffer) override;
    int repeatLength;

private:
    MultiTapDelay* delayEffect;
};
