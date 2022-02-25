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
  setSwitchLabel(0, "Hold"); // Increase decay

  distortion = true;
  distortionEffect = new Distortion();
  distortionEffect->gain = 6.0f;
  distortionEffect->level = 0.4f;

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
  delayEffect->paramFeedback = 0.3;

  reverb = true;
  revModel = new revmodel();
  revModel->init(sampleRate);
  revModel->setdamp(0.25);
  revModel->setwidth(0.0);
  revModel->setroomsize(0.60);
  reverbWet = 0.6;
  reverbDry = 1.0;
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

        if (distortion) {
            nextSample = distortionEffect->processSample(nextSample);
        }

        if (chorus) {
            float floatSample = (float)nextSample;
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
