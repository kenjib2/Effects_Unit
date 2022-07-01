#include "RhythmicDelayEffect.h"


RhythmicDelayEffect::RhythmicDelayEffect() {
	usesSynthMidi = false;

	setEffectName("Rhythmic Delay");

	numButtons = 1;
	setButtonLabel(0, "Rvrs");

	numKnobs = 15;
	setKnobLabel(0, "Time");
	setKnobLabel(1, "Lvl");
	setKnobLabel(2, "Tim2");
	setKnobLabel(3, "Lvl2");
	setKnobLabel(4, "Tim3");
	setKnobLabel(5, "Lvl3");
	setKnobLabel(6, "Tim4");
	setKnobLabel(7, "Lvl4");
	setKnobLabel(8, "TimR");
	setKnobLabel(9, "LvlR");
	setKnobLabel(10, "1/3");
	setKnobLabel(11, "1/2");
	setKnobLabel(12, "3/4");
	setKnobLabel(13, "3/2");
	setKnobLabel(14, "Gold");
	setKnobLabel(15, "Fdbk");

	numSwitches = 1;
	setSwitchLabel(0, "Tmpo");
	setSwitchLabel(0, "Fmod");
	// <<<<< ADD FEEDBACK MODES TO FEEDBACK ALL INDICES OR JUST THE FIRST ONE

	primaryDelay = 25000;
	delayEffect = new MultiTapDelay();
	delayEffect->setNumTaps(10);
	// Time
	delayEffect->setPrimaryDelayLength(primaryDelay);
	delayEffect->setPrimaryDelayLevel(0.7f);
	// Tim2
	delayEffect->setTapDelayLength(0, 11300);
	delayEffect->setTapDelayLevel(0, 0.0f);
	// Tim3
	delayEffect->setTapDelayLength(1, 17700);
	delayEffect->setTapDelayLevel(1, 0.8f);
	// Tim4
	delayEffect->setTapDelayLength(2, 9300);
	delayEffect->setTapDelayLevel(2, 0.0f);
	// TimR
	delayEffect->setTapDelayLength(3, primaryDelay + 2500); // This one goes from -X to +X
	delayEffect->setTapDelayLevel(3, 0.8f);
	// 1/3
	delayEffect->setTapDelayLength(4, primaryDelay / 3);
	delayEffect->setTapDelayLevel(4, 0.8f);
	delayEffect->setTapDelayLength(5, primaryDelay * 2 / 3);
	delayEffect->setTapDelayLevel(5, 0.8f);
	// 1/2
	delayEffect->setTapDelayLength(6, primaryDelay / 2);
	delayEffect->setTapDelayLevel(6, 0.0f);
	// 3/4
	delayEffect->setTapDelayLength(7, primaryDelay * 3 / 4);
	delayEffect->setTapDelayLevel(7, 0.8f);
	// 3/2
	delayEffect->setTapDelayLength(8, primaryDelay * 3 / 2);
	delayEffect->setTapDelayLevel(8, 0.0f);
	// Gold
	delayEffect->setTapDelayLength(9, (int)(primaryDelay * 1.61803399));
	delayEffect->setTapDelayLevel(9, 0.8f);

	delayEffect->paramReverse = false;
	delayEffect->paramDry = 1.0f;
	delayEffect->paramWet = 1.0f;
	delayEffect->paramFeedback = 0.4f;
}

RhythmicDelayEffect::~RhythmicDelayEffect() {
	delete delayEffect;
}

void RhythmicDelayEffect::processEffect(int16_t* effectBuffer, Controls* controls) {
	for (int i = 0; i < 128; i++) {
		int16_t nextSample = effectBuffer[i];
		nextSample = delayEffect->processSample(nextSample);
		effectBuffer[i] = nextSample;
	}
}
