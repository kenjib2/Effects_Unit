#include "LostInSpaceEffect.h"


LostInSpaceEffect::LostInSpaceEffect() {
  usesSynthMidi = false;

  setEffectName("Lost in Space");
  
  numButtons = 1;
  setButtonLabel(0, "Dir"); // Delay forward or reverse

  numKnobs = 14;
  setKnobLabel(0, "Dry");
  setKnobLabel(1, "Wet");
  setKnobLabel(2, "Size");
  setKnobLabel(3, "Damp");
  setKnobLabel(4, "Shrt");
  setKnobLabel(5, "Time");
  setKnobLabel(6, "Fdbk");
  setKnobLabel(7, "Ptch");
  setKnobLabel(8, "Long");
  setKnobLabel(9, "Time");
  setKnobLabel(10, "Fdbk");
  setKnobLabel(11, "Ptch");
  setKnobLabel(12, "Blm"); // Bloom
  setKnobLabel(13, "Shim"); // Shimmer
  setKnobLabel(14, "Driv"); // Drive

  numSwitches = 1;
  setSwitchLabel(0, "Hold"); // Increase decay
}

void LostInSpaceEffect::processEffect(int16_t * effectBuffer) {
}
