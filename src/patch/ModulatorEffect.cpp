#include "ModulatorEffect.h"


ModulatorEffect::ModulatorEffect() :
	tremoloLfo(44100.f)
{
	usesSynthMidi = false;

	setEffectName("Modulator");

	numButtons = 3;
	setButtonLabel(0, "TWav");
	setButtonLabel(1, "VWav");
	setButtonLabel(2, "FWav");

	numKnobs = 14;
	setKnobLabel(0, "ViDp");
	setKnobLabel(1, "ViSp");
	setKnobLabel(2, "TrDp");
	setKnobLabel(3, "TrSp");
	setKnobLabel(4, "FlLv");
	setKnobLabel(5, "FlTi");
	setKnobLabel(6, "FlFb");
	setKnobLabel(7, "FlDp");
	setKnobLabel(8, "FlSp");
	setKnobLabel(9, "PhLv");
	setKnobLabel(10, "PhSp");
	setKnobLabel(11, "PhFb");
	setKnobLabel(12, "PhMn");
	setKnobLabel(13, "PhMx");

	numSwitches = 1;
	setSwitchLabel(0, "Tmpo");

	vibratoDepth = 0.3f;
	vibratoDepth = 0.f;
	vibratoRate = 1.3f;
	vibratoWaveform = 0;

	tremoloDepth = 0.5f;
	tremoloDepth = 0.f;
	tremoloRate = 8.f;
	tremoloWaveform = 0;

	flangerLevel = 0.5f;
	flangerTime = 50;
	flangerFeedback = 0.45f;
	flangerDepth = 0.3f;
	flangerRate = 0.71f;
	flangerWaveform = 0;

	phaserLevel = 0.9f;
	phaserRate = .17f;
	phaserFeedback = 0.8f;
	phaserMin = 440.f;
	phaserMax = 1600.f;

	vibratoModulation = new Modulation(300);
	vibratoModulation->depth = vibratoDepth;
	vibratoModulation->doppler = 0.f;
	vibratoModulation->setRate(vibratoRate);
	vibratoModulation->setWaveform(vibratoWaveform);

	flangerModulation = new Modulation(150);
	flangerModulation->depth = flangerDepth;
	flangerModulation->doppler = 0.f;
	flangerModulation->setRate(flangerRate);
	flangerModulation->setWaveform(flangerWaveform);
	flangerModulation->depthScale = 400.f;
	flangerBuffer = new Delay(300);
	flangerBuffer->setDelayLength(flangerTime);
	flangerBuffer->paramReverse = false;
	flangerBuffer->paramDry = 1.f;
	flangerBuffer->paramWet = flangerLevel;
	flangerBuffer->paramFeedback = flangerFeedback;
	flangerBuffer->setWriteInsert(flangerModulation);

	tremoloLfo.setWaveform(tremoloWaveform);
	tremoloLfo.setRate(tremoloRate);

	phaser.Depth(phaserLevel);
	phaser.Rate(phaserRate);
	phaser.Feedback(phaserFeedback);
	phaser.Range(phaserMin, phaserMax);

}

ModulatorEffect::~ModulatorEffect() {
	delete vibratoModulation;
	delete flangerModulation;
}

void ModulatorEffect::processEffect(int16_t* effectBuffer) {
	for (int i = 0; i < 128; i++) {
		int16_t nextSample = effectBuffer[i];

		if (vibratoDepth > EPSILON) {
			nextSample = vibratoModulation->processSample(nextSample);
		}

		if (flangerLevel > EPSILON) {
			nextSample = flangerBuffer->processSample(nextSample);
		}

		if (tremoloDepth > EPSILON) {
			float lfoValue = tremoloLfo.tick(tremoloWaveform); // -1 to 1
			float tremoloFactor = 1.f - ((lfoValue + 1) / 2.f * tremoloDepth);  // 0 to 1

			nextSample = (int)(tremoloFactor * nextSample);
		}

		if (phaserLevel > EPSILON) {
			nextSample = phaser.Update(nextSample);
		}

		effectBuffer[i] = nextSample;
	}
}
