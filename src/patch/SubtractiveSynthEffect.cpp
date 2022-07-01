#include "SubtractiveSynthEffect.h"


SubtractiveSynthEffect::SubtractiveSynthEffect() {
  usesSynthMidi = true;

  setEffectName("Subtractive Synth");
  
  numButtons = 4;
  setButtonLabel(0, "Wav1");
  setButtonLabel(1, "Wav2");
  setButtonLabel(2, "Oct2");
  setButtonLabel(3, "WavL");

  numKnobs = 16;
  setKnobLabel(0, "Osc1");
  setKnobLabel(1, "Osc2");
  setKnobLabel(2, "Det2");
  setKnobLabel(3, "LFrq");
  setKnobLabel(4, "Attk");
  setKnobLabel(5, "Decy");
  setKnobLabel(6, "Sust");
  setKnobLabel(7, "Rels");
  setKnobLabel(8, "OEnv");
  setKnobLabel(9, "OLFO");
  setKnobLabel(10, "AEnv");
  setKnobLabel(11, "ALFO");
  setKnobLabel(12, "Freq");
  setKnobLabel(13, "Reso");
  setKnobLabel(14, "FEnv");
  setKnobLabel(15, "FLFO");

  numSwitches = 2;
  setSwitchLabel(0, "Mod");
  setSwitchLabel(1, "Sus");
}

void SubtractiveSynthEffect::processEffect(int16_t * effectBuffer, Controls* controls) {
}
