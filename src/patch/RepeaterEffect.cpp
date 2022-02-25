#include "RepeaterEffect.h"


RepeaterEffect::RepeaterEffect() {
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

	repeatLength = 4000;
	delayEffect = new MultiTapDelay();
	delayEffect->setNumTaps(15);
	for (int i = 0; i < 16; i++) {
		delayEffect->setTapDelayLength(i, repeatLength * (i + 1));
		Serial.println(repeatLength * (i + 1));
	}
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
	delayEffect->paramDry = 1.0f;
	delayEffect->paramWet = 0.6f;
	delayEffect->paramFeedback = 0.0f;
}

RepeaterEffect::~RepeaterEffect() {
	delete delayEffect;
}

void RepeaterEffect::processEffect(int16_t* effectBuffer) {
	for (int i = 0; i < 128; i++) {
		int16_t nextSample = effectBuffer[i];
		nextSample = delayEffect->processSample(nextSample);
		effectBuffer[i] = nextSample;
	}
}
