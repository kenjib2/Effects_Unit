#ifndef CONTROLS_H
#define CONTROLS_H


#include "Arduino.h"


const int NUM_KNOBS = 16;
const int KNOB_HISTORY_SIZE = 20;
const int KNOB_DROP_BITS = 2;
const int KNOB_MAX_VALUE = 1023 >> KNOB_DROP_BITS;
const int NUM_BUTTONS = 4;
const int NUM_SWITCHES = 2;

unsigned const int DEBOUNCE_DELAY = 50;


typedef enum EncoderState {
  ENCODER_UP
  , ENCODER_DOWN
  , ENCODER_UNCHANGED
} EncoderState;


class Controls {
  public:
    Controls();

    void initKnobHistory();
    void pollInput();
    EncoderState getEncoderState(); // Reading the encoder state resets the state to unchanged.
    bool encoderPressed(); // Reading the encoder button pressed value resets the state to false;
    word getKnobValue(int knob);
    void setKnobValue(int knob, word value);
    void resetKnobInputs();
    void buttonMod(int button, int modulus);
    word getButtonValue(int button);

    
  private:
    EncoderState encoderState;
    bool encoderButtonPressed;
    bool knobInputActive[NUM_KNOBS] = {};
    word knobValues[NUM_KNOBS] = {};
    word knobReads[NUM_KNOBS][KNOB_HISTORY_SIZE] = {};
    word previousKnobReads[NUM_KNOBS] = {};
    int knobReadIndex;
    word buttonValues[NUM_BUTTONS] = {};

    void setMultiplexerPins(int index);
    word getPotReading(int potIndex);
    int getKnobRead(int knob);
    void calculateKnobValue(int knob);
};


#endif // #ifndef CONTROLS_H
