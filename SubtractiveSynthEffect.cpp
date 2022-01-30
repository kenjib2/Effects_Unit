#include <string.h>
#include "Patch.h"
#include "SubtractiveSynthEffect.h"


SubtractiveSynthEffect::SubtractiveSynthEffect() {
  strcpy(effectName, "SubtractiveSynth");
  usesSynthMidi = true;
  
  numButtons = 4;
  char label[] = "1234";
  strcpy(label, "Wav1");
  setButtonLabel(0, label);
  strcpy(label, "Wav2");
  setButtonLabel(1, label);
  strcpy(label, "Oct2");
  setButtonLabel(2, label);
  strcpy(label, "WavL");
  setButtonLabel(3, label);

  numKnobs = 16;
  strcpy(label, "Osc1");
  setKnobLabel(0, label);
  strcpy(label, "Osc2");
  setKnobLabel(1, label);
  strcpy(label, "Det2");
  setKnobLabel(2, label);
  strcpy(label, "LFrq");
  setKnobLabel(3, label);
  strcpy(label, "Attk");
  setKnobLabel(4, label);
  strcpy(label, "Decy");
  setKnobLabel(5, label);
  strcpy(label, "Sust");
  setKnobLabel(6, label);
  strcpy(label, "Rels");
  setKnobLabel(7, label);
  strcpy(label, "OEnv");
  setKnobLabel(8, label);
  strcpy(label, "OLFO");
  setKnobLabel(9, label);
  strcpy(label, "AEnv");
  setKnobLabel(10, label);
  strcpy(label, "ALFO");
  setKnobLabel(11, label);
  strcpy(label, "Freq");
  setKnobLabel(12, label);
  strcpy(label, "Reso");
  setKnobLabel(13, label);
  strcpy(label, "FEnv");
  setKnobLabel(14, label);
  strcpy(label, "FLFO");
  setKnobLabel(15, label);

  numSwitches = 2;
  strcpy(label, "Mod");
  setSwitchLabel(0, label);
  strcpy(label, "Sus");
  setSwitchLabel(1, label);
}

void SubtractiveSynthEffect::processEffect(int16_t * effectBuffer) {
}
