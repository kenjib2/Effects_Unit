#include <functional>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "SubtractiveSynthEngine.h"


// GUItool: begin automatically generated code
AudioSynthWaveformDc     vcfDc;          //xy=57,564
AudioSynthWaveformDc     vcoDc;          //xy=66,75
AudioSynthWaveform       vcoLfo;         //xy=69,358
AudioEffectEnvelope      vcoEnvelope;    //xy=103,161
AudioMixer4              vcoModMixer;    //xy=107,269
AudioSynthWaveform       vcfLfo;         //xy=192,614
AudioEffectEnvelope      vcfEnvelope;    //xy=204,536
AudioSynthNoisePink      pinkNoise1;     //xy=236,394
AudioSynthWaveformModulated osc2;           //xy=239,313
AudioSynthWaveformModulated osc1;           //xy=245,232
AudioMixer4              vcfModMixer;    //xy=365,578
AudioMixer4              vcoMixer;       //xy=367,315
AudioFilterLadder        ladderVcf;      //xy=519,327
AudioEffectEnvelope      vcaPassThrough; //xy=639,225
AudioEffectEnvelope      vcaEnvelope;    //xy=648,419
AudioMixer4              vcaEnvelopeMixer; //xy=824,333
AudioOutputI2S           i2s1;           //xy=994,331
AudioConnection          patchCord1(vcfDc, vcfEnvelope);
AudioConnection          patchCord2(vcoDc, vcoEnvelope);
AudioConnection          patchCord3(vcoLfo, 0, vcoModMixer, 1);
AudioConnection          patchCord4(vcoEnvelope, 0, vcoModMixer, 0);
AudioConnection          patchCord5(vcoModMixer, 0, osc1, 0);
AudioConnection          patchCord6(vcoModMixer, 0, osc2, 0);
AudioConnection          patchCord7(vcfLfo, 0, vcfModMixer, 1);
AudioConnection          patchCord8(vcfEnvelope, 0, vcfModMixer, 0);
AudioConnection          patchCord9(pinkNoise1, 0, vcoMixer, 2);
AudioConnection          patchCord10(osc2, 0, vcoMixer, 1);
AudioConnection          patchCord11(osc1, 0, vcoMixer, 0);
AudioConnection          patchCord12(vcfModMixer, 0, ladderVcf, 1);
AudioConnection          patchCord13(vcoMixer, 0, ladderVcf, 0);
AudioConnection          patchCord14(ladderVcf, vcaEnvelope);
AudioConnection          patchCord15(ladderVcf, vcaPassThrough);
AudioConnection          patchCord16(vcaPassThrough, 0, vcaEnvelopeMixer, 0);
AudioConnection          patchCord17(vcaEnvelope, 0, vcaEnvelopeMixer, 1);
AudioConnection          patchCord18(vcaEnvelopeMixer, 0, i2s1, 0);
AudioConnection          patchCord19(vcaEnvelopeMixer, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=975,388
// GUItool: end automatically generated code


const byte NOTE_BUFFER_SIZE = 10;
const float noteFreqs[128] = {
    8.176, 8.662, 9.177, 9.723, 10.301, 10.913, 11.562, 12.25, 12.978, 13.75, 14.568, 15.434, 16.352, 17.324,18.354, 19.445,
    20.602, 21.827, 23.125, 24.5, 25.957, 27.5, 29.135, 30.868, 32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249,
    48.999, 51.913, 55, 58.27, 61.735, 65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110, 116.541,
    123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220, 233.082, 246.942, 261.626,
    277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33,
    622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659, 1244.508,
    1318.51, 1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533, 2093.005, 2217.461, 2349.318, 2489.016,
    2637.02, 2793.826, 2959.955, 3135.963, 3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922, 4698.636, 4978.032,
    5274.041, 5587.652, 5919.911, 6271.927, 6644.875, 7040, 7458.62, 7902.133, 8372.018, 8869.844, 9397.273, 9956.063,
    10548.08, 11175.3, 11839.82, 12543.85};
const int MAX_ENVELOPE_MS = 3000;
const int MAX_FILTER_FREQ = 10000;
const int FILTER_OCTAVE_CONTROL = 4.0;
const float Q_RATIO = 1.2;
const float Q_FLOOR = 0.0;
const float MIN_LFO_FREQ = 0.1;
const float MAX_LFO_FREQ = 12.0;

byte globalNote = 0;
byte globalVelocity = 0;
const float DIV127 = (1.0 / 127.0);
int octave = 0;
float detuneRatio = 1.0;
float bendRatio = 1.0;
int bendRange = 2;


void initSynthEngine(usb_midi_class usbMIDIControl) {
  AudioMemory(20);

  usbMIDIControl.setHandleControlChange(midiControlChange);
  usbMIDIControl.setHandleNoteOff(midiNoteOff);
  usbMIDIControl.setHandleNoteOn(midiNoteOn);
  usbMIDIControl.setHandlePitchChange(midiPitchChange);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.50);

  osc1.begin(WAVEFORM_SAWTOOTH);
  osc1.amplitude(1.0);
  osc1.frequency(82.41);

  osc2.begin(WAVEFORM_SAWTOOTH);
  osc2.amplitude(1.0);
  osc2.frequency(82.41);

  pinkNoise1.amplitude(0.0);

  vcoMixer.gain(0, 1.0);
  vcoMixer.gain(1, 1.0);
  vcoMixer.gain(2, 0.0);

  vcaEnvelope.attack(0);
  vcaEnvelope.decay(0);
  vcaEnvelope.sustain(1);
  vcaEnvelope.release(0.0);
  
  vcaPassThrough.attack(0);
  vcaPassThrough.decay(0);
  vcaPassThrough.sustain(1);
  vcaPassThrough.release(0.0);
  
  vcaEnvelopeMixer.gain(0, 0.0);
  vcaEnvelopeMixer.gain(1, 1.0);

  vcfDc.amplitude(0.0);

  vcfEnvelope.attack(0);
  vcfEnvelope.decay(0);
  vcfEnvelope.sustain(1);
  vcfEnvelope.release(0.0);

  vcfLfo.begin(WAVEFORM_TRIANGLE);
  vcfLfo.amplitude(1.0);
  vcfLfo.frequency(1.0);

  vcfModMixer.gain(0, 1.0);
  vcfModMixer.gain(1, 0.0);

  vcoDc.amplitude(0.0);

  vcoEnvelope.attack(0);
  vcoEnvelope.decay(0);
  vcoEnvelope.sustain(1);
  vcoEnvelope.release(0.0);

  vcoLfo.begin(WAVEFORM_TRIANGLE);
  vcoLfo.amplitude(1.0);
  vcoLfo.frequency(1.0);

  vcoModMixer.gain(0, 1.0);
  vcoModMixer.gain(1, 0.0);

  ladderVcf.resonance(Q_FLOOR);
  ladderVcf.frequency(MAX_FILTER_FREQ);
  ladderVcf.octaveControl(FILTER_OCTAVE_CONTROL);
}


void midiControlChange(byte channel, byte control, byte value) {
  float floatVal;
  switch (control) {
    case 102:
      // Osc 1 Volume
      vcoMixer.gain(0, value * DIV127);
      break;
    case 103:
      // Osc 2 Volume
      vcoMixer.gain(1, value * DIV127);
      break;
    case 104:
      // Pink Noise Volume
      vcoMixer.gain(2, value * DIV127);
      break;
    case 105:
      // Osc 2 Octave
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
      break;
    case 106:
      // Attack
      floatVal = MAX_ENVELOPE_MS * (value * DIV127);
      vcaEnvelope.attack(floatVal);
      vcfEnvelope.attack(floatVal);
      vcoEnvelope.attack(floatVal);
      break;
    case 107:
      // Decay
      floatVal = MAX_ENVELOPE_MS * (value * DIV127);
      vcaEnvelope.decay(floatVal);
      vcfEnvelope.decay(floatVal);
      vcoEnvelope.decay(floatVal);
      break;
    case 108:
      // Sustain
      floatVal = value * DIV127;
      vcaEnvelope.sustain(floatVal);
      vcfEnvelope.sustain(floatVal);
      vcoEnvelope.sustain(floatVal);
      break;
    case 109:
      // Release
      floatVal = MAX_ENVELOPE_MS * (value * DIV127);
      vcaEnvelope.release(floatVal);
      vcfEnvelope.release(floatVal);
      vcoEnvelope.release(floatVal);
      break;
    case 110:
      // Osc 1 Waveform
      switch (value) {
        case 0:
          osc1.begin(WAVEFORM_SINE);
          break;
        case 1:
          osc1.begin(WAVEFORM_TRIANGLE);
          break;
        case 2:
          osc1.begin(WAVEFORM_PULSE);
          break;
        case 3:
          osc1.begin(WAVEFORM_SAWTOOTH);
          break;
      }
      break;
    case 111:
      // Osc 2 Waveform
      switch (value) {
        case 0:
          osc2.begin(WAVEFORM_SINE);
          break;
        case 1:
          osc2.begin(WAVEFORM_TRIANGLE);
          break;
        case 2:
          osc2.begin(WAVEFORM_PULSE);
          break;
        case 3:
          osc2   .begin(WAVEFORM_SAWTOOTH);
          break;
      }
      break;
    case 112:
      // Osc 2 Detune
      detuneRatio = 1 - (0.04 * (value * DIV127));
      updateOscFrequency();
      break;
    case 113:
      // VCF Frequency
      ladderVcf.frequency(MAX_FILTER_FREQ * (value * DIV127));
      break;
    case 114:
      // VCF Resonance
      ladderVcf.resonance(Q_RATIO * (value * DIV127) + Q_FLOOR);
      break;
    case 115:
      // Pitch Change Range
      bendRange = value;
      break;
    case 116:
      // VCO Envelope
      vcoDc.amplitude(((int)value - 64) / 640.0);
      break;
    case 117:
      // VCF Envelope
      vcfDc.amplitude(((int)value - 64) / 64.0);
      break;
    case 118:
      // VCA Envelope
      floatVal = value * DIV127;
      vcaEnvelopeMixer.gain(0, 1.0 - floatVal);
      vcaEnvelopeMixer.gain(1, floatVal);
      break;
    case 119:
      // VCO LFO
      vcoModMixer.gain(1, 0.5 * value * DIV127);
      break;
    case 120:
      // VCF LFO
      vcfModMixer.gain(1, value * DIV127);
      break;
    case 121:
      // TO DO VCA LFO
      break;
    case 122:
      // LFO Frequency
      floatVal = (MAX_LFO_FREQ - MIN_LFO_FREQ) * (value * DIV127) + MIN_LFO_FREQ;
      vcoLfo.frequency(floatVal);
      vcfLfo.frequency(floatVal);
      break;
    case 123:
      // LFO Waveform
      switch (value) {
        case 0:
          vcoLfo.begin(WAVEFORM_SINE);
          vcfLfo.begin(WAVEFORM_SINE);
          break;
        case 1:
          vcoLfo.begin(WAVEFORM_TRIANGLE);
          vcfLfo.begin(WAVEFORM_TRIANGLE);
          break;
        case 2:
          vcoLfo.begin(WAVEFORM_PULSE);
          vcfLfo.begin(WAVEFORM_PULSE);
          break;
        case 3:
          vcoLfo.begin(WAVEFORM_SAWTOOTH);
          vcfLfo.begin(WAVEFORM_SAWTOOTH);
          break;
      }
      break;
  }
}


void midiNoteOn(byte channel, byte note, byte velocity) {
  if (note > 23 && note < 108) {
    globalNote = note;
    globalVelocity = velocity;
    keyBuff(note, true);
  }
}


void midiNoteOff(byte channel, byte note, byte velocity) {
  if (note > 23 && note < 108) {
    keyBuff(note, false);
  }
}


void midiPitchChange(byte channel, int bend) {
  float bendAmt = bend;
  bendAmt /= 8192;
  bendAmt *= bendRange;
  bendAmt /= 12;
  bendRatio = pow(2, bendAmt);
  updateOscFrequency();
}


void keyBuff(byte note, bool playNote) {
  static byte buff[NOTE_BUFFER_SIZE];
  static byte buffSize = 0;

  // Add Note
  if (playNote == true && (buffSize < NOTE_BUFFER_SIZE) ) {
    oscPlay(note, true);
    buff[buffSize] = note;
    buffSize++;
    return;
  }

  // Remove Note
  else if (playNote == false && buffSize != 0) {
    for (byte found = 0; found < buffSize; found++) {
      if (buff[found] == note) {
        for (byte gap = found; gap < (buffSize - 1); gap++) {
          buff[gap] = buff[gap + 1];
        }
        buffSize--;
        buff[buffSize] = 255;
        if (buffSize != 0) {
          oscPlay(buff[buffSize - 1], false);
          return;
        }
        else {
          oscStop();
          return;
        }
      }
    }
  }
}


void oscPlay(byte note, bool triggerEnvelope) {
  osc1.frequency(noteFreqs[note] * bendRatio);
  osc2.frequency(noteFreqs[note + octave] * detuneRatio * bendRatio);
  float velo = (globalVelocity * DIV127);
  osc1.amplitude(velo);
  osc2.amplitude(velo);
  pinkNoise1.amplitude(velo);

  if (triggerEnvelope) {
    vcaEnvelope.noteOn();
    vcaPassThrough.noteOn();
    vcfEnvelope.noteOn();
    vcoEnvelope.noteOn();
  }
}


void oscStop() {
  vcaEnvelope.noteOff();
  vcaPassThrough.noteOff();
  vcfEnvelope.noteOff();
  vcoEnvelope.noteOff();
}


void updateOscFrequency() {
  osc1.frequency(noteFreqs[globalNote] * bendRatio);
  osc2.frequency(noteFreqs[globalNote + octave] * detuneRatio * bendRatio);
}
