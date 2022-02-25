#include "AudioEngine.h"
#include "TftGui.h"
#include "TeensyPins.h"
#include "Util.h"


ST7735_t3 tft = ST7735_t3(PIN_DISPLAY_CS, PIN_DISPLAY_DC, PIN_DISPLAY_MOSI, PIN_DISPLAY_CLK, PIN_DISPLAY_RST);
Window window(tft);


void setMultiplexerPins(int index) {
  digitalWrite(PIN_MULTI_S0, bitRead(index, 0));
  digitalWrite(PIN_MULTI_S1, bitRead(index, 1));
  digitalWrite(PIN_MULTI_S2, bitRead(index, 2));
  digitalWrite(PIN_MULTI_S3, bitRead(index, 3));
}


word getPotReading(int potIndex) {
  digitalWrite(PIN_MULTI_E, 0);
  setMultiplexerPins(potIndex);
  digitalWrite(PIN_MULTI_E, 1);
  return analogRead(PIN_MULTI_SIG);
}


void pollInput() {
  static bool encoderALast = LOW;
  static int encoderButtonLastState = HIGH;
  static int encoderButtonState;
  static int lastDebounceTime = 0;
  
/*  for(int i = 0; i < 6; i++) {
    Serial.printf("Potentiometer %d: %d\n", i + 1, getPotReading(i));
  }
  Serial.printf("Potentiometer DIRECT: %d\n", analogRead(25));*/

  // Read encoder rotation
  bool encoderA = digitalRead(PIN_ENCODER_A);
  if ((encoderALast == HIGH) && (encoderA == LOW)) {
    if (digitalRead(PIN_ENCODER_B)) {
      window.scrollUp();
    } else {
      window.scrollDown();
    }
  }
  encoderALast = encoderA;

  // Read encoder button debounced
  int reading = digitalRead(PIN_ENCODER_CLICK);
  if (reading != encoderButtonLastState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (reading != encoderButtonState) {
      encoderButtonState = reading;

      if (encoderButtonState == LOW) {
        window.select();
      }
    }
  }
  encoderButtonLastState = reading;
}


void setup() {
  Serial.begin(9600);
  
  pinMode(PIN_ENCODER_A, INPUT_PULLUP);
  pinMode(PIN_ENCODER_B, INPUT_PULLUP);
  pinMode(PIN_ENCODER_CLICK, INPUT_PULLUP);

  pinMode(PIN_MULTI_S0, OUTPUT);
  pinMode(PIN_MULTI_S1, OUTPUT);
  pinMode(PIN_MULTI_S2, OUTPUT);
  pinMode(PIN_MULTI_S3, OUTPUT);

  window.initDisplay();
  window.createTestData();
  window.invalidate();

  // initAudioEngine must be last to make sure the AudioRecordQueue.begin is the last thing called in setup. Otherwise we get latency issues
  // from a delay before the buffer is picked up and pushed to the playback queue.
  initAudioEngine(usbMIDI);
}

void loop() {
  Effect *effect1 = window.getEffect(0);
  Effect *effect2 = window.getEffect(1);
  // processAudioEngine needs to be first. See above notes.
  processAudioEngine(effect1, effect2);
  if (effect1->usesSynthMidi) {
    processMidi(usbMIDI);
  }

  static int i = 0;
  i++;
  if (i == 1000) {
    i = 0;
//    Serial.printf("Usage: memory %d / processor %f\n", AudioMemoryUsageMax(), AudioProcessorUsageMax());
    pollInput();
  }  
  
  window.render();
}
