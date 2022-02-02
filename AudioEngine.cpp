#include "AudioEngine.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       lfo;            //xy=65,544
AudioInputI2S            i2s1;           //xy=117,65
AudioSynthWaveformDc     vcoPulseWidth_1;  //xy=215,355
AudioSynthWaveformDc     vcoPulseWidth_2; //xy=220,708
AudioMixer4              vcoModMixer_1;    //xy=231,290
AudioMixer4              vcoModMixer_2; //xy=236,643
AudioRecordQueue         effect1In;      //xy=265,66
AudioSynthWaveformDc     envelopeDc_1;     //xy=265,475
AudioSynthWaveformDc     envelopeDc_2; //xy=287,830
AudioSynthNoisePink      pinkNoise_1;      //xy=385,403
AudioSynthWaveformModulated vco1_1;           //xy=386,296
AudioSynthWaveformModulated vco2_1;           //xy=388,350
AudioSynthNoisePink      pinkNoise_2; //xy=390,756
AudioSynthWaveformModulated vco1_2; //xy=391,649
AudioSynthWaveformModulated vco2_2; //xy=393,703
AudioPlayQueue           effect1Out;     //xy=402,65
AudioEffectEnvelope      envelope_1;       //xy=428,475
AudioEffectEnvelope      envelope_2; //xy=433,828
AudioMixer4              synthPolyphony;         //xy=451,149
AudioMixer4              vcoMixer_1;       //xy=541,349
AudioMixer4              vcoMixer_2; //xy=546,702
AudioMixer4              vcfModMixer_1;    //xy=591,417
AudioMixer4              vcfModMixer_2; //xy=596,770
AudioMixer4              synthMixer;     //xy=612,60
AudioFilterLadder        vcf_1;            //xy=685,345
AudioFilterLadder        vcf_2; //xy=690,698
AudioRecordQueue         effect2In;      //xy=757,60
AudioEffectEnvelope      vcaPassThroughEnvelope_1; //xy=776,280
AudioSynthWaveformDc     vcaLfoDcOffset_1; //xy=778,450
AudioEffectEnvelope      vcaPassThroughEnvelope_2; //xy=781,633
AudioSynthWaveformDc     vcaLfoDcOffset_2; //xy=783,803
AudioEffectMultiply      vca_1;            //xy=811,406
AudioEffectMultiply      vca_2; //xy=816,759
AudioPlayQueue           effect2Out;     //xy=883,59
AudioMixer4              vcaMixer_1;       //xy=925,343
AudioMixer4              vcaMixer_2; //xy=930,696
AudioMixer4              vcaLfoAmount_1;   //xy=976,456
AudioMixer4              vcaLfoAmount_2; //xy=981,809
AudioOutputI2S           audioOut;       //xy=1052,60
AudioEffectMultiply      vcaLfoMod_1;      //xy=1085,349
AudioEffectMultiply      vcaLfoMod_2;   //xy=1090,702
AudioConnection          patchCord1(lfo, 0, vcaLfoAmount_1, 0);
AudioConnection          patchCord2(lfo, 0, vcoModMixer_1, 1);
AudioConnection          patchCord3(lfo, 0, vcfModMixer_1, 1);
AudioConnection          patchCord4(lfo, 0, vcoModMixer_2, 1);
AudioConnection          patchCord5(lfo, 0, vcaLfoAmount_2, 0);
AudioConnection          patchCord6(lfo, 0, vcfModMixer_2, 1);
AudioConnection          patchCord7(i2s1, 0, effect1In, 0);
AudioConnection          patchCord8(vcoPulseWidth_1, 0, vco1_1, 1);
AudioConnection          patchCord9(vcoPulseWidth_1, 0, vco2_1, 1);
AudioConnection          patchCord10(vcoPulseWidth_2, 0, vco1_2, 1);
AudioConnection          patchCord11(vcoPulseWidth_2, 0, vco2_2, 1);
AudioConnection          patchCord12(vcoModMixer_1, 0, vco1_1, 0);
AudioConnection          patchCord13(vcoModMixer_1, 0, vco2_1, 0);
AudioConnection          patchCord14(vcoModMixer_2, 0, vco1_2, 0);
AudioConnection          patchCord15(vcoModMixer_2, 0, vco2_2, 0);
AudioConnection          patchCord16(envelopeDc_1, envelope_1);
AudioConnection          patchCord17(envelopeDc_2, envelope_2);
AudioConnection          patchCord18(pinkNoise_1, 0, vcoMixer_1, 2);
AudioConnection          patchCord19(vco1_1, 0, vcoMixer_1, 0);
AudioConnection          patchCord20(vco2_1, 0, vcoMixer_1, 1);
AudioConnection          patchCord21(pinkNoise_2, 0, vcoMixer_2, 2);
AudioConnection          patchCord22(vco1_2, 0, vcoMixer_2, 0);
AudioConnection          patchCord23(vco2_2, 0, vcoMixer_2, 1);
AudioConnection          patchCord24(effect1Out, 0, synthMixer, 0);
AudioConnection          patchCord25(envelope_1, 0, vca_1, 1);
AudioConnection          patchCord26(envelope_1, 0, vcoModMixer_1, 0);
AudioConnection          patchCord27(envelope_1, 0, vcfModMixer_1, 0);
AudioConnection          patchCord28(envelope_2, 0, vca_2, 1);
AudioConnection          patchCord29(envelope_2, 0, vcoModMixer_2, 0);
AudioConnection          patchCord30(envelope_2, 0, vcfModMixer_2, 0);
AudioConnection          patchCord31(synthPolyphony, 0, synthMixer, 1);
AudioConnection          patchCord32(vcoMixer_1, 0, vcf_1, 0);
AudioConnection          patchCord33(vcoMixer_2, 0, vcf_2, 0);
AudioConnection          patchCord34(vcfModMixer_1, 0, vcf_1, 1);
AudioConnection          patchCord35(vcfModMixer_2, 0, vcf_2, 1);
AudioConnection          patchCord36(synthMixer, effect2In);
AudioConnection          patchCord37(vcf_1, vcaPassThroughEnvelope_1);
AudioConnection          patchCord38(vcf_1, 0, vca_1, 0);
AudioConnection          patchCord39(vcf_2, vcaPassThroughEnvelope_2);
AudioConnection          patchCord40(vcf_2, 0, vca_2, 0);
AudioConnection          patchCord41(vcaPassThroughEnvelope_1, 0, vcaMixer_1, 0);
AudioConnection          patchCord42(vcaLfoDcOffset_1, 0, vcaLfoAmount_1, 1);
AudioConnection          patchCord43(vcaPassThroughEnvelope_2, 0, vcaMixer_2, 0);
AudioConnection          patchCord44(vcaLfoDcOffset_2, 0, vcaLfoAmount_2, 1);
AudioConnection          patchCord45(vca_1, 0, vcaMixer_1, 1);
AudioConnection          patchCord46(vca_2, 0, vcaMixer_2, 1);
AudioConnection          patchCord47(effect2Out, 0, audioOut, 0);
AudioConnection          patchCord48(effect2Out, 0, audioOut, 1);
AudioConnection          patchCord49(vcaMixer_1, 0, vcaLfoMod_1, 0);
AudioConnection          patchCord50(vcaMixer_2, 0, vcaLfoMod_2, 0);
AudioConnection          patchCord51(vcaLfoAmount_1, 0, vcaLfoMod_1, 1);
AudioConnection          patchCord52(vcaLfoAmount_2, 0, vcaLfoMod_2, 1);
AudioConnection          patchCord53(vcaLfoMod_1, 0, synthPolyphony, 0);
AudioConnection          patchCord54(vcaLfoMod_2, 0, synthPolyphony, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1051,117
// GUItool: end automatically generated code


const byte MAX_BUFFER = 8; //Size of keyboard buffer
const byte NUM_VOICES = 2; // Number of polyphony voices
const float noteFreqs[128] = {8.176, 8.662, 9.177, 9.723, 10.301, 10.913, 11.562, 12.25, 12.978, 13.75, 14.568, 15.434, 16.352, 17.324, 18.354, 19.445, 20.602, 21.827, 23.125, 24.5, 25.957, 27.5, 29.135, 30.868, 32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55, 58.27, 61.735, 65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659, 1244.508, 1318.51, 1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533, 2093.005, 2217.461, 2349.318, 2489.016, 2637.02, 2793.826, 2959.955, 3135.963, 3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922, 4698.636, 4978.032, 5274.041, 5587.652, 5919.911, 6271.927, 6644.875, 7040, 7458.62, 7902.133, 8372.018, 8869.844, 9397.273, 9956.063, 10548.08, 11175.3, 11839.82, 12543.85};
const float DIV127 = (1.0 / 127.0);

const int MAX_FILTER_FREQ = 10000;
const int FILTER_OCTAVE_CONTROL = 4.0;
const float Q_RATIO = 1.2;
const float Q_FLOOR = 0.0;
const float MIN_LFO_FREQ = 0.1;
const float MAX_LFO_FREQ = 12.0;


// GLOBAL VARIABLES
byte globalNote = 0;
int octave = 0;
float detuneFactor = 1;
float bendFactor = 1;
int bendRange = 12;
MidiNote noteBuffer[MAX_BUFFER];
byte notesBuffered = 0;
bool vcoPlaying[2];


void initAudioEngine(usb_midi_class usbMIDIControl) {
  AudioMemory(1024);

  synthMixer.gain(0, 1.0);
  synthMixer.gain(1, 1.0);

  synthPolyphony.gain(0, 0.8);
  synthPolyphony.gain(1, 0.8);
  synthPolyphony.gain(2, 0.8);
  synthPolyphony.gain(3, 0.8);

  effect1In.begin();
  effect2In.begin();

  usbMIDIControl.setHandleControlChange(midiControlChange);
  usbMIDIControl.setHandleNoteOff(midiNoteOff);
  usbMIDIControl.setHandleNoteOn(midiNoteOn);
  usbMIDIControl.setHandlePitchChange(midiPitchBend);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.70);

  vcoPlaying[0] = false;
  vcoPlaying[1] = false;

  vco1_1.begin(WAVEFORM_SAWTOOTH);
  vco1_1.amplitude(0.75);
  vco1_1.frequency(82.41);
  vco1_2.begin(WAVEFORM_SAWTOOTH);
  vco1_2.amplitude(0.75);
  vco1_2.frequency(82.41);

  vco2_1.begin(WAVEFORM_SAWTOOTH);
  vco2_1.amplitude(0.75);
  vco2_1.frequency(123);
  vco2_2.begin(WAVEFORM_SAWTOOTH);
  vco2_2.amplitude(0.75);
  vco2_2.frequency(123);

  vcoPulseWidth_1.amplitude(0.5);
  vcoPulseWidth_2.amplitude(0.5);

  pinkNoise_1.amplitude(1.0);
  pinkNoise_2.amplitude(1.0);

  vcoModMixer_1.gain(0, 0.0);
  vcoModMixer_1.gain(1, 0.0);
  vcoModMixer_2.gain(0, 0.0);
  vcoModMixer_2.gain(1, 0.0);

  vcoMixer_1.gain(0, 1.0);
  vcoMixer_1.gain(1, 1.0);
  vcoMixer_1.gain(2, 0.0);
  vcoMixer_2.gain(0, 1.0);
  vcoMixer_2.gain(1, 1.0);
  vcoMixer_2.gain(2, 0.0);

  vcf_1.resonance(Q_FLOOR);
  vcf_1.frequency(MAX_FILTER_FREQ);
  vcf_1.octaveControl(FILTER_OCTAVE_CONTROL);
  vcf_2.resonance(Q_FLOOR);
  vcf_2.frequency(MAX_FILTER_FREQ);
  vcf_2.octaveControl(FILTER_OCTAVE_CONTROL);

  vcfModMixer_1.gain(0, 0.0);
  vcfModMixer_1.gain(1, 0.0);
  vcfModMixer_2.gain(0, 0.0);
  vcfModMixer_2.gain(1, 0.0);

  vcaPassThroughEnvelope_1.attack(1);
  vcaPassThroughEnvelope_1.decay(0);
  vcaPassThroughEnvelope_1.sustain(1);
  vcaPassThroughEnvelope_1.release(1);
  vcaPassThroughEnvelope_2.attack(1);
  vcaPassThroughEnvelope_2.decay(0);
  vcaPassThroughEnvelope_2.sustain(1);
  vcaPassThroughEnvelope_2.release(1);

  vcaMixer_1.gain(0, 0.0);
  vcaMixer_1.gain(1, 1.0);
  vcaMixer_2.gain(0, 0.0);
  vcaMixer_2.gain(1, 1.0);

  vcaLfoDcOffset_1.amplitude(1.0);
  vcaLfoDcOffset_2.amplitude(1.0);

  vcaLfoAmount_1.gain(0, 0.0);
  vcaLfoAmount_1.gain(1, 1.0);
  vcaLfoAmount_2.gain(0, 0.0);
  vcaLfoAmount_2.gain(1, 1.0);

  envelopeDc_1.amplitude(1.0);
  envelopeDc_2.amplitude(1.0);

  envelope_1.attack(1);
  envelope_1.decay(0);
  envelope_1.sustain(1);
  envelope_1.release(1);
  envelope_2.attack(1);
  envelope_2.decay(0);
  envelope_2.sustain(1);
  envelope_2.release(1);

  lfo.begin(WAVEFORM_TRIANGLE);
  lfo.amplitude(1.0);
  lfo.frequency(1.0);
  lfo.pulseWidth(0.5);
}

void processMidi(usb_midi_class usbMIDIControl) {
  usbMIDIControl.read();
}

void processAudioEngine(Effect * effect1, Effect * effect2) {
  if (effect1In.available() >= 1) {
    int16_t *audioBuffer = effect1Out.getBuffer();
    memcpy(audioBuffer, effect1In.readBuffer(), 256);
    effect1In.freeBuffer();
    effect1->processEffect(audioBuffer);
    effect1Out.playBuffer();
  }

  if (effect2In.available() >= 1) {
    int16_t *audioBuffer = effect2Out.getBuffer();
    memcpy(audioBuffer, effect2In.readBuffer(), 256);
    effect2In.freeBuffer();
    effect2->processEffect(audioBuffer);
    effect2Out.playBuffer();
  }
}

int getNextOscillator() {
  for (int i = 0; i < NUM_VOICES; i++) {
    if (!vcoPlaying[i]) {
      return i;
    }
  }

  return -1;  
}

void addBufferNote(MidiNote midiNote) {
  /*
   * Need to add mono mode
      if (buffSize < MAX_BUFFER) {
   */
  if (notesBuffered >= NUM_VOICES) {
    removeBufferNote(noteBuffer[0]);    
  }
  int nextVcoNumber = getNextOscillator();
  vcoPlaying[midiNote.vcoNumber] = true;
  midiNote.vcoNumber = nextVcoNumber;
  noteBuffer[notesBuffered] = midiNote;
  notesBuffered++;
  vcoTrigger(midiNote);
  envelopeTrigger(midiNote);
}

void removeBufferNote(MidiNote midiNote) {
  if (notesBuffered > 0) {
    for (int i = 0; i < notesBuffered; i++) {
      if (noteBuffer[i].note == midiNote.note) {
        MidiNote removedNote = noteBuffer[i];
        for (int j = i; j < notesBuffered - 1; j++) {
          // Shift all notes down to replace the removed note
          noteBuffer[j] = noteBuffer[j + 1];
        }
        vcoStop(removedNote);
        vcoPlaying[removedNote.vcoNumber] = false;
        notesBuffered--;
      }
    }
  }
}

void vcoTrigger(MidiNote midiNote) {
  float velo = (midiNote.velocity * DIV127);
  switch (midiNote.vcoNumber) {
    case 0:
      vco1_1.frequency(noteFreqs[midiNote.note] * bendFactor);
      vco2_1.frequency(noteFreqs[midiNote.note + octave] * detuneFactor * bendFactor);
      vco1_1.amplitude(velo);
      vco2_1.amplitude(velo);
      pinkNoise_1.amplitude(velo);
      break;
    case 1:
      vco1_2.frequency(noteFreqs[midiNote.note] * bendFactor);
      vco2_2.frequency(noteFreqs[midiNote.note + octave] * detuneFactor * bendFactor);
      vco1_2.amplitude(velo);
      vco2_2.amplitude(velo);
      pinkNoise_2.amplitude(velo);
      break;
  }
}

void envelopeTrigger(MidiNote midiNote) {
  switch (midiNote.vcoNumber) {
    case 0:
      envelope_1.noteOn();
      vcaPassThroughEnvelope_1.noteOn();
      break;
    case 1:
      envelope_2.noteOn();
      vcaPassThroughEnvelope_2.noteOn();
      break;
  }
}

void vcoStop(MidiNote midiNote) {
  switch (midiNote.vcoNumber) {
    case 0:
      envelope_1.noteOff();
      vcaPassThroughEnvelope_1.noteOff();
      break;
    case 1:
      envelope_2.noteOff();
      vcaPassThroughEnvelope_2.noteOff();
      break;
  }
}

void vcoUpdateFrequency() {
  for (int i = 0; i < notesBuffered; i++) {
    MidiNote midiNote = noteBuffer[i];
    switch (midiNote.vcoNumber) {
      case 0:
        vco1_1.frequency(noteFreqs[midiNote.note] * bendFactor);
        vco2_1.frequency(noteFreqs[midiNote.note + octave] * detuneFactor * bendFactor);
        break;
      case 1:
        vco1_2.frequency(noteFreqs[midiNote.note] * bendFactor);
        vco2_2.frequency(noteFreqs[midiNote.note + octave] * detuneFactor * bendFactor);
        break;
    }
  }
}

void midiNoteOn(byte channel, byte note, byte velocity) {
  MidiNote midiNote;
  midiNote.note = note;
  midiNote.velocity = velocity;
  midiNote.channel = channel;
  
  if ( note > 23 && note < 108 ) {
    addBufferNote(midiNote);
  }
}

void midiNoteOff(byte channel, byte note, byte velocity) {
  MidiNote midiNote;
  midiNote.note = note;
  midiNote.velocity = velocity;
  midiNote.channel = channel;

  if ( note > 23 && note < 108 ) {
    removeBufferNote(midiNote);
  }
}

void midiPitchBend(byte channel, int bend) {
  float bendF = bend;
  bendF = bendF / 8192;
  bendF = bendF * bendRange;
  bendF = bendF / 12;
  bendFactor = pow(2, bendF);
  vcoUpdateFrequency();
}

void midiControlChange(byte channel, byte control, byte value) {
  float floatVal = 0.0;

  switch (control) {

    // ============================== VCO Controls ==============================
    case 102:
      // VCO 1 Level
      vcoMixer_1.gain(0, (value * DIV127));
      vcoMixer_2.gain(0, (value * DIV127));
      break;

    case 103:
      // VCO 2 Level
      vcoMixer_1.gain(1, (value * DIV127));
      vcoMixer_2.gain(1, (value * DIV127));
      break;

    case 104:
      // Pink Noise Level
      vcoMixer_1.gain(2, (value * DIV127));
      vcoMixer_2.gain(2, (value * DIV127));
      break;

    case 105:
      // VCO 1 Waveform
      switch (value) {
        case 0:
          vco1_1.begin(WAVEFORM_SINE);
          vco1_2.begin(WAVEFORM_SINE);
          break;
        case 1:
          vco1_1.begin(WAVEFORM_TRIANGLE);
          vco1_2.begin(WAVEFORM_TRIANGLE);
          break;
        case 2:
          vco1_1.begin(WAVEFORM_PULSE);
          vco1_2.begin(WAVEFORM_PULSE);
          break;
        case 3:
          vco1_1.begin(WAVEFORM_SAWTOOTH);
          vco1_2.begin(WAVEFORM_SAWTOOTH);
          break;
      }
      break;

    case 106:
      // VCO 2 Waveform
      switch (value) {
        case 0:
          vco2_1.begin(WAVEFORM_SINE);
          vco2_2.begin(WAVEFORM_SINE);
          break;
        case 1:
          vco2_1.begin(WAVEFORM_TRIANGLE);
          vco2_2.begin(WAVEFORM_TRIANGLE);
          break;
        case 2:
          vco2_1.begin(WAVEFORM_PULSE);
          vco2_2.begin(WAVEFORM_PULSE);
          break;
        case 3:
          vco2_1.begin(WAVEFORM_SAWTOOTH);
          vco2_2.begin(WAVEFORM_SAWTOOTH);
          break;
      }
      break;

    case 107:
      // VCO 2 Octave
      switch (value) {
        case 0:
          octave = 24;
          break;
        case 1:
          octave = 12;
          break;
        case 2:
          octave = 0;
          break;
        case 3:
          octave = -12;
          break;
        case 4:
          octave = -24;
          break;
      }
      vcoUpdateFrequency();
      break;

    case 108:
      // VCO 2 Detune
      detuneFactor = 1 - (0.05 * (value * DIV127));
      vcoUpdateFrequency();
      break;

    case 109:
      // Pitch Bend Range
      if (value <= 12 && value > 0) bendRange = value;
      break;

    case 110:
      // VCO Env
      vcoModMixer_1.gain(0, (value - 64) * DIV127 * 0.25);
      vcoModMixer_2.gain(0, (value - 64) * DIV127 * 0.25);
      break;

    case 111:
      // VCO LFO
      vcoModMixer_1.gain(1, 0.25 * value * DIV127);
      vcoModMixer_2.gain(1, 0.25 * value * DIV127);
      break;

    // ============================== VCF Controls ==============================
    case 112:
      // VCF Frequency
      vcf_1.frequency(MAX_FILTER_FREQ * (value * DIV127));
      vcf_2.frequency(MAX_FILTER_FREQ * (value * DIV127));
      break;

    case 113:
      // VCF Resonance
      vcf_1.resonance(Q_RATIO * (value * DIV127) + Q_FLOOR);
      vcf_2.resonance(Q_RATIO * (value * DIV127) + Q_FLOOR);
      break;

    case 114:
      // VCF Envelope
      vcfModMixer_1.gain(0, ((int)value - 64) / 64.0);
      vcfModMixer_2.gain(0, ((int)value - 64) / 64.0);
      break;

    case 115:
      // VCF LFO
      vcfModMixer_1.gain(1, value * DIV127);
      vcfModMixer_2.gain(1, value * DIV127);
      break;

    // ============================== VCA Controls ==============================
    case 116:
      // VCA Envelope
      floatVal = value * DIV127;
      vcaMixer_1.gain(0, 1.0 - floatVal);
      vcaMixer_2.gain(0, 1.0 - floatVal);
      vcaMixer_1.gain(1, floatVal);
      vcaMixer_2.gain(1, floatVal);
      break;

    case 117:
      // VCA LFO
      floatVal = 0.5 * value * DIV127;
      vcaLfoAmount_1.gain(0, floatVal);
      vcaLfoAmount_2.gain(0, floatVal);
      vcaLfoAmount_1.gain(1, 1.0 - floatVal);
      vcaLfoAmount_2.gain(1, 1.0 - floatVal);
      break;

    // ============================== Envelope Controls ==============================
    case 118:
      // Attack
      envelope_1.attack(3000 * (value * DIV127) + 1);
      envelope_2.attack(3000 * (value * DIV127) + 1);
      break;

    case 119:
      // Decay
      envelope_1.decay(3000 * (value * DIV127));
      envelope_2.decay(3000 * (value * DIV127));
      break;

    case 120:
      // Sustain
      envelope_1.sustain(value * DIV127);
      envelope_2.sustain(value * DIV127);
      break;

    case 121:
      // Release
      envelope_1.release(3000 * (value * DIV127));
      envelope_2.release(3000 * (value * DIV127));
      break;

    // ============================== LFO Controls ==============================
    case 122:
      // LFO Rate
      lfo.frequency((MAX_LFO_FREQ - MIN_LFO_FREQ) * (value * DIV127) + MIN_LFO_FREQ);
      break;

    case 123:
      // LFO Waveform
      switch (value) {
        case 0:
          lfo.begin(WAVEFORM_SINE);
          break;
        case 1:
          lfo.begin(WAVEFORM_TRIANGLE);
          break;
        case 2:
          lfo.begin(WAVEFORM_PULSE);
          break;
        case 3:
          lfo.begin(WAVEFORM_SAWTOOTH);
          break;
      }
      break;

  }
}
