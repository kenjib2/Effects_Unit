#include "ReverbEffect.h"


const float sampleRate = 44100.0f;


ReverbEffect::ReverbEffect() {
    usesSynthMidi = false;

    setEffectName("Reverb");

    numButtons = 0;

    numKnobs = 6;
    setKnobLabel(0, "Dry");
    setKnobLabel(1, "Wet");
    setKnobLabel(2, "Size");
    setKnobLabel(3, "Damp");
    setKnobLabel(4, "BlmL"); // Bloom Level
    setKnobLabel(5, "BlmT"); // Bloom Time

    numSwitches = 1;
    setSwitchLabel(0, "Hold"); // Freeze mode on for the reverb

    revModel = new revmodel();
    revModel->init(sampleRate);
    revModel->setdamp(0.15);
    revModel->setwidth(0.0);
    revModel->setroomsize(0.70);
    reverbWet = 0.35;
    reverbDry = 1.0f;

    bloomRevModel = new revmodel();
    bloomRevModel->init(sampleRate);
    bloomRevModel->setdamp(0.10);
    bloomRevModel->setwidth(0.0);
    bloomRevModel->setroomsize(0.30);
}

ReverbEffect::~ReverbEffect() {
    delete revModel;
    delete bloomRevModel;
}

void ReverbEffect::processEffect(int16_t* effectBuffer) {
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
