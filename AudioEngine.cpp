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

  usbMIDIControl.setHandleControlChange(myControlChange);
  usbMIDIControl.setHandleNoteOff(myNoteOff);
  usbMIDIControl.setHandleNoteOn(myNoteOn);
  usbMIDIControl.setHandlePitchChange(myPitchBend);

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

void myNoteOn(byte channel, byte note, byte velocity) {
  if ( note > 23 && note < 108 ) {
    globalNote = note;
    globalVelocity = velocity;
    bufferNote(note, true);
  }
}

void myNoteOff(byte channel, byte note, byte velocity) {
  if ( note > 23 && note < 108 ) {
    bufferNote(note, false);
  }
}

void myPitchBend(byte channel, int bend) {
  float bendF = bend;
  bendF = bendF / 8192;
  bendF = bendF * bendRange;
  bendF = bendF / 12;
  bendFactor = pow(2, bendF);
  vcoUpdateFrequency();
}

void myControlChange(byte channel, byte control, byte value) {
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


/*
#include <functional>
#include "Patch.h"
#include "AudioEngine.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc     vcfDc;          //xy=85,734
AudioSynthWaveformDc     vcoDc;          //xy=94,245
AudioInputI2S            audioIn;           //xy=95,65
AudioSynthWaveform       vcoLfo;         //xy=97,528
AudioEffectEnvelope      vcoEnvelope;    //xy=131,331
AudioMixer4              vcoModMixer;    //xy=135,439
AudioSynthWaveform       vcfLfo;         //xy=220,784
AudioEffectEnvelope      vcfEnvelope;    //xy=232,706
AudioRecordQueue         effect1InLeft;         //xy=258,64
AudioSynthNoisePink      pinkNoise1;     //xy=264,564
AudioSynthWaveformModulated osc2;           //xy=267,483
AudioSynthWaveformModulated osc1;           //xy=273,402
AudioMixer4              vcfModMixer;    //xy=393,748
AudioMixer4              vcoMixer;       //xy=395,485
AudioPlayQueue           effect1OutLeft;         //xy=408,64
AudioFilterLadder        ladderVcf;      //xy=547,497
AudioSynthWaveformDc     vcaDc;            //xy=559,661
AudioMixer4              leftAudioMix;         //xy=612,63
AudioEffectEnvelope      vcaEnvelope;    //xy=625,611
AudioEffectMultiply      vcaEnvelopeMod;      //xy=658,558
AudioEffectEnvelope      vcaEnvelopeThrough;      //xy=678,431
AudioRecordQueue         effect2InLeft;         //xy=787,60
AudioMixer4              vcaEnvelopeMixer;         //xy=800,502
AudioSynthWaveformDc     vcaOffset;            //xy=816,731
AudioSynthWaveform       vcaLfo;      //xy=820,681
AudioPlayQueue           effect2OutLeft;         //xy=937,60
AudioMixer4              vcaLfoOffsetMixer; //xy=1000,727
AudioEffectMultiply      vcaLfoMod; //xy=1003,508
AudioOutputI2S           audioOut;           //xy=1093,61
AudioConnection          patchCord1(vcfDc, vcfEnvelope);
AudioConnection          patchCord2(vcoDc, vcoEnvelope);
AudioConnection          patchCord3(audioIn, 0, effect1InLeft, 0);
AudioConnection          patchCord4(vcoLfo, 0, vcoModMixer, 1);
AudioConnection          patchCord5(vcoEnvelope, 0, vcoModMixer, 0);
AudioConnection          patchCord6(vcoModMixer, 0, osc1, 0);
AudioConnection          patchCord7(vcfLfo, 0, vcfModMixer, 1);
AudioConnection          patchCord8(vcfEnvelope, 0, vcfModMixer, 0);
AudioConnection          patchCord9(pinkNoise1, 0, vcoMixer, 2);
AudioConnection          patchCord10(osc2, 0, audioOut, 0);
AudioConnection          patchCord11(osc2, 0, audioOut, 1);
AudioConnection          patchCord12(osc1, 0, vcoMixer, 0);
AudioConnection          patchCord13(vcfModMixer, 0, ladderVcf, 1);
AudioConnection          patchCord14(vcoMixer, 0, ladderVcf, 0);
AudioConnection          patchCord15(effect1OutLeft, 0, leftAudioMix, 0);
AudioConnection          patchCord16(ladderVcf, 0, vcaEnvelopeMod, 0);
AudioConnection          patchCord17(ladderVcf, vcaEnvelopeThrough);
AudioConnection          patchCord18(vcaDc, vcaEnvelope);
AudioConnection          patchCord19(leftAudioMix, effect2InLeft);
AudioConnection          patchCord20(vcaEnvelope, 0, vcaEnvelopeMod, 1);
AudioConnection          patchCord21(vcaEnvelopeMod, 0, vcaEnvelopeMixer, 1);
AudioConnection          patchCord22(vcaEnvelopeThrough, 0, vcaEnvelopeMixer, 0);
AudioConnection          patchCord23(vcaEnvelopeMixer, 0, vcaLfoMod, 0);
AudioConnection          patchCord24(vcaOffset, 0, vcaLfoOffsetMixer, 1);
AudioConnection          patchCord25(vcaLfo, 0, vcaLfoOffsetMixer, 0);
AudioConnection          patchCord26(vcaLfoOffsetMixer, 0, vcaLfoMod, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1098,185
// GUItool: end automatically generated code

// GUItool: begin automatically generated code
//AudioSynthNoisePink      pink1;          //xy=82,380
//AudioRecordQueue         queueIn;         //xy=269,368
//AudioPlayQueue           queueOut;         //xy=410,371
//AudioOutputI2S           i2s1;           //xy=683,454
//AudioConnection          patchCord1(pink1, queueIn);
//AudioConnection          patchCord2(queueOut, 0, i2s1, 0);
//AudioConnection          patchCord3(queueOut, 0, i2s1, 1);
//AudioControlSGTL5000     sgtl5000_1;     //xy=701,345
// GUItool: end automatically generated code

/*
// GUItool: begin automatically generated code
AudioSynthWaveformDc     vcfDc;          //xy=85,734
AudioSynthWaveformDc     vcoDc;          //xy=94,245
AudioInputI2S            audioIn;           //xy=95,65
AudioSynthWaveform       vcoLfo;         //xy=97,528
AudioEffectEnvelope      vcoEnvelope;    //xy=131,331
AudioMixer4              vcoModMixer;    //xy=135,439
AudioSynthWaveform       vcfLfo;         //xy=220,784
AudioEffectEnvelope      vcfEnvelope;    //xy=232,706
AudioRecordQueue         effect1InLeft;         //xy=258,64
AudioSynthNoisePink      pinkNoise1;     //xy=264,564
AudioSynthWaveformModulated osc2;           //xy=267,483
AudioSynthWaveformModulated osc1;           //xy=273,402
AudioSynthNoiseWhite     noise1;         //xy=364,128
AudioSynthNoisePink      pink1;          //xy=367,194
AudioMixer4              vcfModMixer;    //xy=393,748
AudioMixer4              vcoMixer;       //xy=395,485
AudioPlayQueue           effect1OutLeft;         //xy=408,64
AudioSynthWaveformSine   sine1;          //xy=462,266
AudioFilterLadder        ladderVcf;      //xy=547,497
AudioSynthWaveformDc     vcaDc;            //xy=559,661
AudioMixer4              leftAudioMix;         //xy=612,63
AudioEffectEnvelope      vcaEnvelope;    //xy=625,611
AudioEffectMultiply      vcaEnvelopeMod;      //xy=658,558
AudioEffectEnvelope      vcaEnvelopeThrough;      //xy=678,431
AudioRecordQueue         effect2InLeft;         //xy=787,60
AudioMixer4              vcaEnvelopeMixer;         //xy=800,502
AudioSynthWaveformDc     vcaOffset;            //xy=816,731
AudioSynthWaveform       vcaLfo;      //xy=820,681
AudioPlayQueue           effect2OutLeft;         //xy=937,60
AudioMixer4              vcaLfoOffsetMixer; //xy=1000,727
AudioEffectMultiply      vcaLfoMod; //xy=1003,508
AudioOutputI2S           audioOut;           //xy=1096,112
AudioConnection          patchCord1(vcfDc, vcfEnvelope);
AudioConnection          patchCord2(vcoDc, vcoEnvelope);
AudioConnection          patchCord3(audioIn, 0, effect1InLeft, 0);
AudioConnection          patchCord4(vcoLfo, 0, vcoModMixer, 1);
AudioConnection          patchCord5(vcoEnvelope, 0, vcoModMixer, 0);
AudioConnection          patchCord6(vcoModMixer, 0, osc1, 0);
AudioConnection          patchCord7(vcoModMixer, 0, osc2, 0);
AudioConnection          patchCord8(vcfLfo, 0, vcfModMixer, 1);
AudioConnection          patchCord9(vcfEnvelope, 0, vcfModMixer, 0);
AudioConnection          patchCord10(pinkNoise1, 0, vcoMixer, 2);
AudioConnection          patchCord11(osc2, 0, vcoMixer, 1);
AudioConnection          patchCord12(osc1, 0, vcoMixer, 0);
AudioConnection          patchCord15(vcfModMixer, 0, ladderVcf, 1);
AudioConnection          patchCord16(vcoMixer, 0, ladderVcf, 0);
AudioConnection          patchCord17(effect1OutLeft, 0, leftAudioMix, 0);
AudioConnection          patchCord18(ladderVcf, 0, vcaEnvelopeMod, 0);
AudioConnection          patchCord19(ladderVcf, vcaEnvelopeThrough);
AudioConnection          patchCord20(vcaDc, vcaEnvelope);
AudioConnection          patchCord21(leftAudioMix, effect2InLeft);
AudioConnection          patchCord22(vcaEnvelope, 0, vcaEnvelopeMod, 1);
AudioConnection          patchCord23(vcaEnvelopeMod, 0, vcaEnvelopeMixer, 1);
AudioConnection          patchCord24(vcaEnvelopeThrough, 0, vcaEnvelopeMixer, 0);
AudioConnection          patchCord25(vcaEnvelopeMixer, 0, vcaLfoMod, 0);
AudioConnection          patchCord26(vcaOffset, 0, vcaLfoOffsetMixer, 1);
AudioConnection          patchCord27(vcaLfo, 0, vcaLfoOffsetMixer, 0);
AudioConnection          patchCord28(vcaLfoOffsetMixer, 0, vcaLfoMod, 1);
AudioConnection          patchCord29(vcaLfoMod, 0, leftAudioMix, 1);
AudioConnection          patchCord13(effect2OutLeft, 0, audioOut, 0);
AudioConnection          patchCord14(effect2OutLeft, 0, audioOut, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1098,185
// GUItool: end automatically generated code
*/
/*
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
const int AUDIO_BUFFER_SIZE = 128;

byte globalNote = 0;
byte globalVelocity = 0;
const float DIV127 = (1.0 / 127.0);
int octave = 0;
float detuneRatio = 1.0;
float bendRatio = 1.0;
int bendRange = 2;


void initAudioEngine() {
  AudioMemory(40);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.25);

  leftAudioMix.gain(0, 1.0);
  leftAudioMix.gain(1, 1.0);

  effect1InLeft.begin();
  effect2InLeft.begin();
}


void processAudio() {
//void processAudio(Effect effect1, Effect effect2) {
  if (effect1InLeft.available() >= 1) {
    int16_t *audioBuffer = effect1OutLeft.getBuffer();
    memcpy(audioBuffer, effect1InLeft.readBuffer(), 256);
    effect1InLeft.freeBuffer();
//    effect1.processEffect(audioBuffer);
    effect1OutLeft.playBuffer();
  }
  if (effect2InLeft.available() >= 1) {
    int16_t *audioBuffer = effect2OutLeft.getBuffer();
    memcpy(audioBuffer, effect2InLeft.readBuffer(), 256);
    effect2InLeft.freeBuffer();
//    effect2.processEffect(audioBuffer);
    effect2OutLeft.playBuffer();
  }
}


void initSynthEngine(usb_midi_class usbMIDIControl) {
//  AudioMemory(80);

//  sgtl5000_1.enable();
//  sgtl5000_1.volume(0.45);

//  pinkNoise1.amplitude(1.0);
  AudioMemory(40);

  usbMIDIControl.setHandleControlChange(midiControlChange);
  usbMIDIControl.setHandleNoteOff(midiNoteOff);
  usbMIDIControl.setHandleNoteOn(midiNoteOn);
  usbMIDIControl.setHandlePitchChange(midiPitchChange);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.65);

  osc1.begin(WAVEFORM_SAWTOOTH);
  osc1.amplitude(1.0);
  osc1.frequency(82.41);

  osc2.begin(WAVEFORM_SAWTOOTH);
  osc2.amplitude(1.0);
  osc2.frequency(82.41);

  pinkNoise1.amplitude(1.0);

  vcoMixer.gain(0, 1.0);
  vcoMixer.gain(1, 1.0);
  vcoMixer.gain(2, 0.0);

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

  vcaDc.amplitude(1.0);

  vcaEnvelope.attack(0);
  vcaEnvelope.decay(0);
  vcaEnvelope.sustain(1);
  vcaEnvelope.release(0.0);
  
  vcaEnvelopeThrough.attack(0);
  vcaEnvelopeThrough.decay(0);
  vcaEnvelopeThrough.sustain(1);
  vcaEnvelopeThrough.release(0.0);
  
  vcaEnvelopeMixer.gain(0, 1.0);
  vcaEnvelopeMixer.gain(1, 0.0);

  vcaLfo.begin(WAVEFORM_TRIANGLE);
  vcaLfo.amplitude(1.0);
  vcaLfo.frequency(1.0);
  vcaLfo.pulseWidth(0.5);

  vcaOffset.amplitude(1.0);

  vcaLfoOffsetMixer.gain(0, 0.0);
  vcaLfoOffsetMixer.gain(0, 0.0);
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
          osc2.begin(WAVEFORM_SAWTOOTH);
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
      // VCA LFO
      floatVal = value * DIV127 / 2.0;
      vcaLfoOffsetMixer.gain(0, floatVal);
      vcaLfoOffsetMixer.gain(1, 1.0 - floatVal);
      break;
    case 122:
      // LFO Frequency
      floatVal = (MAX_LFO_FREQ - MIN_LFO_FREQ) * (value * DIV127) + MIN_LFO_FREQ;
      vcoLfo.frequency(floatVal);
      vcfLfo.frequency(floatVal);
      vcaLfo.frequency(floatVal);
      break;
    case 123:
      // LFO Waveform
      switch (value) {
        case 0:
          vcoLfo.begin(WAVEFORM_SINE);
          vcfLfo.begin(WAVEFORM_SINE);
          vcaLfo.begin(WAVEFORM_SINE);
          break;
        case 1:
          vcoLfo.begin(WAVEFORM_TRIANGLE);
          vcfLfo.begin(WAVEFORM_TRIANGLE);
          vcaLfo.begin(WAVEFORM_TRIANGLE);
          break;
        case 2:
          vcoLfo.begin(WAVEFORM_PULSE);
          vcfLfo.begin(WAVEFORM_PULSE);
          vcaLfo.begin(WAVEFORM_PULSE);
          break;
        case 3:
          vcoLfo.begin(WAVEFORM_SAWTOOTH);
          vcfLfo.begin(WAVEFORM_SAWTOOTH);
          vcaLfo.begin(WAVEFORM_SAWTOOTH);
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
  osc2.frequency(noteFreqs[note]);
//  osc2.frequency(noteFreqs[note + octave] * detuneRatio * bendRatio);
  float velo = (globalVelocity * DIV127);
  osc1.amplitude(velo);
  osc2.amplitude(velo);
  pinkNoise1.amplitude(velo);

  if (triggerEnvelope) {
    vcaEnvelope.noteOn();
    vcaEnvelopeThrough.noteOn();
    vcfEnvelope.noteOn();
    vcoEnvelope.noteOn();
  }
}


void oscStop() {
  vcaEnvelope.noteOff();
  vcaEnvelopeThrough.noteOff();
  vcfEnvelope.noteOff();
  vcoEnvelope.noteOff();
}


void updateOscFrequency() {
  osc1.frequency(noteFreqs[globalNote] * bendRatio);
  osc2.frequency(noteFreqs[globalNote]);
}

*/
