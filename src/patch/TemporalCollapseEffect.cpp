#include "TemporalCollapseEffect.h"


TemporalCollapseEffect::TemporalCollapseEffect() {
  usesSynthMidi = false;

  setEffectName("Temporal Collapse");
  
  numButtons = 2;
  setButtonLabel(0, "Buff");
  setButtonLabel(1, "Rvrs");

  numKnobs = 12;
  setKnobLabel(0, "Dry");
  setKnobLabel(1, "Wet");
  setKnobLabel(2, "Sens");
  setKnobLabel(3, "Ltch");
  setKnobLabel(4, "Time");
  setKnobLabel(5, "Feed");
  setKnobLabel(6, "Drft");
  setKnobLabel(7, "Ltch");
  setKnobLabel(8, "Smth");
  setKnobLabel(9, "Smr");
  setKnobLabel(10, "Driv");
  setKnobLabel(11, "Crsh");

  numSwitches = 2;
  setSwitchLabel(0, "Ltch");
  setSwitchLabel(1, "Tmpo");

  delayEffect = new Delay();
  delayEffect->setDelayLength(30000);
  delayEffect->paramReverse = false;
  delayEffect->paramDry = 1.0;
  delayEffect->paramWet = 0.6;
  delayEffect->paramFeedback = 0.4;
  delayEffect->setLoopLatch(0.5);
//  delayEffect->paramSensitivity = 30000;

  bitCrusherEffect = new BitCrusher();
}

TemporalCollapseEffect::~TemporalCollapseEffect() {
    delete delayEffect;
}

void TemporalCollapseEffect::processEffect(int16_t * effectBuffer) {
  for (int i = 0; i < 128; i++) {
    int16_t nextSample = effectBuffer[i];

    nextSample = delayEffect->processSample(nextSample);
//    nextSample = bitCrusherEffect->process(nextSample, 14.f, 16.f);

    effectBuffer[i] = nextSample;
  }
}
