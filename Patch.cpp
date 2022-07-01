#include "Patch.h"
#include "EffectFactory.h"


void Effect::setEffectName(const char * effectName) {
  // Truncate to a max of MAX_EFFECT_NAME_LENGTH null terminated characters
  this->effectName[MAX_EFFECT_NAME_LENGTH] = 0;
  strncpy(this->effectName, effectName, MAX_EFFECT_NAME_LENGTH);
}

void Effect::setButtonLabel(int buttonNumber, const char * label) {
  if (buttonNumber < 0 || buttonNumber >= NUM_KNOBS) {
    return;
  }
  // Truncate to a max of CTRL_LABEL_LENGTH null terminated characters
  buttonLabels[buttonNumber][CTRL_LABEL_LENGTH] = 0;
  strncpy(buttonLabels[buttonNumber], label, CTRL_LABEL_LENGTH);
}

void Effect::setKnobLabel(int knobNumber, const char * label) {
  if (knobNumber < 0 || knobNumber >= NUM_KNOBS) {
    return;
  }
  // Truncate to a max of CTRL_LABEL_LENGTH null terminated characters
  knobLabels[knobNumber][CTRL_LABEL_LENGTH] = 0;
  strncpy(knobLabels[knobNumber], label, CTRL_LABEL_LENGTH);
}

void Effect::setSwitchLabel(int switchNumber, const char * label) {
  if (switchNumber < 0 || switchNumber >= NUM_SWITCHES) {
    return;
  }
  // Truncate to a max of CTRL_LABEL_LENGTH null terminated characters
  switchLabels[switchNumber][CTRL_LABEL_LENGTH] = 0;
  strncpy(switchLabels[switchNumber], label, CTRL_LABEL_LENGTH);
}

//void Effect::processEffect(short * effectBuffer){} // To make it not inline and fix the vtable


BypassEffect::BypassEffect() {
  usesSynthMidi = false;
  setEffectName("Bypass");
  numButtons = 0;
  numKnobs = 0;
  numSwitches = 0;
}

void BypassEffect::processEffect(int16_t * effectBuffer, Controls * controls) {
}


void Patch::setPatchName(const char * patchName) {
  this->patchName[MAX_PATCH_NAME_LENGTH] = 0;
  strncpy(this->patchName, patchName, MAX_PATCH_NAME_LENGTH);
}

void Patch::setEffect(int effectNumber, std::string effectName) {
  if (effectNumber < 0 || effectNumber >= NUM_EFFECTS) {
    return;
  }

  delete effects[effectNumber];
  effects[effectNumber] = EffectFactory::createEffect(effectName);
}
