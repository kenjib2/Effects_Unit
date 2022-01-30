#pragma once
#include <Audio.h>


const int CTRL_LABEL_LENGTH = 4;
const int CTRL_PER_ROW = 4;
const int NUM_BUTTONS = 4;
const int NUM_KNOBS = 16;
const int NUM_SWITCHES = 2;

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

    void setEffectName(char * effectName);  
    void setButtonLabel(int buttonNumber, char * label);
    void setKnobLabel(int knobNumber, char * label);
    void setSwitchLabel(int switchNumber, char * label);

    virtual void processEffect(short * effectBuffer);
};


class BypassEffect: public Effect {
  public:
    BypassEffect();
    void processEffect(int16_t * effectBuffer);
};


class LostInSpaceEffect: public Effect {
  public:
    LostInSpaceEffect();
    void processEffect(int16_t * effectBuffer);
};


class TemporalCollapseEffect: public Effect {
  public:
    TemporalCollapseEffect();
    void processEffect(int16_t * effectBuffer);
};


class Patch {
  public:
    char patchName[MAX_PATCH_NAME_LENGTH + 1];
    Effect *effects[NUM_EFFECTS];

    void setPatchName(char * patchName);
    void setEffect(int effectNumber, Effect * effect);
};
