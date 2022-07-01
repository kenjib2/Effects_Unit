#include "Controls.h"
#include "TeensyPins.h"


Controls::Controls()
  : knobReadIndex(0)
{
  initKnobHistory();
}


void Controls::initKnobHistory() {
  for (int i = 0; i < NUM_KNOBS; i++) {
    int value = getPotReading(i);
    for (int j = 0; j < KNOB_HISTORY_SIZE; j++) {
      knobReads[i][j] = value;
    }
    calculateKnobValue(i);
    previousKnobReads[i] = getKnobValue(i);
  }
  resetKnobInputs();
}


void Controls::pollInput() {
  // ------------- BUTTONS -------------
  static int buttonsLastState[NUM_BUTTONS] = { HIGH, HIGH, HIGH, HIGH };
  static int buttonsState[NUM_BUTTONS];
  static int buttonsLastDebounceTime[NUM_BUTTONS];

  for (int i = 0; i < NUM_BUTTONS; i++) {
    int buttonPin = 0;
    switch (i) {
      case 0:
        buttonPin = PIN_BUTTON_BLUE;
        break;
      case 1:
        buttonPin = PIN_BUTTON_RED;
        break;
      case 2:
        buttonPin = PIN_BUTTON_YELLOW;
        break;
      case 3:
        buttonPin = PIN_BUTTON_GREEN;
        break;
    }

    int reading = digitalRead(buttonPin);
    if (reading != buttonsLastState[i]) {
      buttonsLastDebounceTime[i] = millis();
    }
  
    if ((millis() - buttonsLastDebounceTime[i]) > DEBOUNCE_DELAY) {
      if (reading != buttonsState[i]) {
        buttonsState[i] = reading;
  
        if (buttonsState[i] == LOW) {
          Serial.println("BUTTON PRESSED");
          buttonValues[i]++;
        }
      }
    }
    buttonsLastState[i] = reading;
  }


  // ------------- KNOBS -------------
  for (int i = 0; i < NUM_KNOBS; i++) {
    knobReads[i][knobReadIndex] = getPotReading(i);
    calculateKnobValue(i);
  }
  knobReadIndex++;
  if (knobReadIndex >= KNOB_HISTORY_SIZE) {
    knobReadIndex = 0;
  }

  // ------------- ROTARY ENCODER -------------
  // Read encoder rotation
  static bool encoderALast = LOW;
  static int encoderButtonLastState = HIGH;
  static int encoderButtonState;
  static int encoderLastDebounceTime = 0;

  bool encoderA = digitalRead(PIN_ENCODER_A);
  if ((encoderALast == HIGH) && (encoderA == LOW)) {
    if (digitalRead(PIN_ENCODER_B)) {
      encoderState = ENCODER_UP;
    } else {
      encoderState = ENCODER_DOWN;
    }
  }
  encoderALast = encoderA;

  // Read encoder button debounced
  int reading = digitalRead(PIN_ENCODER_CLICK);
  if (reading != encoderButtonLastState) {
    encoderLastDebounceTime = millis();
  }

  if ((millis() - encoderLastDebounceTime) > DEBOUNCE_DELAY) {
    if (reading != encoderButtonState) {
      encoderButtonState = reading;

      if (encoderButtonState == LOW) {
        encoderButtonPressed = true;
      }
    }
  }
  encoderButtonLastState = reading;

  // ------------- DEBUG OUTPUT -------------
  static int displayDelay = 0;
  displayDelay++;
  if (displayDelay > 1000) {
    Serial.printf("Buttons: ");
    for(int i = 0; i < NUM_BUTTONS; i++) {
      Serial.printf("%d: %d, ", i + 1, getButtonValue(i));
    }
    Serial.printf("\n");

    Serial.printf("Potentiometers: ");
    for(int i = 0; i < NUM_KNOBS; i++) {
      Serial.printf("%d: %d, ", i + 1, getKnobValue(i));
    }
    Serial.printf("\n");

    displayDelay = 0;
  }
}


EncoderState Controls::getEncoderState() {
  EncoderState temp = encoderState;
  encoderState = ENCODER_UNCHANGED;

  return temp;
}


bool Controls::encoderPressed() {
  bool temp = encoderButtonPressed;
  encoderButtonPressed = false;

  return temp;
}


// Don't call this more than once per input polling cycle or previousKnobReads will get messed up.
void Controls::calculateKnobValue(int knob) {
  bool prevIsLessOrEqual = previousKnobReads[knob] <= knobValues[knob];
  word nextRead = getKnobRead(knob);
  bool nextIsGreaterOrEqual = nextRead >= knobValues[knob];
  if (!knobInputActive[knob] && prevIsLessOrEqual == nextIsGreaterOrEqual) {
    knobInputActive[knob] = true;
  }

  if (knobInputActive[knob]) {
    knobValues[knob] = nextRead;
  }
  previousKnobReads[knob] = nextRead;
}


int Controls::getKnobRead(int knob) {
  int value = 0;
  for (int i = 0; i < KNOB_HISTORY_SIZE; i++) {
    value += knobReads[knob][i] >> KNOB_DROP_BITS;
  }

  value /= KNOB_HISTORY_SIZE;

  // Do not change if the change in value is only one step unless min or max -- this is for hysteresis
  if (value == 0 || value == 1023 >> KNOB_DROP_BITS || abs(previousKnobReads[knob] - value) > 1) {
    return value;
  } else {
    return previousKnobReads[knob];
  }
}


word Controls::getKnobValue(int knob) {
  return knobValues[knob];
}


void Controls::setKnobValue(int knob, word value) {
  knobValues[knob] = value;
}


void Controls::resetKnobInputs() {
  for (int i = 0; i < NUM_KNOBS; i++) {
    knobInputActive[i] = false;
  }
}


void Controls::buttonMod(int button, int modulus) {
  buttonValues[button] %= modulus;
}


word Controls::getButtonValue(int button) {
  return buttonValues[button];
}


void Controls::setMultiplexerPins(int index) {
  digitalWrite(PIN_MULTI_S0, bitRead(index, 0));
  digitalWrite(PIN_MULTI_S1, bitRead(index, 1));
  digitalWrite(PIN_MULTI_S2, bitRead(index, 2));
  digitalWrite(PIN_MULTI_S3, bitRead(index, 3));
}


word Controls::getPotReading(int potIndex) {
  digitalWrite(PIN_MULTI_E, 0);
  setMultiplexerPins(potIndex);
  digitalWrite(PIN_MULTI_E, 1);
  return analogRead(PIN_MULTI_SIG);
}
