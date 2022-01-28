void initSynthEngine(usb_midi_class usbMIDIControl);
void midiControlChange(byte channel, byte control, byte value);
void midiNoteOn(byte channel, byte note, byte velocity);
void midiNoteOff(byte channel, byte note, byte velocity);
void midiPitchChange(byte channel, int bend);
void keyBuff(byte note, bool playNote);
void oscPlay(byte note, bool triggerEnvelope);
void oscStop();
void updateOscFrequency();
