#include <string.h>
#include "Patch.h"


void Effect::setEffectName(char * effectName) {
  // Truncate to a max of MAX_EFFECT_NAME_LENGTH null terminated characters
  effectName[MAX_EFFECT_NAME_LENGTH] = 0;
  memcpy(this->effectName, effectName, MAX_EFFECT_NAME_LENGTH);
}

void Effect::setButtonLabel(int buttonNumber, char * label) {
  if (buttonNumber < 0 || buttonNumber >= NUM_KNOBS) {
    return;
  }
  // Truncate to a max of CTRL_LABEL_LENGTH null terminated characters
  buttonLabels[buttonNumber][CTRL_LABEL_LENGTH] = 0;
  memcpy(buttonLabels[buttonNumber], label, CTRL_LABEL_LENGTH);
}

void Effect::setKnobLabel(int knobNumber, char * label) {
  if (knobNumber < 0 || knobNumber >= NUM_KNOBS) {
    return;
  }
  // Truncate to a max of CTRL_LABEL_LENGTH null terminated characters
  knobLabels[knobNumber][CTRL_LABEL_LENGTH] = 0;
  memcpy(knobLabels[knobNumber], label, CTRL_LABEL_LENGTH);
}

void Effect::setSwitchLabel(int switchNumber, char * label) {
  if (switchNumber < 0 || switchNumber >= NUM_SWITCHES) {
    return;
  }
  // Truncate to a max of CTRL_LABEL_LENGTH null terminated characters
  switchLabels[switchNumber][CTRL_LABEL_LENGTH] = 0;
  memcpy(switchLabels[switchNumber], label, CTRL_LABEL_LENGTH);
}

void Effect::processEffect(short * effectBuffer){} // To make it not inline and fix the vtable


BypassEffect::BypassEffect() {
  strcpy(effectName, "Bypass");
  usesSynthMidi = false;
  numButtons = 0;
  numKnobs = 0;
  numSwitches = 0;
}

void BypassEffect::processEffect(int16_t * effectBuffer) {
}


LostInSpaceEffect::LostInSpaceEffect() {
  strcpy(effectName, "Lost in Space");
  usesSynthMidi = false;
  
  numButtons = 1;
  char label[] = "1234";
  strcpy(label, "Dir"); // Delay forward or reverse
  setButtonLabel(0, label);

  numKnobs = 14;
  strcpy(label, "Dry");
  setKnobLabel(0, label);
  strcpy(label, "Wet");
  setKnobLabel(1, label);
  strcpy(label, "Size");
  setKnobLabel(2, label);
  strcpy(label, "Damp");
  setKnobLabel(3, label);
  strcpy(label, "Shrt");
  setKnobLabel(4, label);
  strcpy(label, "Time");
  setKnobLabel(5, label);
  strcpy(label, "Fdbk");
  setKnobLabel(6, label);
  strcpy(label, "Ptch");
  setKnobLabel(7, label);
  strcpy(label, "Long");
  setKnobLabel(8, label);
  strcpy(label, "Time");
  setKnobLabel(9, label);
  strcpy(label, "Fdbk");
  setKnobLabel(10, label);
  strcpy(label, "Ptch");
  setKnobLabel(11, label);
  strcpy(label, "Blm"); // Bloom
  setKnobLabel(12, label);
  strcpy(label, "Shim"); // Shimmer
  setKnobLabel(13, label);
  strcpy(label, "Driv"); // Drive
  setKnobLabel(14, label);

  numSwitches = 1;
  strcpy(label, "Hold"); // Increase decay
  setSwitchLabel(0, label);
}

void LostInSpaceEffect::processEffect(int16_t * effectBuffer) {
}


TemporalCollapseEffect::TemporalCollapseEffect() {
  strcpy(effectName, "Temporal Collapse");
  usesSynthMidi = false;
  
  numButtons = 2;
  char label[] = "1234";
  strcpy(label, "Buff");
  setButtonLabel(0, label);
  strcpy(label, "Dir");
  setButtonLabel(1, label);

  numKnobs = 12;
  strcpy(label, "Dry");
  setKnobLabel(0, label);
  strcpy(label, "Wet");
  setKnobLabel(1, label);
  strcpy(label, "Sens");
  setKnobLabel(2, label);
  strcpy(label, "Ltch");
  setKnobLabel(3, label);
  strcpy(label, "Time");
  setKnobLabel(4, label);
  strcpy(label, "Feed");
  setKnobLabel(5, label);
  strcpy(label, "Drft");
  setKnobLabel(6, label);
  strcpy(label, "Ltch");
  setKnobLabel(7, label);
  strcpy(label, "Smth");
  setKnobLabel(8, label);
  strcpy(label, "Smr");
  setKnobLabel(9, label);
  strcpy(label, "Driv");
  setKnobLabel(10, label);
  strcpy(label, "Crsh");
  setKnobLabel(11, label);

  numSwitches = 2;
  strcpy(label, "Ltch");
  setSwitchLabel(0, label);
  strcpy(label, "Tmpo");
  setSwitchLabel(1, label);
}

void TemporalCollapseEffect::processEffect(int16_t * effectBuffer) {
  Serial.println("Here");
  for (int i = 0; i < 128; i++) {
/*    int16_t nextVolume = effectBuffer[i];

    float saturatedVoltage = (float)nextVolume / 32768.0 * 10.0;

    saturatedVoltage = (2.f / PI) * atan(saturatedVoltage);

    nextVolume = (int)(saturatedVoltage * 32768);
    effectBuffer[i] = nextVolume;*/
    effectBuffer[i] /= 2;

  }
}


void Patch::setPatchName(char * patchName) {
  this->patchName[MAX_PATCH_NAME_LENGTH] = 0;
  memcpy(this->patchName, patchName, MAX_PATCH_NAME_LENGTH);
}

void Patch::setEffect(int effectNumber, Effect * effect) {
  if (effectNumber < 0 || effectNumber >= NUM_EFFECTS) {
    return;
  }

  effects[effectNumber] = effect;
}
