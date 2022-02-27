#include "LostInSpaceEffect.h"


const float sampleRate = 44100.0f;


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
  setSwitchLabel(0, "Hold"); // Freeze mode on for the reverb

  chorus = true;
  chorusEngine = new MonoChorusEngine(sampleRate);
  chorusEngine->setEnablesChorus(false, true);
  chorusEngine->chorus1->lfo->phase = 1.0f;
  chorusEngine->chorus1->rate = 0.5f;
  chorusEngine->chorus1->delayTime = 7.0f;
  chorusEngine->chorus2->lfo->phase = 0.0f;
  chorusEngine->chorus2->rate = 0.83f;
  chorusEngine->chorus2->delayTime = 7.0f;

  // Short reflections are the tap delays?
  // Long reflections are primary delay and feedback?
  // Or have a second effect for long reflections...
  delay = true;
  primaryDelay = 15000;
  delayLevel = 0.6;
  delayEffect = new MultiTapDelay();
  delayEffect->setNumTaps(5);
  delayEffect->setPrimaryDelayLength(primaryDelay);
  delayEffect->setPrimaryDelayLevel(delayLevel);

  delayEffect->setTapDelayLength(0, primaryDelay / 2);
  delayEffect->setTapDelayLevel(0, delayLevel);
  delayEffect->setTapDelayLength(1, primaryDelay / 3);
  delayEffect->setTapDelayLevel(1, delayLevel);
  delayEffect->setTapDelayLength(2, primaryDelay * 2 / 3);
  delayEffect->setTapDelayLevel(2, delayLevel);
  delayEffect->setTapDelayLength(3, primaryDelay * 3 / 4);
  delayEffect->setTapDelayLevel(3, delayLevel);
  delayEffect->setTapDelayLength(4, (int)(primaryDelay * 1.61803399));
  delayEffect->setTapDelayLevel(4, delayLevel);

  delayEffect->paramReverse = true;
  delayEffect->paramDry = 1.0;
  delayEffect->paramWet = 0.6;
  delayEffect->paramFeedback = 0.5;

  distortion = true;
  distortionEffect = new Distortion();
  distortionEffect->gain = 4.0f;
  distortionEffect->level = 0.8f;

  reverb = true;
  revModel = new revmodel();
  revModel->init(sampleRate);
  revModel->setdamp(0.15);
  revModel->setwidth(0.0);
  revModel->setroomsize(0.80);
  reverbWet = 1.0;
  reverbDry = 0.8;
}

LostInSpaceEffect::~LostInSpaceEffect() {
    delete revModel;
    delete delayEffect;
    delete chorusEngine;
    delete distortionEffect;
}

void LostInSpaceEffect::processEffect(int16_t * effectBuffer) {
    for (int i = 0; i < 128; i++) {
        int16_t nextSample = effectBuffer[i];

        if (chorus) {
            float floatSample = (float)nextSample;
            float chorusSample = floatSample;
            chorusEngine->process(&chorusSample);
            nextSample = floatSample * 0.8 + chorusSample * 0.2;
        }

        if (distortion) {
            nextSample = distortionEffect->processSample(nextSample);
        }

        if (delay) {
            nextSample = delayEffect->processSample(nextSample);
        }

        if (reverb) {
            float outL = 0.f;
            float outR = 0.f;
            revModel->process(nextSample, outL, outR);
            nextSample = nextSample * reverbDry + outL * reverbWet;
        }

        effectBuffer[i] = nextSample;
    }
}
