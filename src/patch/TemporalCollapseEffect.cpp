#include "TemporalCollapseEffect.h"


TemporalCollapseEffect::TemporalCollapseEffect() {
  usesSynthMidi = false;

  setEffectName("Temporal Collapse");
  
  numButtons = 2;
  setButtonLabel(0, "Buff");
  setButtonLabel(1, "Dir");

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
}

void TemporalCollapseEffect::processEffect(int16_t * effectBuffer) {
  for (int i = 0; i < 128; i++) {
    int16_t nextVoltage = effectBuffer[i];

    float saturatedVoltage = (float)nextVoltage / 32768.0 * 10.0;

    saturatedVoltage = (2.f / PI) * atan(saturatedVoltage);

    nextVoltage = (int)(saturatedVoltage * 32768 / 2);
    
    effectBuffer[i] = nextVoltage;
  }
}
