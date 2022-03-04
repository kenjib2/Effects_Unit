#include "StandardFxChainEffect.h"


const float sampleRate = 44100.0f;


StandardFxChainEffect::StandardFxChainEffect() {
  usesSynthMidi = false;

  setEffectName("Standard FX Chain");
  
  numButtons = 4;
  setButtonLabel(0, "Dist");
  setButtonLabel(1, "Chor");
  setButtonLabel(2, "Dlay");
  setButtonLabel(3, "Rvrb");

  numKnobs = 10;
  setKnobLabel(0, "Gain");
  setKnobLabel(1, "Lvl");
  setKnobLabel(2, "Dpth");
  setKnobLabel(3, "Spd");
  setKnobLabel(4, "Rte");
  setKnobLabel(5, "Lvl");
  setKnobLabel(6, "Fdbk");
  setKnobLabel(7, "Mix");
  setKnobLabel(8, "Rmsz");
  setKnobLabel(9, "Damp");

  numSwitches = 1;
  setSwitchLabel(0, "Tmpo");

  distortion = true;
  distortionEffect = new Distortion();
  distortionEffect->gain = 1.5f;
  distortionEffect->level = 0.8f;

  chorus = true;
  chorusEngine = new MonoChorusEngine(sampleRate);
  chorusEngine->setEnablesChorus(false, true);
  chorusEngine->chorus1->lfo->phase = 1.0f;
  chorusEngine->chorus1->rate = 0.5f;
  chorusEngine->chorus1->delayTime = 7.0f;
  chorusEngine->chorus2->lfo->phase = 0.0f;
  chorusEngine->chorus2->rate = 0.83f;
  chorusEngine->chorus2->delayTime = 7.0f;

  delay = true;
  delayEffect = new Delay();
  delayEffect->setDelayLength(14000);
  delayEffect->paramReverse = false;
  delayEffect->paramDry = 1.0;
  delayEffect->paramWet = 0.4;
  delayEffect->paramFeedback = 0.0;

  reverb = true;
  revModel = new revmodel();
  revModel->init(sampleRate);
  revModel->setdamp(0.25);
  revModel->setwidth(0.0);
  revModel->setroomsize(0.60);
  reverbWet = 0.6;
  reverbDry = 1.0;
}

StandardFxChainEffect::~StandardFxChainEffect() {
  delete revModel;
  delete delayEffect;
  delete chorusEngine;
  delete distortionEffect;
}

void StandardFxChainEffect::processEffect(int16_t * effectBuffer) {
  for (int i = 0; i < 128; i++) {
    int16_t nextSample = effectBuffer[i];

    if (distortion) {
      nextSample = distortionEffect->processSample(nextSample);
    }

    if (chorus) {
        float floatSample= (float)nextSample;
        chorusEngine->process(&floatSample);
        nextSample = floatSample;
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
