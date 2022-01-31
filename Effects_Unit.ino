//#include <ST7735_t3.h>
//#include <SPI.h>
//#include "Patch.h"
#include "AudioEngine.h"
#include "TftGui.h"


//const int PIN_ENCODER_A = 16;
//const int PIN_ENCODER_B = 17;
//const int PIN_ENCODER_CLICK = 22;


const int PIN_DISPLAY_CLK = 13;
const int PIN_DISPLAY_MOSI = 11;
const int PIN_DISPLAY_DC = 9;
const int PIN_DISPLAY_RST = 8;
const int PIN_DISPLAY_CS = 10;
/*#define TFT_DC      20
#define TFT_CS      21
#define TFT_RST    255  // 255 = unused, connect to 3.3V
#define TFT_MOSI     7
#define TFT_SCLK    14
#define TFT_MISO    12*/
/*const int PIN_DISPLAY_CLK = 14;
const int PIN_DISPLAY_MOSI = 7;
const int PIN_DISPLAY_DC = 20;
const int PIN_DISPLAY_RST = 255;  // 255 = unused, connect to 3.3V
const int PIN_DISPLAY_CS = 21;*/


ST7735_t3 tft = ST7735_t3(PIN_DISPLAY_CS, PIN_DISPLAY_DC, PIN_DISPLAY_MOSI, PIN_DISPLAY_CLK, PIN_DISPLAY_RST);
Window window(tft);


void setup() {
  Serial.begin(9600);
  
//  pinMode(PIN_ENCODER_A, INPUT_PULLUP);
//  pinMode(PIN_ENCODER_B, INPUT_PULLUP);
//  pinMode(PIN_ENCODER_CLICK, INPUT_PULLUP);

  initAudioEngine(usbMIDI);

  window.initDisplay();
  window.createTestData();
  window.invalidate();
}

void loop() {
  static int i = 0;
  i++;
  if (i == 1000) {
    i = 0;
    Serial.printf("Usage: memory %d / processor %f\n", AudioMemoryUsageMax(), AudioProcessorUsageMax());
  }  

/*  static bool encoderALast = LOW;
  
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
  }*/
  
  window.render();

  Effect *effect1 = window.getEffect(0);
//  Effect *effect2 = window.getEffect(1);
  if (effect1->usesSynthMidi) {
    processMidi(usbMIDI);
  }  
  processAudioEngine();
//  processAudio(effect1, effect2);
}
