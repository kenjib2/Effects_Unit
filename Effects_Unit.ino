#include <ST7735_t3.h>
#include <SPI.h>
#include "TftGui.h"
#include "SubtractiveSynthEngine.h"


const int PIN_DISPLAY_CLK = 13;
const int PIN_DISPLAY_MOSI = 11;
const int PIN_DISPLAY_DC = 9;
const int PIN_DISPLAY_RST = 8;
const int PIN_DISPLAY_CS = 10;

const int PIN_ENCODER_A = 16;
const int PIN_ENCODER_B = 17;
const int PIN_ENCODER_CLICK = 22;


ST7735_t3 tft = ST7735_t3(PIN_DISPLAY_CS, PIN_DISPLAY_DC, PIN_DISPLAY_MOSI, PIN_DISPLAY_CLK, PIN_DISPLAY_RST);
Window window(tft);


void setup() {
  pinMode(PIN_ENCODER_A, INPUT_PULLUP);
  pinMode(PIN_ENCODER_B, INPUT_PULLUP);
  pinMode(PIN_ENCODER_CLICK, INPUT_PULLUP);

  window.initDisplay();
  window.createTestData();
  window.invalidate();

  initSynthEngine(usbMIDI);
}


void loop() {
  static bool encoderALast = LOW;
  
  bool encoderA = digitalRead(PIN_ENCODER_A);
  if ((encoderALast == HIGH) && (encoderA == LOW)) {
    if (digitalRead(PIN_ENCODER_B)) {
      window.scrollUp();
    } else {
      window.scrollDown();
    }
  }
  encoderALast = encoderA;

  if (digitalRead(PIN_ENCODER_CLICK) == LOW) {
    window.select();
  }

  window.render();

  usbMIDI.read();
}
