#include <Audio.h>

void initAudioEngine(usb_midi_class usbMIDIControl);
void processMidi(usb_midi_class usbMIDIControl);
void processAudioEngine();
void keyBuff(byte note, bool playNote);
void vcoTrigger(byte note, bool triggerEnvelope);
void vcoStop();
void vcoUpdateFrequency();
void midiNoteOn(byte channel, byte note, byte velocity);
void midiNoteOff(byte channel, byte note, byte velocity);
void midiPitchBend(byte channel, int bend);
void midiControlChange(byte channel, byte control, byte value);
