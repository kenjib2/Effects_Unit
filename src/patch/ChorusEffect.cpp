#include "ChorusEffect.h"


ChorusEffect::ChorusEffect() {
	usesSynthMidi = false;

	setEffectName("Chorus");

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

	delayLevels[0] = 0.8f;
	delayLengths[0] = 950;
	delayDepths[0] = 0.3f;
	delayRates[0] = 1.f;

	delayLevels[1] = 0.6f;
	delayLengths[1] = 750;
	delayDepths[1] = 0.2f;
	delayRates[1] = 8.f;

	delayLevels[2] = 0.6f;
	delayLengths[2] = 550;
	delayDepths[2] = 0.3;
	delayRates[2] = 2.3f;

	delayLevels[3] = 0.6f;
	delayLengths[3] = 350;
	delayDepths[3] = 0.2;
	delayRates[3] = 0.7f;

	for (int i = 0; i < NUM_CHORUS_BUFFERS; i++) {
		delayModulation[i] = new Modulation(300);
		delayModulation[i]->depth = delayDepths[i];
		delayModulation[i]->setRate(delayRates[i]);
		delayModulation[i]->setWaveform(CHORUS_LFO_WAVEFORM);

		delayBuffer[i] = new Delay(MAX_CHORUS_DELAY);
		delayBuffer[i]->setDelayLength(delayLengths[0]);
		delayBuffer[i]->paramReverse = false;
		delayBuffer[i]->paramDry = 0.f;
		delayBuffer[i]->paramWet = delayLevels[0];
		delayBuffer[i]->paramFeedback = 0.f;
		delayBuffer[i]->setWriteInsert(delayModulation[i]);
	}

}

ChorusEffect::~ChorusEffect() {
	for (int i = 0; i < NUM_CHORUS_BUFFERS; i++) {
		delete delayBuffer[i];
		delete delayModulation[i];
	}
}

void ChorusEffect::processEffect(int16_t* effectBuffer, Controls* controls) {
	for (int i = 0; i < 128; i++) {
		int16_t nextSample = effectBuffer[i];
		for (int i = 0; i < NUM_CHORUS_BUFFERS; i++) {
			nextSample += delayBuffer[i]->processSample(nextSample) * delayLevels[i] * 0.7; // How to prevent overflows?
		}
		effectBuffer[i] = nextSample;
	}
}
