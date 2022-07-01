#pragma once
#include <string>
#include <Audio.h>
#include "Controls.h"


const int CTRL_LABEL_LENGTH = 4;
const int CTRL_PER_ROW = 4;

const int NUM_EFFECTS = 2;
const int MAX_PATCH_NAME_LENGTH = 18;
const int MAX_EFFECT_NAME_LENGTH = 18;


class Effect {
  public:
    char effectName[MAX_PATCH_NAME_LENGTH + 1];
    char buttonLabels[NUM_BUTTONS][CTRL_LABEL_LENGTH + 1];
    char knobLabels[NUM_KNOBS][CTRL_LABEL_LENGTH + 1];
    char switchLabels[NUM_SWITCHES][CTRL_LABEL_LENGTH + 1];
    int numButtons;
    int numKnobs;
    int numSwitches;
    bool usesSynthMidi;

    virtual ~Effect() = default;

    void setEffectName(const char * effectName);  
    void setButtonLabel(int buttonNumber, const char * label);
    void setKnobLabel(int knobNumber, const char * label);
    void setSwitchLabel(int switchNumber, const char * label);

    virtual void processEffect(short * effectBuffer, Controls * controls);
};


class BypassEffect: public Effect {
  public:
    BypassEffect();
    void processEffect(int16_t * effectBuffer, Controls * controls) override;
};


class Patch {
  public:
    char patchName[MAX_PATCH_NAME_LENGTH + 1];
    Effect *effects[NUM_EFFECTS];
    char * extraData;
    int extraDataSize = 0;

    void setPatchName(const char * patchName);
    void setEffect(int effectNumber, std::string effectName);
};
