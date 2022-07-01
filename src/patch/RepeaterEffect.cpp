#include "RepeaterEffect.h"


const int REPEATER_BUFFER_SIZE = 88200;


RepeaterEffect::RepeaterEffect() 
	: repeatMin(1000)
{
	usesSynthMidi = false;

	setEffectName("Repeater");

	numButtons = 0;
	setButtonLabel(0, "Rvrs");

	numKnobs = 16;
	setKnobLabel(0, "Time");
	setKnobLabel(1, "Tap1");
	setKnobLabel(2, "Tap2");
	setKnobLabel(3, "Tap3");
	setKnobLabel(4, "Tap4");
	setKnobLabel(5, "Tap5");
	setKnobLabel(6, "Tap6");
	setKnobLabel(7, "Tap7");
	setKnobLabel(8, "Tap8");
	setKnobLabel(9, "Tap9");
	setKnobLabel(10, "Tp10");
	setKnobLabel(11, "Tp11");
	setKnobLabel(12, "Tp12");
	setKnobLabel(13, "Tp13");
	setKnobLabel(14, "Tp14");
	setKnobLabel(15, "Tp15");

	numSwitches = 1;
	setSwitchLabel(0, "Tmpo");

	delayEffect = new MultiTapDelay(REPEATER_BUFFER_SIZE);
	repeatMax = REPEATER_BUFFER_SIZE / 16;
	repeatLength = 4000;
	delayEffect->setNumTaps(15);
	for (int i = 0; i < 15; i++) {
		delayEffect->setTapDelayLength(i, repeatLength * (i + 1));
	}
	delayEffect->setPrimaryDelayLevel(0.f);
	delayEffect->setTapDelayLevel(0, 0.2f);
	delayEffect->setTapDelayLevel(1, 0.0f);
	delayEffect->setTapDelayLevel(2, 0.8f);
	delayEffect->setTapDelayLevel(3, 0.0f);
	delayEffect->setTapDelayLevel(4, 0.2f);
	delayEffect->setTapDelayLevel(5, 0.0f);
	delayEffect->setTapDelayLevel(6, 0.8f);
	delayEffect->setTapDelayLevel(7, 0.0f);
	delayEffect->setTapDelayLevel(8, 0.2f);
	delayEffect->setTapDelayLevel(9, 0.3f);
	delayEffect->setTapDelayLevel(10, 0.5f);
	delayEffect->setTapDelayLevel(11, 0.6f);
	delayEffect->setTapDelayLevel(12, 0.7f);
	delayEffect->setTapDelayLevel(13, 0.8f);
	delayEffect->setTapDelayLevel(14, 0.9f);
	delayEffect->paramReverse = false;
	delayEffect->paramDry = 1.f;
	delayEffect->paramWet = 1.f;
	delayEffect->paramFeedback = 0.f;
}

RepeaterEffect::~RepeaterEffect() {
	delete delayEffect;
}

void RepeaterEffect::processEffect(int16_t* effectBuffer, Controls* controls) {
	repeatLength = controls->getKnobValue(0) / 255.f * (repeatMax - repeatMin) + repeatMin;
	for (int i = 0; i < 15; i++) {
		delayEffect->setTapDelayLevel(i, controls->getKnobValue(i + 1) / 255.f);
		delayEffect->setTapDelayLength(i, repeatLength * (i + 1));
	}
	for (int i = 0; i < 128; i++) {
		int16_t nextSample = effectBuffer[i];
		nextSample = delayEffect->processSample(nextSample);
		effectBuffer[i] = nextSample;
	}
}
