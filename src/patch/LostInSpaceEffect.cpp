#include "LostInSpaceEffect.h"


const float sampleRate = 44100.0f;


LostInSpaceEffect::LostInSpaceEffect() {
  usesSynthMidi = false;

  setEffectName("Lost in Space");
  
  numButtons = 2;
  setButtonLabel(0, "SDir"); // Short reflections forward or reverse
  setButtonLabel(1, "LDir"); // Long reflections forward or reverse

  numKnobs = 13;
  setKnobLabel(0, "Dry");
  setKnobLabel(1, "Wet");
  setKnobLabel(2, "Size");
  setKnobLabel(3, "Damp");
  setKnobLabel(4, "Shrt");
  setKnobLabel(5, "Time");
  setKnobLabel(6, "Fdbk");
  setKnobLabel(7, "Long");
  setKnobLabel(8, "Time");
  setKnobLabel(9, "Fdbk");
  setKnobLabel(10, "Blm"); // Bloom
  setKnobLabel(11, "Shim"); // Shimmer
  setKnobLabel(12, "Driv"); // Drive

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
  primaryDelay = 7000;
  delayLevel = 0.12f;
  shortReflections = new MultiTapDelay(13000);
  shortReflections->setNumTaps(5);
  shortReflections->setPrimaryDelayLength(primaryDelay);
  shortReflections->setPrimaryDelayLevel(1.f);

  shortReflections->setTapDelayLength(0, primaryDelay / 2);
  shortReflections->setTapDelayLevel(0, 1.f);
  shortReflections->setTapDelayLength(1, primaryDelay / 3);
  shortReflections->setTapDelayLevel(1, 1.f);
  shortReflections->setTapDelayLength(2, primaryDelay * 2 / 3);
  shortReflections->setTapDelayLevel(2, 1.f);
  shortReflections->setTapDelayLength(3, primaryDelay * 3 / 4);
  shortReflections->setTapDelayLevel(3, 1.f);
  shortReflections->setTapDelayLength(4, (int)(primaryDelay * 1.61803399));
  shortReflections->setTapDelayLevel(4, 1.f);

  shortReflections->paramReverse = false;
  shortReflections->paramDry = 1.f;
  shortReflections->paramWet = delayLevel;
  shortReflections->paramFeedback = 0.f;

  int primaryLongDelay = 7000;
  float longDelayLevel = .14f;
  longReflections = new MultiTapDelay(13000);
  longReflections->setNumTaps(1);
  longReflections->setPrimaryDelayLength(primaryLongDelay);
  longReflections->setPrimaryDelayLevel(1.f);

  longReflections->paramReverse = false;
  longReflections->paramDry = 1.f;
  longReflections->paramWet = longDelayLevel;
  longReflections->paramFeedback = 0.5f;

  distortion = true;
  distortionEffect = new Distortion();
  distortionEffect->gain = 6.0f;
  distortionEffect->level = 0.7f;

  reverb = true;
  revModel = new revmodel();
  revModel->init(sampleRate);
  revModel->setdamp(0.1);
  revModel->setwidth(0.0);
  revModel->setroomsize(0.70);
  reverbWet = 1.f;
  reverbDry = 1.f;

  bloomRevModel = new revmodel();
  bloomRevModel->init(sampleRate);
  bloomRevModel->setdamp(0.15);
  bloomRevModel->setwidth(0.0);
  bloomRevModel->setroomsize(0.30);

  shimmerPitch = new PitchShift();
  shimmerPitch->playbackSpeed = 2.f;

  int primaryShimmerDelay = 18000;
  float shimmerDelayLevel = .09f;
  shimmerDelay = new Delay(20000);
  shimmerDelay->setDelayLength(primaryShimmerDelay);

  shimmerDelay->paramReverse = false;
  shimmerDelay->paramDry = 1.f;
  shimmerDelay->paramWet = shimmerDelayLevel;
  shimmerDelay->paramFeedback = 0.35f;
  shimmerDelay->setWriteInsert(shimmerPitch);

}

LostInSpaceEffect::~LostInSpaceEffect() {
    delete revModel;
    delete shortReflections;
    delete longReflections;
    delete chorusEngine;
    delete distortionEffect;
}

void LostInSpaceEffect::processEffect(int16_t * effectBuffer) {
    for (int i = 0; i < 128; i++) {
        int16_t nextSample = effectBuffer[i];

        if (distortion) {
            nextSample = distortionEffect->processSample(nextSample);
        }

        if (chorus) {
            float floatSample = (float)nextSample;
            float chorusSample = floatSample;
            chorusEngine->process(&chorusSample);
            nextSample = floatSample * 0.8 + chorusSample * 0.2;
        }

        if (delay) {
            nextSample = shortReflections->processSample(nextSample);
            nextSample = longReflections->processSample(nextSample);
        }

        if (reverb) {
            float outL = 0.f;
            float outR = 0.f;
            float bloomOutL = 0.f;
            float bloomOutR = 0.f;
            revModel->process(nextSample, outL, outR);
            bloomRevModel->process(nextSample, bloomOutL, bloomOutR);
            outL -= bloomOutL;
            outL = shimmerDelay->processSample(outL);
            nextSample = nextSample * reverbDry + outL * reverbWet;
        }

        effectBuffer[i] = nextSample;
    }
}
