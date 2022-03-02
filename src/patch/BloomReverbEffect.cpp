#include "BloomReverbEffect.h"


const float sampleRate = 44100.0f;


BloomReverbEffect::BloomReverbEffect() {
    usesSynthMidi = false;

    setEffectName("Bloom Reverb");

    numButtons = 0;

    numKnobs = 16;
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
    setKnobLabel(12, "BlmL"); // Bloom Level
    setKnobLabel(12, "BlmT"); // Bloom Time
    setKnobLabel(13, "Shim"); // Shimmer
    setKnobLabel(14, "Driv"); // Drive

    numSwitches = 1;
    setSwitchLabel(0, "Hold"); // Freeze mode on for the reverb

    revModel = new revmodel();
    revModel->init(sampleRate);
    revModel->setdamp(0.10);
    revModel->setwidth(0.0);
    revModel->setroomsize(0.70);
    reverbWet = 1.0;
    reverbDry = 0.8f;

    bloomRevModel = new revmodel();
    bloomRevModel->init(sampleRate);
    bloomRevModel->setdamp(0.10);
    bloomRevModel->setwidth(0.0);
    bloomRevModel->setroomsize(0.30);
}

BloomReverbEffect::~BloomReverbEffect() {
    delete revModel;
    delete bloomRevModel;
}

void BloomReverbEffect::processEffect(int16_t* effectBuffer) {
    for (int i = 0; i < 128; i++) {
        int16_t nextSample = effectBuffer[i];

        float outL = 0.f;
        float outR = 0.f;
        float bloomOutL = 0.f;
        float bloomOutR = 0.f;
        revModel->process(nextSample, outL, outR);
        bloomRevModel->process(nextSample, bloomOutL, bloomOutR);
        outL -= bloomOutL;
        nextSample = nextSample * reverbDry + outL * reverbWet * 3;

        effectBuffer[i] = nextSample;
    }
}
