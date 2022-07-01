#include <Audio.h>
#include "../../patch.h"
#include "../delay/Delay.h"
#include "../fx/Distortion.h"
#include "../fx/BitCrusher.h"
#include "../freeverb/revmodel.hpp"
#include "../fx/CjFilter.h"


class TemporalCollapseWriteInsert : public WriteInsert {
protected:

public:
  Distortion* distortion;
  BitCrusher* bitCrusher;
  CjFilter* filter;
  revmodel* revModel;

  float paramSmooth = 0.f;
  float paramSmear = 0.f;
  float paramDrive = 0.f;
  float paramCrush = 0.f;

  TemporalCollapseWriteInsert();
  ~TemporalCollapseWriteInsert();

  int16_t processSample(int16_t sampleIn) override;
};


class TemporalCollapseEffect: public Effect {
  public:
    TemporalCollapseEffect();
    ~TemporalCollapseEffect();
    void processEffect(int16_t * effectBuffer, Controls* controls) override;

  private:
    Delay* delayEffect;
    TemporalCollapseWriteInsert* writeInsert;
};
