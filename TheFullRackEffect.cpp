#include "TheFullRackEffect.h"


const float DIV127 = (1.0 / 127.0);
const float sampleRate = 44100.0;


TheFullRackEffect::TheFullRackEffect() {
  usesSynthMidi = false;

  setEffectName("The Full Rack");
  
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
  gain = 4.0;
  level = 90;

  chorus = true;

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
  revModel->setdamp(0.20);
  revModel->setwidth(0.0);
  revModel->setroomsize(0.70);
  reverbWet = 0.6;
  reverbDry = 1.0;
}

TheFullRackEffect::~TheFullRackEffect() {
  delete revModel;
  delete delayEffect;
}

void TheFullRackEffect::processEffect(int16_t * effectBuffer) {
  for (int i = 0; i < 128; i++) {
    int16_t nextSample = effectBuffer[i];

    if (distortion) {
      float saturatedSample = (float)nextSample / 32768.0 * gain;
      saturatedSample = (2.f / PI) * atan(saturatedSample);
      nextSample = (int)(saturatedSample * 32768 * (level * DIV127));
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
