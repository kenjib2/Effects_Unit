#include <USBHost_t36.h>
#include <LittleFS.h>
#include "AudioEngine.h"
#include "TftGui.h"
#include "TeensyPins.h"
#include "Util.h"
#include "Controls.h"


ST7735_t3 tft = ST7735_t3(PIN_DISPLAY_CS, PIN_DISPLAY_DC, PIN_DISPLAY_MOSI, PIN_DISPLAY_CLK, PIN_DISPLAY_RST);
Window window(tft);
USBHost usbHost;
MIDIDevice usbMidi(usbHost);
Controls * controls;
LittleFS_QSPIFlash myfs;


void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  
  pinMode(PIN_ENCODER_A, INPUT_PULLUP);
  pinMode(PIN_ENCODER_B, INPUT_PULLUP);
  pinMode(PIN_ENCODER_CLICK, INPUT_PULLUP);

  pinMode(PIN_BUTTON_BLUE, INPUT_PULLUP);
  pinMode(PIN_BUTTON_RED, INPUT_PULLUP);
  pinMode(PIN_BUTTON_YELLOW, INPUT_PULLUP);
  pinMode(PIN_BUTTON_GREEN, INPUT_PULLUP);

  pinMode(PIN_MULTI_S0, OUTPUT);
  pinMode(PIN_MULTI_S1, OUTPUT);
  pinMode(PIN_MULTI_S2, OUTPUT);
  pinMode(PIN_MULTI_S3, OUTPUT);

  controls = new Controls();

  // put your setup code here, to run once:
 if (!myfs.begin()) {
    Serial.printf("Error starting %s\n", "QSPI");
    while (1) {
      // Flash error, so don't do anything more - stay stuck here
    }
 }
  Serial.println("QSPI Initialized.");

  window.initDisplay();
//  window.createTestData();
//  window.savePatch(&myfs, controls, 1);
  printDirectory(myfs);
  window.loadPatch(&myfs, controls, "001.Dark Neutron Star.dat");
  window.invalidate();

  usbHost.begin();

  // initAudioEngine must be last to make sure the AudioRecordQueue.begin is the last thing called in setup. Otherwise we get latency issues
  // from a delay before the buffer is picked up and pushed to the playback queue.
  initAudioEngine(&usbMidi);

}

void loop() {
  Effect *effect1 = window.getEffect(0);
  Effect *effect2 = window.getEffect(1);
  // processAudioEngine needs to be first. See above notes.
  processAudioEngine(effect1, effect2, controls);
  if (effect1->usesSynthMidi) {
    usbHost.Task();
    processMidi();
  }

  static int i = 0;
  i++;
  if (i == 1000) {
    i = 0;
//    Serial.printf("Usage: memory %d / processor %f\n", AudioMemoryUsageMax(), AudioProcessorUsageMax());
    controls->pollInput();
    EncoderState encoderState = controls->getEncoderState();
    if (encoderState == ENCODER_UP) {
      window.scrollUp();
    } else if (encoderState == ENCODER_DOWN) {
      window.scrollDown();
    }
    if (controls->encoderPressed()) {
      window.select();
    }
  }  
  
  window.render();
}
