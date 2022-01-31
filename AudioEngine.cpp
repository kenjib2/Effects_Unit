#include "AudioEngine.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=104,67
AudioSynthWaveformDc     envelopeDc;     //xy=124,657
AudioSynthWaveformDc     vcoPulseWidth;  //xy=134,411
AudioMixer4              vcoModMixer;    //xy=150,346
AudioRecordQueue         effect1In;         //xy=252,68
AudioEffectEnvelope      envelope;       //xy=282,658
AudioSynthNoisePink      pinkNoise;      //xy=304,459
AudioSynthWaveformModulated vco1;           //xy=305,352
AudioSynthWaveformModulated vco2;           //xy=307,406
AudioPlayQueue           effect1Out;         //xy=389,67
AudioMixer4              vcoMixer;       //xy=446,405
AudioMixer4              vcfModMixer;         //xy=504,483
AudioFilterLadder        vcf;            //xy=590,401
AudioMixer4              synthMixer;         //xy=599,62
AudioSynthWaveform       lfo;            //xy=604,660
AudioEffectMultiply      vca;            //xy=730,462
AudioEffectEnvelope      vcaPassThroughEnvelope; //xy=733,324
AudioRecordQueue         effect2In;         //xy=744,62
AudioSynthWaveformDc     vcaLfoDcOffset;            //xy=781,660
AudioMixer4              vcaMixer;       //xy=844,399
AudioPlayQueue           effect2Out;         //xy=870,61
AudioMixer4              vcaLfoAmount;         //xy=897,546
AudioEffectMultiply      vcaLfoMod;      //xy=991,397
AudioOutputI2S           audioOut;           //xy=1039,62
AudioConnection          patchCord1(i2s1, 0, effect1In, 0);
AudioConnection          patchCord2(envelopeDc, envelope);
AudioConnection          patchCord3(vcoPulseWidth, 0, vco1, 1);
AudioConnection          patchCord4(vcoPulseWidth, 0, vco2, 1);
AudioConnection          patchCord5(vcoModMixer, 0, vco1, 0);
AudioConnection          patchCord6(vcoModMixer, 0, vco2, 0);
AudioConnection          patchCord7(envelope, 0, vca, 1);
AudioConnection          patchCord8(envelope, 0, vcoModMixer, 0);
AudioConnection          patchCord9(envelope, 0, vcfModMixer, 0);
AudioConnection          patchCord10(pinkNoise, 0, vcoMixer, 2);
AudioConnection          patchCord11(vco1, 0, vcoMixer, 0);
AudioConnection          patchCord12(vco2, 0, vcoMixer, 1);
AudioConnection          patchCord13(effect1Out, 0, synthMixer, 0);
AudioConnection          patchCord14(vcoMixer, 0, vcf, 0);
AudioConnection          patchCord15(vcfModMixer, 0, vcf, 1);
AudioConnection          patchCord16(vcf, vcaPassThroughEnvelope);
AudioConnection          patchCord17(vcf, 0, vca, 0);
AudioConnection          patchCord18(synthMixer, effect2In);
AudioConnection          patchCord19(lfo, 0, vcaLfoAmount, 0);
AudioConnection          patchCord20(lfo, 0, vcoModMixer, 1);
AudioConnection          patchCord21(lfo, 0, vcfModMixer, 1);
AudioConnection          patchCord22(vca, 0, vcaMixer, 1);
AudioConnection          patchCord23(vcaPassThroughEnvelope, 0, vcaMixer, 0);
AudioConnection          patchCord24(vcaLfoDcOffset, 0, vcaLfoAmount, 1);
AudioConnection          patchCord25(vcaMixer, 0, vcaLfoMod, 0);
AudioConnection          patchCord26(effect2Out, 0, audioOut, 0);
AudioConnection          patchCord27(effect2Out, 0, audioOut, 1);
AudioConnection          patchCord28(vcaLfoAmount, 0, vcaLfoMod, 1);
AudioConnection          patchCord29(vcaLfoMod, 0, synthMixer, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1081,659
// GUItool: end automatically generated code


const byte BUFFER = 8; //Size of keyboard buffer
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
byte globalVelocity = 0;
int octave = 0;
float detuneFactor = 1;
float bendFactor = 1;
int bendRange = 12;


void initializeAudioEngine(usb_midi_class usbMIDIControl) {
  AudioMemory(1024);

  synthMixer.gain(0, 1.0);
  synthMixer.gain(1, 1.0);

  effect1In.begin();
  effect2In.begin();

  usbMIDIControl.setHandleControlChange(midiControlChange);
  usbMIDIControl.setHandleNoteOff(midiNoteOff);
  usbMIDIControl.setHandleNoteOn(midiNoteOn);
  usbMIDIControl.setHandlePitchChange(midiPitchBend);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.32);

  vco1.begin(WAVEFORM_SAWTOOTH);
  vco1.amplitude(0.75);
  vco1.frequency(82.41);

  vco2.begin(WAVEFORM_SAWTOOTH);
  vco2.amplitude(0.75);
  vco2.frequency(123);

  vcoPulseWidth.amplitude(0.5);

  pinkNoise.amplitude(1.0);

  vcoModMixer.gain(0, 0.0);
  vcoModMixer.gain(1, 0.0);

  vcoMixer.gain(0, 1.0);
  vcoMixer.gain(1, 1.0);
  vcoMixer.gain(2, 1.0);

  vcf.resonance(Q_FLOOR);
  vcf.frequency(MAX_FILTER_FREQ);
  vcf.octaveControl(FILTER_OCTAVE_CONTROL);

  vcfModMixer.gain(0, 0.0);
  vcfModMixer.gain(1, 0.0);

  vcaPassThroughEnvelope.attack(1);
  vcaPassThroughEnvelope.decay(0);
  vcaPassThroughEnvelope.sustain(1);
  vcaPassThroughEnvelope.release(1);

  vcaMixer.gain(0, 0.0);
  vcaMixer.gain(1, 1.0);

  vcaLfoDcOffset.amplitude(1.0);

  vcaLfoAmount.gain(0, 0.0);
  vcaLfoAmount.gain(1, 1.0);

  envelopeDc.amplitude(1.0);

  envelope.attack(1);
  envelope.decay(0);
  envelope.sustain(1);
  envelope.release(1);

  lfo.begin(WAVEFORM_TRIANGLE);
  lfo.amplitude(1.0);
  lfo.frequency(1.0);
  lfo.pulseWidth(0.5);
}

void processAudioEngine(usb_midi_class usbMIDIControl) {
  if (effect1In.available() >= 1) {
    int16_t *audioBuffer = effect1Out.getBuffer();
    memcpy(audioBuffer, effect1In.readBuffer(), 256);
    effect1In.freeBuffer();
//    effect2.processEffect(audioBuffer);
    effect1Out.playBuffer();
  }

  if (effect2In.available() >= 1) {
    int16_t *audioBuffer = effect2Out.getBuffer();
    memcpy(audioBuffer, effect2In.readBuffer(), 256);
    effect2In.freeBuffer();
//    effect2.processEffect(audioBuffer);
    effect2Out.playBuffer();
  }
}

void bufferNote(byte note, bool playNote) {
  static byte buff[BUFFER];
  static byte buffSize = 0;

  // Add Note
  if (playNote == true && (buffSize < BUFFER) ) {
    vcoTrigger(note, true);
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
          vcoTrigger(buff[buffSize - 1], false);
          return;
        }
        else {
          vcoStop();

          return;
        }
      }
    }
  }
}

void vcoTrigger(byte note, bool triggerEnvelope) {
  vco1.frequency(noteFreqs[note] * bendFactor);
  vco2.frequency(noteFreqs[note + octave] * detuneFactor * bendFactor);
  float velo = (globalVelocity * DIV127);
  vco1.amplitude(velo);
  vco2.amplitude(velo);
  pinkNoise.amplitude(velo);

  if (triggerEnvelope) {
    envelope.noteOn();
    vcaPassThroughEnvelope.noteOn();
  }
}

void vcoStop() {
  envelope.noteOff();
  vcaPassThroughEnvelope.noteOff();
}

void vcoUpdateFrequency() {
  vco1.frequency(noteFreqs[globalNote] * bendFactor);
  vco2.frequency(noteFreqs[globalNote + octave] * detuneFactor * bendFactor);
}

void midiNoteOn(byte channel, byte note, byte velocity) {
  if ( note > 23 && note < 108 ) {
    globalNote = note;
    globalVelocity = velocity;
    bufferNote(note, true);
  }
}

void midiNoteOff(byte channel, byte note, byte velocity) {
  if ( note > 23 && note < 108 ) {
    bufferNote(note, false);
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
      vcoMixer.gain(0, (value * DIV127));
      break;

    case 103:
      // VCO 2 Level
      vcoMixer.gain(1, (value * DIV127));
      break;

    case 104:
      // Pink Noise Level
      vcoMixer.gain(2, (value * DIV127));
      break;

    case 105:
      // VCO 1 Waveform
      switch (value) {
        case 0:
          vco1.begin(WAVEFORM_SINE);
          break;
        case 1:
          vco1.begin(WAVEFORM_TRIANGLE);
          break;
        case 2:
          vco1.begin(WAVEFORM_PULSE);
          break;
        case 3:
          vco1.begin(WAVEFORM_SAWTOOTH);
          break;
      }
      break;

    case 106:
      // VCO 2 Waveform
      switch (value) {
        case 0:
          vco2.begin(WAVEFORM_SINE);
          break;
        case 1:
          vco2.begin(WAVEFORM_TRIANGLE);
          break;
        case 2:
          vco2.begin(WAVEFORM_PULSE);
          break;
        case 3:
          vco2.begin(WAVEFORM_SAWTOOTH);
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
      vcoModMixer.gain(0, (value - 64) * DIV127 * 0.25);
      break;

    case 111:
      // VCO LFO
      vcoModMixer.gain(1, 0.25 * value * DIV127);
      break;

    // ============================== VCF Controls ==============================
    case 112:
      // VCF Frequency
      vcf.frequency(MAX_FILTER_FREQ * (value * DIV127));
      break;

    case 113:
      // VCF Resonance
      vcf.resonance(Q_RATIO * (value * DIV127) + Q_FLOOR);
      break;

    case 114:
      // VCF Envelope
      vcfModMixer.gain(0, ((int)value - 64) / 64.0);
      break;

    case 115:
      // VCF LFO
      vcfModMixer.gain(1, value * DIV127);
      break;

    // ============================== VCA Controls ==============================
    case 116:
      // VCA Envelope
      floatVal = value * DIV127;
      vcaMixer.gain(0, 1.0 - floatVal);
      vcaMixer.gain(1, floatVal);
      break;

    case 117:
      // VCA LFO
      floatVal = 0.5 * value * DIV127;
      vcaLfoAmount.gain(0, floatVal);
      vcaLfoAmount.gain(1, 1.0 - floatVal);
      break;

    // ============================== Envelope Controls ==============================
    case 118:
      // Attack
      envelope.attack(3000 * (value * DIV127) + 1);
      break;

    case 119:
      // Decay
      envelope.decay(3000 * (value * DIV127));
      break;

    case 120:
      // Sustain
      envelope.sustain(value * DIV127);
      break;

    case 121:
      // Release
      envelope.release(3000 * (value * DIV127));
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
