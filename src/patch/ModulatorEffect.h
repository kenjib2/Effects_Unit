// Tremolo, Vibrato, Phaser, Flanger
#ifndef MODULATOR_EFFECT_H
#define MODULATOR_EFFECT_H


#include "../../patch.h"
#include "../fx/Modulation.h"
#include "../delay/Delay.h"
#include "../fx/Phaser.h"


class ModulatorEffect : public Effect {
public:
    float vibratoDepth = 0.f;  // 0.f to 1.f
    float vibratoRate = 1.f;  // In hz.
    int vibratoWaveform = 0;

    float tremoloDepth = 0.f;  // 0.f to 1.f
    float tremoloRate = 1.f;  // In hz.
    int tremoloWaveform = 0;

    float flangerLevel = 0.f;  // 0.f to 1.f
    int flangerTime = 200; // typically 441 - 2205 but -150 for the mod buffer size
    float flangerFeedback = 0.f;  // 0.f to 1.f
    float flangerDepth = 0.f;  // 0.f to 1.f
    float flangerRate = 1.f;  // In hz.
    int flangerWaveform = 0;

    float phaserLevel = 0.f;  // 0.f to 1.f
    float phaserRate = 0.5f;  // cycles per second
    int phaserFeedback = 0.7f;  // 0.f to < 1.f
    int phaserMin = 440.f;  // in hz
    int phaserMax = 1600.f;  // in hz


    ModulatorEffect();
    ~ModulatorEffect() override;
    void processEffect(int16_t* effectBuffer, Controls* controls) override;

private:
    Lfo tremoloLfo;
    Modulation* vibratoModulation;
    Modulation* flangerModulation;
    Delay* flangerBuffer;
    Phaser phaser;
};


#endif	// #ifndef MODULATOR_EFFECT_H