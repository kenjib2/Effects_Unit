#include "TestEffect.h"


TestEffect::TestEffect() {
	usesSynthMidi = false;

	setEffectName("Test");

	numButtons = 0;

	numKnobs = 16;
	setKnobLabel(0, "Tlv1"); // Mix instead of this would be crossfade between dry and wet
	setKnobLabel(1, "Tim1");
	setKnobLabel(2, "Dep1");
	setKnobLabel(3, "Spd1");
	setKnobLabel(4, "Tlv2");
	setKnobLabel(5, "Tim2");
	setKnobLabel(6, "Dep2");
	setKnobLabel(7, "Spd2");
	setKnobLabel(8, "Tlv3");
	setKnobLabel(9, "Tim3");
	setKnobLabel(10, "Dep3");
	setKnobLabel(11, "Spd3");
	setKnobLabel(12, "Tlv4");
	setKnobLabel(13, "Tim4");
	setKnobLabel(14, "Dep4");
	setKnobLabel(15, "Spd4");

	numSwitches = 0;

}

TestEffect::~TestEffect() {
}

void TestEffect::processEffect(int16_t* effectBuffer) {
	for (int i = 0; i < 128; i++) {
		int16_t nextSample = effectBuffer[i];
//		nextSample += delayBuffer->processSample(nextSample); // How to prevent overflows?
		effectBuffer[i] = nextSample;
	}
}
