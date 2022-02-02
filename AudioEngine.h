#include <Audio.h>
#include "patch.h"


typedef struct _MidiNote {
  byte note;
  byte velocity;
  byte channel;
  byte vcoNumber;
} MidiNote;


enum SynthMode {
    Monophonic
  , LastNotePriority
};


void initAudioEngine(usb_midi_class usbMIDIControl);
void processMidi(usb_midi_class usbMIDIControl);
void processAudioEngine(Effect * effect1, Effect * effect2);
void setSynthMode(SynthMode mode);
void addBufferNote(MidiNote midiNote);
void removeBufferNote(MidiNote midiNote);
void vcoTrigger(MidiNote midiNote);
void envelopeTrigger(MidiNote midiNote);
void vcoStop(MidiNote midiNote);
void vcoUpdateFrequency();
void vcoStopAllNotes();
void midiNoteOn(byte channel, byte note, byte velocity);
void midiNoteOff(byte channel, byte note, byte velocity);
void midiPitchBend(byte channel, int bend);
void midiControlChange(byte channel, byte control, byte value);
