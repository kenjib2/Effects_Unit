#include <Audio.h>

void initializeAudioEngine(usb_midi_class usbMIDIControl);
void processAudioEngine(usb_midi_class usbMIDIControl);
void keyBuff(byte note, bool playNote);
void vcoTrigger(byte note, bool triggerEnvelope);
void vcoStop();
void vcoUpdateFrequency();
void midiNoteOn(byte channel, byte note, byte velocity);
void midiNoteOff(byte channel, byte note, byte velocity);
void midiPitchBend(byte channel, int bend);
void midiControlChange(byte channel, byte control, byte value);
