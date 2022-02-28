#include "TemporalCollapseEffect.h"


TemporalCollapseWriteInsert::TemporalCollapseWriteInsert() {
  paramSmooth = 0.f;
  paramSmear = 0.f;
  paramDrive = 0.f;
  paramCrush = 0.f;
    
  bitCrusher = new BitCrusher();

  distortion = new Distortion();

  filter = new CjFilter();

  revModel = new revmodel();
  revModel->init(44100);
  revModel->setdamp(0.50);
  revModel->setwidth(0.0);
  revModel->setroomsize(0.20);
}


TemporalCollapseWriteInsert::~TemporalCollapseWriteInsert() {
  delete bitCrusher;
  delete distortion;
  delete filter;
  delete revModel;
}


int16_t TemporalCollapseWriteInsert::processSample(int16_t sampleIn) {
  if (paramSmear > 0.001f) {
    float outL = 0.f;
    float outR = 0.f;
    revModel->process(sampleIn, outL, outR);
    sampleIn = outL * (paramSmear * 0.6f) + sampleIn * (1.f - (paramSmear * 0.6f)); // We scale down smear because too high generates a lot of feedback
  }
  if (paramDrive > 0.001f) {
    distortion->gain = 1.f + paramDrive * 3;
    distortion->level = 1.0f - (paramDrive * paramDrive / 2);
    sampleIn = distortion->processSample(sampleIn);
  }
  if (paramSmooth > 0.001f) {
      sampleIn = filter->doFilter(sampleIn, 1.f - paramSmooth, 0.f);
  }
  if (paramCrush > 0.001f) {
    float paramCrushLog = paramCrush * paramCrush;
    bitCrusher->bits = 15.f - paramCrushLog * 4;
    bitCrusher->downsample = paramCrushLog * 64;
    sampleIn = bitCrusher->processSample(sampleIn);
  }
    return sampleIn;
}


TemporalCollapseEffect::TemporalCollapseEffect() {
  usesSynthMidi = false;

  setEffectName("Temporal Collapse");
  
  numButtons = 2;
  setButtonLabel(0, "Buff");
  setButtonLabel(1, "Rvrs");

  numKnobs = 12;
  setKnobLabel(0, "Dry");
  setKnobLabel(1, "Wet");
  setKnobLabel(2, "Sens");
  setKnobLabel(3, "Ltch");
  setKnobLabel(4, "Time");
  setKnobLabel(5, "Feed");
  setKnobLabel(6, "Drft");
  setKnobLabel(7, "Ltch");
  setKnobLabel(8, "Smth");
  setKnobLabel(9, "Smr");
  setKnobLabel(10, "Driv");
  setKnobLabel(11, "Crsh");

  numSwitches = 2;
  setSwitchLabel(0, "Ltch");
  setSwitchLabel(1, "Tmpo");

  delayEffect = new Delay();
  delayEffect->setDelayLength(10000);
  delayEffect->paramReverse = false;
  delayEffect->paramDry = 1.0;
  delayEffect->paramWet = 0.6;
  delayEffect->paramFeedback = 0.5;
  delayEffect->setLoopLatch(0.3f);
  delayEffect->paramSensitivity = 32767;
//  delayEffect->paramSensitivity = 30000;
  writeInsert = new TemporalCollapseWriteInsert();
  writeInsert->paramSmooth = 0.3f;
  writeInsert->paramSmear = 0.4f;
  writeInsert->paramDrive = 0.8f;
  writeInsert->paramCrush = 0.2f;
  delayEffect->setWriteInsert(writeInsert);
}

TemporalCollapseEffect::~TemporalCollapseEffect() {
    delete writeInsert;
    delete delayEffect;
}

void TemporalCollapseEffect::processEffect(int16_t * effectBuffer) {
  for (int i = 0; i < 128; i++) {
    int16_t nextSample = effectBuffer[i];

    nextSample = delayEffect->processSample(nextSample);

    effectBuffer[i] = nextSample;
  }
}
