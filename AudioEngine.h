#include <Audio.h>
#include <USBHost_t36.h>
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


void initAudioEngine(MIDIDevice * midiDevice);
void processMidi();
void processAudioEngine(Effect * effect1, Effect * effect2, Controls * controls);
void setKnob(int knobNumber, short value);


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
