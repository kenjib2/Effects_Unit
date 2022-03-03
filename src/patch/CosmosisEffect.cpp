#include "CosmosisEffect.h"


CosmosisEffect::CosmosisEffect() {
	usesSynthMidi = false;

	setEffectName("Cosmosis");

	numButtons = 1;
	setButtonLabel(0, "Rvrs");

	numKnobs = 16;
	setKnobLabel(0, "Mix"); // Crossfade between dry and wet
	setKnobLabel(1, "Tim1");
	setKnobLabel(2, "Tap1");
	setKnobLabel(3, "Tlv1");
	setKnobLabel(4, "Dep1");
	setKnobLabel(5, "Spd1");
	setKnobLabel(6, "Tim2");
	setKnobLabel(7, "Tap2");
	setKnobLabel(8, "Tlv2");
	setKnobLabel(9, "Dep2");
	setKnobLabel(10, "Spd2");
	setKnobLabel(11, "Tim3");
	setKnobLabel(12, "Tap3");
	setKnobLabel(13, "Tlv3");
	setKnobLabel(14, "Dep3");
	setKnobLabel(15, "Spd3");

	numSwitches = 0;

	for (int i = 0; i < NUM_COSMOSIS_BUFFERS; i++) {
		primaryDelays[i] = 1800 - i * 200;
		delayBuffer[i] = new MultiTapDelay(MODULATION_BUFFER_SIZE);
		delayBuffer[i]->setNumTaps(NUM_COSMOSIS_TAPS);

		delayBuffer[i]->setPrimaryDelayLength(primaryDelays[i]);
		delayBuffer[i]->setPrimaryDelayLevel(1.f);

		for (int j = 0; j < NUM_COSMOSIS_TAPS; j++) {
			delayBuffer[i]->setTapDelayLength(j, primaryDelays[i] * 3 / 4);
			delayBuffer[i]->setTapDelayLevel(j, 0.5f);
		}

		delayBuffer[i]->paramReverse = false;
		delayBuffer[i]->paramDry = paramDryLevel;
		delayBuffer[i]->paramWet = paramWetLevel;
		delayBuffer[i]->paramFeedback = 0.f;

		delayModulation[i] = new Modulation();
		delayBuffer[i]->setWriteInsert(delayModulation[i]);
	}

}

CosmosisEffect::~CosmosisEffect() {
	for (int i = 0; i < NUM_COSMOSIS_BUFFERS; i++) {
		delete delayBuffer[i];
		delete delayModulation[i];
	}
}

void CosmosisEffect::processEffect(int16_t* effectBuffer) {
	for (int i = 0; i < 128; i++) {
		int16_t nextSample = effectBuffer[i];
		for (int i = 0; i < NUM_COSMOSIS_BUFFERS; i++) {
			nextSample = delayBuffer[i]->processSample(nextSample);
		}
		effectBuffer[i] = nextSample;
	}
}
