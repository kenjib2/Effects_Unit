#include "TestEffect.h"


const int TEST_GRAIN_POOL_SIZE = 10;


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

//	grainPool = new GrainPool(TEST_GRAIN_POOL_SIZE);
//	granularBuffer = new GranularBuffer(grainPool);
//	granularBuffer->speedMultiplier = 1.1f;

	pitchShift = new PitchShift();
}

TestEffect::~TestEffect() {
//	delete grainPool;
//	delete granularBuffer;
	delete pitchShift;
}

void TestEffect::processEffect(int16_t* effectBuffer, Controls* controls) {
//	granularBuffer->loadSamples(effectBuffer, 128);

	for (int i = 0; i < 128; i++) {
		int sample = effectBuffer[i];
		//			effectBuffer[i] = granularBuffer->getNextSample();
		sample = pitchShift->processSample(sample);
		effectBuffer[i] = sample;
	}
}
