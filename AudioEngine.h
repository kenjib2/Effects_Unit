#include <Audio.h>

void initializeAudioEngine(usb_midi_class usbMIDIControl);
void processAudioEngine(usb_midi_class usbMIDIControl);
void keyBuff(byte note, bool playNote);
void vcoTrigger(byte note, bool triggerEnvelope);
void vcoStop();
void vcoSet();
void myNoteOn(byte channel, byte note, byte velocity);
void myNoteOff(byte channel, byte note, byte velocity);
void myPitchBend(byte channel, int bend);
void myControlChange(byte channel, byte control, byte value);


/*
#include "Patch.h"


void initAudioEngine();
void processAudio();
//void processAudio(Effect effect1, Effect effect2);
void initSynthEngine(usb_midi_class usbMIDIControl);
void midiControlChange(byte channel, byte control, byte value);
void midiNoteOn(byte channel, byte note, byte velocity);
void midiNoteOff(byte channel, byte note, byte velocity);
void midiPitchChange(byte channel, int bend);
void keyBuff(byte note, bool playNote);
void oscPlay(byte note, bool triggerEnvelope);
void oscStop();
void updateOscFrequency();
*/
