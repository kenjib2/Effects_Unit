#include "AudioEngine.h"

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       lfo;            //xy=55,1217.75
AudioInputI2S            i2s1;           //xy=117,65
AudioSynthWaveformDc     vcoPulseWidth_6; //xy=208,2010
AudioSynthWaveformDc     vcoPulseWidth_1;  //xy=215,355
AudioSynthWaveformDc     vcoPulseWidth_5; //xy=210,1682
AudioSynthWaveformDc     vcoPulseWidth_4; //xy=212,1358
AudioSynthWaveformDc     vcoPulseWidth_3; //xy=215,1032
AudioSynthWaveformDc     vcoPulseWidth_2; //xy=220,708
AudioMixer4              vcoModMixer_6; //xy=224,1945
AudioMixer4              vcoModMixer_1;    //xy=231,290
AudioMixer4              vcoModMixer_5; //xy=226,1617
AudioMixer4              vcoModMixer_4; //xy=228,1293
AudioMixer4              vcoModMixer_3; //xy=231,967
AudioMixer4              vcoModMixer_2; //xy=236,643
AudioRecordQueue         effect1In;      //xy=265,66
AudioSynthWaveformDc     envelopeDc_1;     //xy=265,475
AudioSynthWaveformDc     envelopeDc_6; //xy=260,2130
AudioSynthWaveformDc     envelopeDc_5; //xy=262,1802
AudioSynthWaveformDc     envelopeDc_4; //xy=264,1478
AudioSynthWaveformDc     envelopeDc_3; //xy=267,1152
AudioSynthWaveformDc     envelopeDc_2; //xy=269,828
AudioSynthNoisePink      pinkNoise_6; //xy=378,2058
AudioSynthNoisePink      pinkNoise_1;      //xy=385,403
AudioSynthWaveformModulated vco1_6; //xy=379,1952
AudioSynthNoisePink      pinkNoise_5; //xy=380,1730
AudioSynthWaveformModulated vco1_1;           //xy=386,296
AudioSynthWaveformModulated vco1_5; //xy=381,1624
AudioSynthNoisePink      pinkNoise_4; //xy=382,1406
AudioSynthWaveformModulated vco1_4; //xy=383,1300
AudioSynthWaveformModulated vco2_6; //xy=381,2005
AudioSynthNoisePink      pinkNoise_3; //xy=385,1080
AudioSynthWaveformModulated vco2_1;           //xy=388,350
AudioSynthWaveformModulated vco2_5; //xy=383,1677
AudioSynthWaveformModulated vco1_3; //xy=386,974
AudioSynthWaveformModulated vco2_4; //xy=385,1353
AudioSynthWaveformModulated vco2_3; //xy=388,1027
AudioSynthNoisePink      pinkNoise_2; //xy=390,756
AudioSynthWaveformModulated vco1_2; //xy=391,650
AudioSynthWaveformModulated vco2_2; //xy=393,703
AudioPlayQueue           effect1Out;     //xy=402,65
AudioEffectEnvelope      envelope_6; //xy=421,2130
AudioEffectEnvelope      envelope_1;       //xy=428,475
AudioEffectEnvelope      envelope_5; //xy=423,1802
AudioEffectEnvelope      envelope_4; //xy=425,1478
AudioEffectEnvelope      envelope_3; //xy=428,1152
AudioEffectEnvelope      envelope_2; //xy=433,828
AudioMixer4              vcoMixer_6; //xy=534,2004
AudioMixer4              vcoMixer_1;       //xy=541,349
AudioMixer4              vcoMixer_5; //xy=536,1676
AudioMixer4              vcoMixer_4; //xy=538,1352
AudioMixer4              vcoMixer_3; //xy=541,1026
AudioMixer4              vcoMixer_2; //xy=546,702
AudioMixer4              vcfModMixer_6; //xy=584,2072
AudioMixer4              vcfModMixer_1;    //xy=591,417
AudioMixer4              vcfModMixer_5; //xy=586,1744
AudioMixer4              vcfModMixer_4; //xy=588,1420
AudioMixer4              vcfModMixer_3; //xy=591,1094
AudioMixer4              vcfModMixer_2; //xy=596,770
AudioMixer4              synthMixer;     //xy=612,60
AudioFilterLadder        vcf_6; //xy=678,2000
AudioFilterLadder        vcf_1;            //xy=685,345
AudioFilterLadder        vcf_5; //xy=680,1672
AudioFilterLadder        vcf_4; //xy=682,1348
AudioFilterLadder        vcf_3; //xy=685,1022
AudioFilterLadder        vcf_2; //xy=690,698
AudioRecordQueue         effect2In;      //xy=757,60
AudioEffectEnvelope      vcaPassThroughEnvelope_6; //xy=769,1935
AudioEffectEnvelope      vcaPassThroughEnvelope_1; //xy=776,280
AudioEffectEnvelope      vcaPassThroughEnvelope_5; //xy=771,1607
AudioEffectEnvelope      vcaPassThroughEnvelope_4; //xy=773,1283
AudioSynthWaveformDc     vcaLfoDcOffset_6; //xy=771,2105
AudioSynthWaveformDc     vcaLfoDcOffset_1; //xy=778,450
AudioEffectEnvelope      vcaPassThroughEnvelope_3; //xy=776,957
AudioSynthWaveformDc     vcaLfoDcOffset_5; //xy=773,1777
AudioSynthWaveformDc     vcaLfoDcOffset_4; //xy=775,1453
AudioSynthWaveformDc     vcaLfoDcOffset_3; //xy=778,1127
AudioEffectEnvelope      vcaPassThroughEnvelope_2; //xy=781,633
AudioSynthWaveformDc     vcaLfoDcOffset_2; //xy=783,803
AudioEffectMultiply      vca_6; //xy=804,2061
AudioEffectMultiply      vca_1;            //xy=811,406
AudioEffectMultiply      vca_5; //xy=806,1733
AudioEffectMultiply      vca_4; //xy=808,1409
AudioEffectMultiply      vca_3; //xy=811,1083
AudioEffectMultiply      vca_2; //xy=816,759
AudioPlayQueue           effect2Out;     //xy=883,59
AudioMixer4              vcaMixer_6; //xy=918,1998
AudioMixer4              vcaMixer_1;       //xy=925,343
AudioMixer4              vcaMixer_5; //xy=920,1670
AudioMixer4              vcaMixer_4; //xy=922,1346
AudioMixer4              vcaMixer_3; //xy=925,1020
AudioMixer4              vcaMixer_2; //xy=930,696
AudioMixer4              vcaLfoAmount_6; //xy=969,2111
AudioMixer4              vcaLfoAmount_1;   //xy=976,456
AudioMixer4              vcaLfoAmount_5; //xy=971,1783
AudioMixer4              vcaLfoAmount_4; //xy=973,1459
AudioMixer4              vcaLfoAmount_3; //xy=976,1133
AudioMixer4              vcaLfoAmount_2; //xy=981,809
AudioOutputI2S           audioOut;       //xy=1052,60
AudioMixer4              synthPolyphony_1;         //xy=1066.5001220703125,143.50001525878906
AudioMixer4              synthPolyphony_2;         //xy=1067.75,213.5
AudioEffectMultiply      vcaLfoMod_6; //xy=1078,2004
AudioEffectMultiply      vcaLfoMod_1;      //xy=1085,349
AudioEffectMultiply      vcaLfoMod_5; //xy=1080,1676
AudioEffectMultiply      vcaLfoMod_4; //xy=1082,1352
AudioEffectMultiply      vcaLfoMod_3; //xy=1085,1026
AudioEffectMultiply      vcaLfoMod_2;   //xy=1090,702
AudioConnection          patchCord1(lfo, 0, vcaLfoAmount_1, 0);
AudioConnection          patchCord2(lfo, 0, vcoModMixer_1, 1);
AudioConnection          patchCord3(lfo, 0, vcfModMixer_1, 1);
AudioConnection          patchCord4(lfo, 0, vcoModMixer_2, 1);
AudioConnection          patchCord5(lfo, 0, vcaLfoAmount_2, 0);
AudioConnection          patchCord6(lfo, 0, vcfModMixer_2, 1);
AudioConnection          patchCord7(lfo, 0, vcoModMixer_3, 1);
AudioConnection          patchCord8(lfo, 0, vcaLfoAmount_3, 0);
AudioConnection          patchCord9(lfo, 0, vcfModMixer_3, 1);
AudioConnection          patchCord10(lfo, 0, vcoModMixer_4, 1);
AudioConnection          patchCord11(lfo, 0, vcaLfoAmount_4, 0);
AudioConnection          patchCord12(lfo, 0, vcfModMixer_4, 1);
AudioConnection          patchCord13(lfo, 0, vcoModMixer_5, 1);
AudioConnection          patchCord14(lfo, 0, vcaLfoAmount_5, 0);
AudioConnection          patchCord15(lfo, 0, vcfModMixer_5, 1);
AudioConnection          patchCord16(lfo, 0, vcoModMixer_6, 1);
AudioConnection          patchCord17(lfo, 0, vcfModMixer_6, 1);
AudioConnection          patchCord18(lfo, 0, vcaLfoAmount_6, 0);
AudioConnection          patchCord19(i2s1, 0, effect1In, 0);
AudioConnection          patchCord20(vcoPulseWidth_6, 0, vco1_6, 1);
AudioConnection          patchCord21(vcoPulseWidth_6, 0, vco2_6, 1);
AudioConnection          patchCord22(vcoPulseWidth_1, 0, vco1_1, 1);
AudioConnection          patchCord23(vcoPulseWidth_1, 0, vco2_1, 1);
AudioConnection          patchCord24(vcoPulseWidth_5, 0, vco1_5, 1);
AudioConnection          patchCord25(vcoPulseWidth_5, 0, vco2_5, 1);
AudioConnection          patchCord26(vcoPulseWidth_4, 0, vco1_4, 1);
AudioConnection          patchCord27(vcoPulseWidth_4, 0, vco2_4, 1);
AudioConnection          patchCord28(vcoPulseWidth_3, 0, vco1_3, 1);
AudioConnection          patchCord29(vcoPulseWidth_3, 0, vco2_3, 1);
AudioConnection          patchCord30(vcoPulseWidth_2, 0, vco1_2, 1);
AudioConnection          patchCord31(vcoPulseWidth_2, 0, vco2_2, 1);
AudioConnection          patchCord32(vcoModMixer_6, 0, vco1_6, 0);
AudioConnection          patchCord33(vcoModMixer_6, 0, vco2_6, 0);
AudioConnection          patchCord34(vcoModMixer_1, 0, vco1_1, 0);
AudioConnection          patchCord35(vcoModMixer_1, 0, vco2_1, 0);
AudioConnection          patchCord36(vcoModMixer_5, 0, vco1_5, 0);
AudioConnection          patchCord37(vcoModMixer_5, 0, vco2_5, 0);
AudioConnection          patchCord38(vcoModMixer_4, 0, vco1_4, 0);
AudioConnection          patchCord39(vcoModMixer_4, 0, vco2_4, 0);
AudioConnection          patchCord40(vcoModMixer_3, 0, vco1_3, 0);
AudioConnection          patchCord41(vcoModMixer_3, 0, vco2_3, 0);
AudioConnection          patchCord42(vcoModMixer_2, 0, vco1_2, 0);
AudioConnection          patchCord43(vcoModMixer_2, 0, vco2_2, 0);
AudioConnection          patchCord44(envelopeDc_1, envelope_1);
AudioConnection          patchCord45(envelopeDc_6, envelope_6);
AudioConnection          patchCord46(envelopeDc_5, envelope_5);
AudioConnection          patchCord47(envelopeDc_4, envelope_4);
AudioConnection          patchCord48(envelopeDc_3, envelope_3);
AudioConnection          patchCord49(envelopeDc_2, envelope_2);
AudioConnection          patchCord50(pinkNoise_6, 0, vcoMixer_6, 2);
AudioConnection          patchCord51(pinkNoise_1, 0, vcoMixer_1, 2);
AudioConnection          patchCord52(vco1_6, 0, vcoMixer_6, 0);
AudioConnection          patchCord53(pinkNoise_5, 0, vcoMixer_5, 2);
AudioConnection          patchCord54(vco1_1, 0, vcoMixer_1, 0);
AudioConnection          patchCord55(vco1_5, 0, vcoMixer_5, 0);
AudioConnection          patchCord56(pinkNoise_4, 0, vcoMixer_4, 2);
AudioConnection          patchCord57(vco1_4, 0, vcoMixer_4, 0);
AudioConnection          patchCord58(vco2_6, 0, vcoMixer_6, 1);
AudioConnection          patchCord59(pinkNoise_3, 0, vcoMixer_3, 2);
AudioConnection          patchCord60(vco2_1, 0, vcoMixer_1, 1);
AudioConnection          patchCord61(vco2_5, 0, vcoMixer_5, 1);
AudioConnection          patchCord62(vco1_3, 0, vcoMixer_3, 0);
AudioConnection          patchCord63(vco2_4, 0, vcoMixer_4, 1);
AudioConnection          patchCord64(vco2_3, 0, vcoMixer_3, 1);
AudioConnection          patchCord65(pinkNoise_2, 0, vcoMixer_2, 2);
AudioConnection          patchCord66(vco1_2, 0, vcoMixer_2, 0);
AudioConnection          patchCord67(vco2_2, 0, vcoMixer_2, 1);
AudioConnection          patchCord68(effect1Out, 0, synthMixer, 0);
AudioConnection          patchCord69(envelope_6, 0, vca_6, 1);
AudioConnection          patchCord70(envelope_6, 0, vcoModMixer_6, 0);
AudioConnection          patchCord71(envelope_6, 0, vcfModMixer_6, 0);
AudioConnection          patchCord72(envelope_1, 0, vca_1, 1);
AudioConnection          patchCord73(envelope_1, 0, vcoModMixer_1, 0);
AudioConnection          patchCord74(envelope_1, 0, vcfModMixer_1, 0);
AudioConnection          patchCord75(envelope_5, 0, vca_5, 1);
AudioConnection          patchCord76(envelope_5, 0, vcoModMixer_5, 0);
AudioConnection          patchCord77(envelope_5, 0, vcfModMixer_5, 0);
AudioConnection          patchCord78(envelope_4, 0, vca_4, 1);
AudioConnection          patchCord79(envelope_4, 0, vcoModMixer_4, 0);
AudioConnection          patchCord80(envelope_4, 0, vcfModMixer_4, 0);
AudioConnection          patchCord81(envelope_3, 0, vca_3, 1);
AudioConnection          patchCord82(envelope_3, 0, vcoModMixer_3, 0);
AudioConnection          patchCord83(envelope_3, 0, vcfModMixer_3, 0);
AudioConnection          patchCord84(envelope_2, 0, vca_2, 1);
AudioConnection          patchCord85(envelope_2, 0, vcoModMixer_2, 0);
AudioConnection          patchCord86(envelope_2, 0, vcfModMixer_2, 0);
AudioConnection          patchCord87(vcoMixer_6, 0, vcf_6, 0);
AudioConnection          patchCord88(vcoMixer_1, 0, vcf_1, 0);
AudioConnection          patchCord89(vcoMixer_5, 0, vcf_5, 0);
AudioConnection          patchCord90(vcoMixer_4, 0, vcf_4, 0);
AudioConnection          patchCord91(vcoMixer_3, 0, vcf_3, 0);
AudioConnection          patchCord92(vcoMixer_2, 0, vcf_2, 0);
AudioConnection          patchCord93(vcfModMixer_6, 0, vcf_6, 1);
AudioConnection          patchCord94(vcfModMixer_1, 0, vcf_1, 1);
AudioConnection          patchCord95(vcfModMixer_5, 0, vcf_5, 1);
AudioConnection          patchCord96(vcfModMixer_4, 0, vcf_4, 1);
AudioConnection          patchCord97(vcfModMixer_3, 0, vcf_3, 1);
AudioConnection          patchCord98(vcfModMixer_2, 0, vcf_2, 1);
AudioConnection          patchCord99(synthMixer, effect2In);
AudioConnection          patchCord100(vcf_6, vcaPassThroughEnvelope_6);
AudioConnection          patchCord101(vcf_6, 0, vca_6, 0);
AudioConnection          patchCord102(vcf_1, vcaPassThroughEnvelope_1);
AudioConnection          patchCord103(vcf_1, 0, vca_1, 0);
AudioConnection          patchCord104(vcf_5, vcaPassThroughEnvelope_5);
AudioConnection          patchCord105(vcf_5, 0, vca_5, 0);
AudioConnection          patchCord106(vcf_4, vcaPassThroughEnvelope_4);
AudioConnection          patchCord107(vcf_4, 0, vca_4, 0);
AudioConnection          patchCord108(vcf_3, vcaPassThroughEnvelope_3);
AudioConnection          patchCord109(vcf_3, 0, vca_3, 0);
AudioConnection          patchCord110(vcf_2, vcaPassThroughEnvelope_2);
AudioConnection          patchCord111(vcf_2, 0, vca_2, 0);
AudioConnection          patchCord112(vcaPassThroughEnvelope_6, 0, vcaMixer_6, 0);
AudioConnection          patchCord113(vcaPassThroughEnvelope_1, 0, vcaMixer_1, 0);
AudioConnection          patchCord114(vcaPassThroughEnvelope_5, 0, vcaMixer_5, 0);
AudioConnection          patchCord115(vcaPassThroughEnvelope_4, 0, vcaMixer_4, 0);
AudioConnection          patchCord116(vcaLfoDcOffset_6, 0, vcaLfoAmount_6, 1);
AudioConnection          patchCord117(vcaLfoDcOffset_1, 0, vcaLfoAmount_1, 1);
AudioConnection          patchCord118(vcaPassThroughEnvelope_3, 0, vcaMixer_3, 0);
AudioConnection          patchCord119(vcaLfoDcOffset_5, 0, vcaLfoAmount_5, 1);
AudioConnection          patchCord120(vcaLfoDcOffset_4, 0, vcaLfoAmount_4, 1);
AudioConnection          patchCord121(vcaLfoDcOffset_3, 0, vcaLfoAmount_3, 1);
AudioConnection          patchCord122(vcaPassThroughEnvelope_2, 0, vcaMixer_2, 0);
AudioConnection          patchCord123(vcaLfoDcOffset_2, 0, vcaLfoAmount_2, 1);
AudioConnection          patchCord124(vca_6, 0, vcaMixer_6, 1);
AudioConnection          patchCord125(vca_1, 0, vcaMixer_1, 1);
AudioConnection          patchCord126(vca_5, 0, vcaMixer_5, 1);
AudioConnection          patchCord127(vca_4, 0, vcaMixer_4, 1);
AudioConnection          patchCord128(vca_3, 0, vcaMixer_3, 1);
AudioConnection          patchCord129(vca_2, 0, vcaMixer_2, 1);
AudioConnection          patchCord130(effect2Out, 0, audioOut, 0);
AudioConnection          patchCord131(effect2Out, 0, audioOut, 1);
AudioConnection          patchCord132(vcaMixer_6, 0, vcaLfoMod_6, 0);
AudioConnection          patchCord133(vcaMixer_1, 0, vcaLfoMod_1, 0);
AudioConnection          patchCord134(vcaMixer_5, 0, vcaLfoMod_5, 0);
AudioConnection          patchCord135(vcaMixer_4, 0, vcaLfoMod_4, 0);
AudioConnection          patchCord136(vcaMixer_3, 0, vcaLfoMod_3, 0);
AudioConnection          patchCord137(vcaMixer_2, 0, vcaLfoMod_2, 0);
AudioConnection          patchCord138(vcaLfoAmount_6, 0, vcaLfoMod_6, 1);
AudioConnection          patchCord139(vcaLfoAmount_1, 0, vcaLfoMod_1, 1);
AudioConnection          patchCord140(vcaLfoAmount_5, 0, vcaLfoMod_5, 1);
AudioConnection          patchCord141(vcaLfoAmount_4, 0, vcaLfoMod_4, 1);
AudioConnection          patchCord142(vcaLfoAmount_3, 0, vcaLfoMod_3, 1);
AudioConnection          patchCord143(vcaLfoAmount_2, 0, vcaLfoMod_2, 1);
AudioConnection          patchCord144(synthPolyphony_1, 0, synthMixer, 1);
AudioConnection          patchCord145(synthPolyphony_2, 0, synthMixer, 2);
AudioConnection          patchCord146(vcaLfoMod_6, 0, synthPolyphony_2, 2);
AudioConnection          patchCord147(vcaLfoMod_1, 0, synthPolyphony_1, 0);
AudioConnection          patchCord148(vcaLfoMod_5, 0, synthPolyphony_2, 1);
AudioConnection          patchCord149(vcaLfoMod_4, 0, synthPolyphony_2, 0);
AudioConnection          patchCord150(vcaLfoMod_3, 0, synthPolyphony_1, 2);
AudioConnection          patchCord151(vcaLfoMod_2, 0, synthPolyphony_1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=127,128
// GUItool: end automatically generated code


const byte MAX_BUFFER = 8; //Size of keyboard buffer
const byte NUM_VOICES = 6; // Number of polyphony voices
const float noteFreqs[128] = {8.176, 8.662, 9.177, 9.723, 10.301, 10.913, 11.562, 12.25, 12.978, 13.75, 14.568, 15.434, 16.352, 17.324, 18.354, 19.445, 20.602, 21.827, 23.125, 24.5, 25.957, 27.5, 29.135, 30.868, 32.703, 34.648, 36.708, 38.891, 41.203, 43.654, 46.249, 48.999, 51.913, 55, 58.27, 61.735, 65.406, 69.296, 73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, 110, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, 164.814, 174.614, 184.997, 195.998, 207.652, 220, 233.082, 246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, 369.994, 391.995, 415.305, 440, 466.164, 493.883, 523.251, 554.365, 587.33, 622.254, 659.255, 698.456, 739.989, 783.991, 830.609, 880, 932.328, 987.767, 1046.502, 1108.731, 1174.659, 1244.508, 1318.51, 1396.913, 1479.978, 1567.982, 1661.219, 1760, 1864.655, 1975.533, 2093.005, 2217.461, 2349.318, 2489.016, 2637.02, 2793.826, 2959.955, 3135.963, 3322.438, 3520, 3729.31, 3951.066, 4186.009, 4434.922, 4698.636, 4978.032, 5274.041, 5587.652, 5919.911, 6271.927, 6644.875, 7040, 7458.62, 7902.133, 8372.018, 8869.844, 9397.273, 9956.063, 10548.08, 11175.3, 11839.82, 12543.85};
const float DIV127 = (1.0 / 127.0);

const int MAX_FILTER_FREQ = 10000;
const int FILTER_OCTAVE_CONTROL = 4.0;
const float Q_RATIO = 1.2;
const float Q_FLOOR = 0.0;
const float MIN_LFO_FREQ = 0.1;
const float MAX_LFO_FREQ = 12.0;
const int MAX_ENVELOPE_MS = 3000;


// GLOBAL VARIABLES
SynthMode synthMode;
byte globalNote = 0;
int octave = 0;
float detuneFactor = 1;
float bendFactor = 1;
int bendRange = 12;
MidiNote noteBuffer[MAX_BUFFER];
byte notesBuffered = 0;
bool vcoPlaying[NUM_VOICES];


void initAudioEngine(usb_midi_class usbMIDIControl) {
  AudioMemory(1024);

  synthMixer.gain(0, 1.0);
  synthMixer.gain(1, 1.0);
  synthMixer.gain(2, 1.0);

  synthPolyphony_1.gain(0, 0.8);
  synthPolyphony_1.gain(1, 0.8);
  synthPolyphony_1.gain(2, 0.8);

  synthPolyphony_2.gain(0, 0.8);
  synthPolyphony_2.gain(1, 0.8);
  synthPolyphony_2.gain(2, 0.8);

  effect1In.begin();
  effect2In.begin();

  usbMIDIControl.setHandleControlChange(midiControlChange);
  usbMIDIControl.setHandleNoteOff(midiNoteOff);
  usbMIDIControl.setHandleNoteOn(midiNoteOn);
  usbMIDIControl.setHandlePitchChange(midiPitchBend);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.70);

  synthMode = LastNotePriority;

  vcoPlaying[0] = false;
  vcoPlaying[1] = false;

  vco1_1.begin(WAVEFORM_SAWTOOTH);
  vco1_1.amplitude(0.75);
  vco1_1.frequency(82.41);
  vco1_2.begin(WAVEFORM_SAWTOOTH);
  vco1_2.amplitude(0.75);
  vco1_2.frequency(82.41);
  vco1_3.begin(WAVEFORM_SAWTOOTH);
  vco1_3.amplitude(0.75);
  vco1_3.frequency(82.41);
  vco1_4.begin(WAVEFORM_SAWTOOTH);
  vco1_4.amplitude(0.75);
  vco1_4.frequency(82.41);
  vco1_5.begin(WAVEFORM_SAWTOOTH);
  vco1_5.amplitude(0.75);
  vco1_5.frequency(82.41);
  vco1_6.begin(WAVEFORM_SAWTOOTH);
  vco1_6.amplitude(0.75);
  vco1_6.frequency(82.41);

  vco2_1.begin(WAVEFORM_SAWTOOTH);
  vco2_1.amplitude(0.75);
  vco2_1.frequency(123);
  vco2_2.begin(WAVEFORM_SAWTOOTH);
  vco2_2.amplitude(0.75);
  vco2_2.frequency(123);
  vco2_3.begin(WAVEFORM_SAWTOOTH);
  vco2_3.amplitude(0.75);
  vco2_3.frequency(123);
  vco2_4.begin(WAVEFORM_SAWTOOTH);
  vco2_4.amplitude(0.75);
  vco2_4.frequency(123);
  vco2_5.begin(WAVEFORM_SAWTOOTH);
  vco2_5.amplitude(0.75);
  vco2_5.frequency(123);
  vco2_6.begin(WAVEFORM_SAWTOOTH);
  vco2_6.amplitude(0.75);
  vco2_6.frequency(123);

  vcoPulseWidth_1.amplitude(0.5);
  vcoPulseWidth_2.amplitude(0.5);
  vcoPulseWidth_3.amplitude(0.5);
  vcoPulseWidth_4.amplitude(0.5);
  vcoPulseWidth_5.amplitude(0.5);
  vcoPulseWidth_6.amplitude(0.5);

  pinkNoise_1.amplitude(1.0);
  pinkNoise_2.amplitude(1.0);
  pinkNoise_3.amplitude(1.0);
  pinkNoise_4.amplitude(1.0);
  pinkNoise_5.amplitude(1.0);
  pinkNoise_6.amplitude(1.0);

  vcoModMixer_1.gain(0, 0.0);
  vcoModMixer_1.gain(1, 0.0);
  vcoModMixer_2.gain(0, 0.0);
  vcoModMixer_2.gain(1, 0.0);
  vcoModMixer_3.gain(0, 0.0);
  vcoModMixer_3.gain(1, 0.0);
  vcoModMixer_4.gain(0, 0.0);
  vcoModMixer_4.gain(1, 0.0);
  vcoModMixer_5.gain(0, 0.0);
  vcoModMixer_5.gain(1, 0.0);
  vcoModMixer_6.gain(0, 0.0);
  vcoModMixer_6.gain(1, 0.0);

  vcoMixer_1.gain(0, 1.0);
  vcoMixer_1.gain(1, 1.0);
  vcoMixer_1.gain(2, 0.0);
  vcoMixer_2.gain(0, 1.0);
  vcoMixer_2.gain(1, 1.0);
  vcoMixer_2.gain(2, 0.0);
  vcoMixer_3.gain(0, 1.0);
  vcoMixer_3.gain(1, 1.0);
  vcoMixer_3.gain(2, 0.0);
  vcoMixer_4.gain(0, 1.0);
  vcoMixer_4.gain(1, 1.0);
  vcoMixer_4.gain(2, 0.0);
  vcoMixer_5.gain(0, 1.0);
  vcoMixer_5.gain(1, 1.0);
  vcoMixer_5.gain(2, 0.0);
  vcoMixer_6.gain(0, 1.0);
  vcoMixer_6.gain(1, 1.0);
  vcoMixer_6.gain(2, 0.0);

  vcf_1.resonance(Q_FLOOR);
  vcf_1.frequency(MAX_FILTER_FREQ);
  vcf_1.octaveControl(FILTER_OCTAVE_CONTROL);
  vcf_2.resonance(Q_FLOOR);
  vcf_2.frequency(MAX_FILTER_FREQ);
  vcf_2.octaveControl(FILTER_OCTAVE_CONTROL);
  vcf_3.resonance(Q_FLOOR);
  vcf_3.frequency(MAX_FILTER_FREQ);
  vcf_3.octaveControl(FILTER_OCTAVE_CONTROL);
  vcf_4.resonance(Q_FLOOR);
  vcf_4.frequency(MAX_FILTER_FREQ);
  vcf_4.octaveControl(FILTER_OCTAVE_CONTROL);
  vcf_5.resonance(Q_FLOOR);
  vcf_5.frequency(MAX_FILTER_FREQ);
  vcf_5.octaveControl(FILTER_OCTAVE_CONTROL);
  vcf_6.resonance(Q_FLOOR);
  vcf_6.frequency(MAX_FILTER_FREQ);
  vcf_6.octaveControl(FILTER_OCTAVE_CONTROL);

  vcfModMixer_1.gain(0, 0.0);
  vcfModMixer_1.gain(1, 0.0);
  vcfModMixer_2.gain(0, 0.0);
  vcfModMixer_2.gain(1, 0.0);
  vcfModMixer_3.gain(0, 0.0);
  vcfModMixer_3.gain(1, 0.0);
  vcfModMixer_4.gain(0, 0.0);
  vcfModMixer_4.gain(1, 0.0);
  vcfModMixer_5.gain(0, 0.0);
  vcfModMixer_5.gain(1, 0.0);
  vcfModMixer_6.gain(0, 0.0);
  vcfModMixer_6.gain(1, 0.0);

  vcaPassThroughEnvelope_1.attack(1);
  vcaPassThroughEnvelope_1.decay(0);
  vcaPassThroughEnvelope_1.sustain(1);
  vcaPassThroughEnvelope_1.release(1);
  vcaPassThroughEnvelope_2.attack(1);
  vcaPassThroughEnvelope_2.decay(0);
  vcaPassThroughEnvelope_2.sustain(1);
  vcaPassThroughEnvelope_2.release(1);
  vcaPassThroughEnvelope_3.attack(1);
  vcaPassThroughEnvelope_3.decay(0);
  vcaPassThroughEnvelope_3.sustain(1);
  vcaPassThroughEnvelope_3.release(1);
  vcaPassThroughEnvelope_4.attack(1);
  vcaPassThroughEnvelope_4.decay(0);
  vcaPassThroughEnvelope_4.sustain(1);
  vcaPassThroughEnvelope_4.release(1);
  vcaPassThroughEnvelope_5.attack(1);
  vcaPassThroughEnvelope_5.decay(0);
  vcaPassThroughEnvelope_5.sustain(1);
  vcaPassThroughEnvelope_5.release(1);
  vcaPassThroughEnvelope_6.attack(1);
  vcaPassThroughEnvelope_6.decay(0);
  vcaPassThroughEnvelope_6.sustain(1);
  vcaPassThroughEnvelope_6.release(1);

  vcaMixer_1.gain(0, 0.0);
  vcaMixer_1.gain(1, 1.0);
  vcaMixer_2.gain(0, 0.0);
  vcaMixer_2.gain(1, 1.0);
  vcaMixer_3.gain(0, 0.0);
  vcaMixer_3.gain(1, 1.0);
  vcaMixer_4.gain(0, 0.0);
  vcaMixer_4.gain(1, 1.0);
  vcaMixer_5.gain(0, 0.0);
  vcaMixer_5.gain(1, 1.0);
  vcaMixer_6.gain(0, 0.0);
  vcaMixer_6.gain(1, 1.0);

  vcaLfoDcOffset_1.amplitude(1.0);
  vcaLfoDcOffset_2.amplitude(1.0);
  vcaLfoDcOffset_3.amplitude(1.0);
  vcaLfoDcOffset_4.amplitude(1.0);
  vcaLfoDcOffset_5.amplitude(1.0);
  vcaLfoDcOffset_6.amplitude(1.0);

  vcaLfoAmount_1.gain(0, 0.0);
  vcaLfoAmount_1.gain(1, 1.0);
  vcaLfoAmount_2.gain(0, 0.0);
  vcaLfoAmount_2.gain(1, 1.0);
  vcaLfoAmount_3.gain(0, 0.0);
  vcaLfoAmount_3.gain(1, 1.0);
  vcaLfoAmount_4.gain(0, 0.0);
  vcaLfoAmount_4.gain(1, 1.0);
  vcaLfoAmount_5.gain(0, 0.0);
  vcaLfoAmount_5.gain(1, 1.0);
  vcaLfoAmount_6.gain(0, 0.0);
  vcaLfoAmount_6.gain(1, 1.0);

  envelopeDc_1.amplitude(1.0);
  envelopeDc_2.amplitude(1.0);
  envelopeDc_3.amplitude(1.0);
  envelopeDc_4.amplitude(1.0);
  envelopeDc_5.amplitude(1.0);
  envelopeDc_6.amplitude(1.0);

  envelope_1.attack(1);
  envelope_1.decay(0);
  envelope_1.sustain(1);
  envelope_1.release(1);
  envelope_2.attack(1);
  envelope_2.decay(0);
  envelope_2.sustain(1);
  envelope_2.release(1);
  envelope_3.attack(1);
  envelope_3.decay(0);
  envelope_3.sustain(1);
  envelope_3.release(1);
  envelope_4.attack(1);
  envelope_4.decay(0);
  envelope_4.sustain(1);
  envelope_4.release(1);
  envelope_5.attack(1);
  envelope_5.decay(0);
  envelope_5.sustain(1);
  envelope_5.release(1);
  envelope_6.attack(1);
  envelope_6.decay(0);
  envelope_6.sustain(1);
  envelope_6.release(1);

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

void setSynthMode(SynthMode mode) {
  vcoStopAllNotes();
  synthMode = mode;
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
  if (synthMode == Monophonic) {
    if (notesBuffered < MAX_BUFFER) {
      midiNote.vcoNumber = 0;
      vcoTrigger(midiNote);
      envelopeTrigger(midiNote);
      noteBuffer[notesBuffered] = midiNote;
      notesBuffered++;
    }

  } else { // Polyphonic
    if (notesBuffered >= NUM_VOICES) {
      removeBufferNote(noteBuffer[0]);    
    }
    int nextVcoNumber = getNextOscillator();
    midiNote.vcoNumber = nextVcoNumber;
    vcoPlaying[midiNote.vcoNumber] = true;
    noteBuffer[notesBuffered] = midiNote;
    notesBuffered++;
    vcoTrigger(midiNote);
    envelopeTrigger(midiNote);
  }
}

void removeBufferNote(MidiNote midiNote) {
  if (synthMode == Monophonic) {
    if (notesBuffered != 0) {
      for (int i = 0; i < notesBuffered; i++) {
        if (noteBuffer[i].note == midiNote.note) {
          MidiNote removedNote = noteBuffer[i];
          for (int j = i; j < (notesBuffered - 1); j++) {
            noteBuffer[j] = noteBuffer[j + 1];
          }
          notesBuffered--;
          if (notesBuffered != 0) {
              vcoTrigger(noteBuffer[notesBuffered - 1]);
            return;
          }
          else {
            vcoStop(removedNote);
            return;
          }
        }
      }
    }
  
  } else { // Polyphonic
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
          return;
        }
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
    case 2:
      vco1_3.frequency(noteFreqs[midiNote.note] * bendFactor);
      vco2_3.frequency(noteFreqs[midiNote.note + octave] * detuneFactor * bendFactor);
      vco1_3.amplitude(velo);
      vco2_3.amplitude(velo);
      pinkNoise_3.amplitude(velo);
      break;
    case 3:
      vco1_4.frequency(noteFreqs[midiNote.note] * bendFactor);
      vco2_4.frequency(noteFreqs[midiNote.note + octave] * detuneFactor * bendFactor);
      vco1_4.amplitude(velo);
      vco2_4.amplitude(velo);
      pinkNoise_4.amplitude(velo);
      break;
    case 4:
      vco1_5.frequency(noteFreqs[midiNote.note] * bendFactor);
      vco2_5.frequency(noteFreqs[midiNote.note + octave] * detuneFactor * bendFactor);
      vco1_5.amplitude(velo);
      vco2_5.amplitude(velo);
      pinkNoise_5.amplitude(velo);
      break;
    case 5:
      vco1_6.frequency(noteFreqs[midiNote.note] * bendFactor);
      vco2_6.frequency(noteFreqs[midiNote.note + octave] * detuneFactor * bendFactor);
      vco1_6.amplitude(velo);
      vco2_6.amplitude(velo);
      pinkNoise_6.amplitude(velo);
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
    case 2:
      envelope_3.noteOn();
      vcaPassThroughEnvelope_3.noteOn();
      break;
    case 3:
      envelope_4.noteOn();
      vcaPassThroughEnvelope_4.noteOn();
      break;
    case 4:
      envelope_5.noteOn();
      vcaPassThroughEnvelope_5.noteOn();
      break;
    case 5:
      envelope_6.noteOn();
      vcaPassThroughEnvelope_6.noteOn();
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
    case 2:
      envelope_3.noteOff();
      vcaPassThroughEnvelope_3.noteOff();
      break;
    case 3:
      envelope_4.noteOff();
      vcaPassThroughEnvelope_4.noteOff();
      break;
    case 4:
      envelope_5.noteOff();
      vcaPassThroughEnvelope_5.noteOff();
      break;
    case 5:
      envelope_6.noteOff();
      vcaPassThroughEnvelope_6.noteOff();
      break;
  }
}

void vcoStopAllNotes() {
  for (int i = 0; i < notesBuffered; i++) {
    removeBufferNote(noteBuffer[0]);
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
      case 2:
        vco1_3.frequency(noteFreqs[midiNote.note] * bendFactor);
        vco2_3.frequency(noteFreqs[midiNote.note + octave] * detuneFactor * bendFactor);
        break;
      case 3:
        vco1_4.frequency(noteFreqs[midiNote.note] * bendFactor);
        vco2_4.frequency(noteFreqs[midiNote.note + octave] * detuneFactor * bendFactor);
        break;
      case 4:
        vco1_5.frequency(noteFreqs[midiNote.note] * bendFactor);
        vco2_5.frequency(noteFreqs[midiNote.note + octave] * detuneFactor * bendFactor);
        break;
      case 5:
        vco1_6.frequency(noteFreqs[midiNote.note] * bendFactor);
        vco2_6.frequency(noteFreqs[midiNote.note + octave] * detuneFactor * bendFactor);
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
      vcoMixer_3.gain(0, (value * DIV127));
      vcoMixer_4.gain(0, (value * DIV127));
      vcoMixer_5.gain(0, (value * DIV127));
      vcoMixer_6.gain(0, (value * DIV127));
      break;

    case 103:
      // VCO 2 Level
      vcoMixer_1.gain(1, (value * DIV127));
      vcoMixer_2.gain(1, (value * DIV127));
      vcoMixer_3.gain(1, (value * DIV127));
      vcoMixer_4.gain(1, (value * DIV127));
      vcoMixer_5.gain(1, (value * DIV127));
      vcoMixer_6.gain(1, (value * DIV127));
      break;

    case 104:
      // Pink Noise Level
      vcoMixer_1.gain(2, (value * DIV127));
      vcoMixer_2.gain(2, (value * DIV127));
      vcoMixer_3.gain(2, (value * DIV127));
      vcoMixer_4.gain(2, (value * DIV127));
      vcoMixer_5.gain(2, (value * DIV127));
      vcoMixer_6.gain(2, (value * DIV127));
      break;

    case 105:
      // VCO 1 Waveform
      switch (value) {
        case 0:
          vco1_1.begin(WAVEFORM_SINE);
          vco1_2.begin(WAVEFORM_SINE);
          vco1_3.begin(WAVEFORM_SINE);
          vco1_4.begin(WAVEFORM_SINE);
          vco1_5.begin(WAVEFORM_SINE);
          vco1_6.begin(WAVEFORM_SINE);
          break;
        case 1:
          vco1_1.begin(WAVEFORM_TRIANGLE);
          vco1_2.begin(WAVEFORM_TRIANGLE);
          vco1_3.begin(WAVEFORM_TRIANGLE);
          vco1_4.begin(WAVEFORM_TRIANGLE);
          vco1_5.begin(WAVEFORM_TRIANGLE);
          vco1_6.begin(WAVEFORM_TRIANGLE);
          break;
        case 2:
          vco1_1.begin(WAVEFORM_PULSE);
          vco1_2.begin(WAVEFORM_PULSE);
          vco1_3.begin(WAVEFORM_PULSE);
          vco1_4.begin(WAVEFORM_PULSE);
          vco1_5.begin(WAVEFORM_PULSE);
          vco1_6.begin(WAVEFORM_PULSE);
          break;
        case 3:
          vco1_1.begin(WAVEFORM_SAWTOOTH);
          vco1_2.begin(WAVEFORM_SAWTOOTH);
          vco1_3.begin(WAVEFORM_SAWTOOTH);
          vco1_4.begin(WAVEFORM_SAWTOOTH);
          vco1_5.begin(WAVEFORM_SAWTOOTH);
          vco1_6.begin(WAVEFORM_SAWTOOTH);
          break;
      }
      break;

    case 106:
      // VCO 2 Waveform
      switch (value) {
        case 0:
          vco2_1.begin(WAVEFORM_SINE);
          vco2_2.begin(WAVEFORM_SINE);
          vco2_3.begin(WAVEFORM_SINE);
          vco2_4.begin(WAVEFORM_SINE);
          vco2_5.begin(WAVEFORM_SINE);
          vco2_6.begin(WAVEFORM_SINE);
          break;
        case 1:
          vco2_1.begin(WAVEFORM_TRIANGLE);
          vco2_2.begin(WAVEFORM_TRIANGLE);
          vco2_3.begin(WAVEFORM_TRIANGLE);
          vco2_4.begin(WAVEFORM_TRIANGLE);
          vco2_5.begin(WAVEFORM_TRIANGLE);
          vco2_6.begin(WAVEFORM_TRIANGLE);
          break;
        case 2:
          vco2_1.begin(WAVEFORM_PULSE);
          vco2_2.begin(WAVEFORM_PULSE);
          vco2_3.begin(WAVEFORM_PULSE);
          vco2_4.begin(WAVEFORM_PULSE);
          vco2_5.begin(WAVEFORM_PULSE);
          vco2_6.begin(WAVEFORM_PULSE);
          break;
        case 3:
          vco2_1.begin(WAVEFORM_SAWTOOTH);
          vco2_2.begin(WAVEFORM_SAWTOOTH);
          vco2_3.begin(WAVEFORM_SAWTOOTH);
          vco2_4.begin(WAVEFORM_SAWTOOTH);
          vco2_5.begin(WAVEFORM_SAWTOOTH);
          vco2_6.begin(WAVEFORM_SAWTOOTH);
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
      vcoModMixer_3.gain(0, (value - 64) * DIV127 * 0.25);
      vcoModMixer_4.gain(0, (value - 64) * DIV127 * 0.25);
      vcoModMixer_5.gain(0, (value - 64) * DIV127 * 0.25);
      vcoModMixer_6.gain(0, (value - 64) * DIV127 * 0.25);
      break;

    case 111:
      // VCO LFO
      vcoModMixer_1.gain(1, 0.25 * value * DIV127);
      vcoModMixer_2.gain(1, 0.25 * value * DIV127);
      vcoModMixer_3.gain(1, 0.25 * value * DIV127);
      vcoModMixer_4.gain(1, 0.25 * value * DIV127);
      vcoModMixer_5.gain(1, 0.25 * value * DIV127);
      vcoModMixer_6.gain(1, 0.25 * value * DIV127);
      break;

    // ============================== VCF Controls ==============================
    case 112:
      // VCF Frequency
      vcf_1.frequency(MAX_FILTER_FREQ * (value * DIV127));
      vcf_2.frequency(MAX_FILTER_FREQ * (value * DIV127));
      vcf_3.frequency(MAX_FILTER_FREQ * (value * DIV127));
      vcf_4.frequency(MAX_FILTER_FREQ * (value * DIV127));
      vcf_5.frequency(MAX_FILTER_FREQ * (value * DIV127));
      vcf_6.frequency(MAX_FILTER_FREQ * (value * DIV127));
      break;

    case 113:
      // VCF Resonance
      vcf_1.resonance(Q_RATIO * (value * DIV127) + Q_FLOOR);
      vcf_2.resonance(Q_RATIO * (value * DIV127) + Q_FLOOR);
      vcf_3.resonance(Q_RATIO * (value * DIV127) + Q_FLOOR);
      vcf_4.resonance(Q_RATIO * (value * DIV127) + Q_FLOOR);
      vcf_5.resonance(Q_RATIO * (value * DIV127) + Q_FLOOR);
      vcf_6.resonance(Q_RATIO * (value * DIV127) + Q_FLOOR);
      break;

    case 114:
      // VCF Envelope
      vcfModMixer_1.gain(0, ((int)value - 64) / 64.0);
      vcfModMixer_2.gain(0, ((int)value - 64) / 64.0);
      vcfModMixer_3.gain(0, ((int)value - 64) / 64.0);
      vcfModMixer_4.gain(0, ((int)value - 64) / 64.0);
      vcfModMixer_5.gain(0, ((int)value - 64) / 64.0);
      vcfModMixer_6.gain(0, ((int)value - 64) / 64.0);
      break;

    case 115:
      // VCF LFO
      vcfModMixer_1.gain(1, value * DIV127);
      vcfModMixer_2.gain(1, value * DIV127);
      vcfModMixer_3.gain(1, value * DIV127);
      vcfModMixer_4.gain(1, value * DIV127);
      vcfModMixer_5.gain(1, value * DIV127);
      vcfModMixer_6.gain(1, value * DIV127);
      break;

    // ============================== VCA Controls ==============================
    case 116:
      // VCA Envelope
      floatVal = value * DIV127;
      vcaMixer_1.gain(0, 1.0 - floatVal);
      vcaMixer_2.gain(0, 1.0 - floatVal);
      vcaMixer_3.gain(0, 1.0 - floatVal);
      vcaMixer_4.gain(0, 1.0 - floatVal);
      vcaMixer_5.gain(0, 1.0 - floatVal);
      vcaMixer_6.gain(0, 1.0 - floatVal);
      vcaMixer_1.gain(1, floatVal);
      vcaMixer_2.gain(1, floatVal);
      vcaMixer_3.gain(1, floatVal);
      vcaMixer_4.gain(1, floatVal);
      vcaMixer_5.gain(1, floatVal);
      vcaMixer_6.gain(1, floatVal);
      break;

    case 117:
      // VCA LFO
      floatVal = 0.5 * value * DIV127;
      vcaLfoAmount_1.gain(0, floatVal);
      vcaLfoAmount_2.gain(0, floatVal);
      vcaLfoAmount_3.gain(0, floatVal);
      vcaLfoAmount_4.gain(0, floatVal);
      vcaLfoAmount_5.gain(0, floatVal);
      vcaLfoAmount_6.gain(0, floatVal);
      vcaLfoAmount_1.gain(1, 1.0 - floatVal);
      vcaLfoAmount_2.gain(1, 1.0 - floatVal);
      vcaLfoAmount_3.gain(1, 1.0 - floatVal);
      vcaLfoAmount_4.gain(1, 1.0 - floatVal);
      vcaLfoAmount_5.gain(1, 1.0 - floatVal);
      vcaLfoAmount_6.gain(1, 1.0 - floatVal);
      break;

    // ============================== Envelope Controls ==============================
    case 118:
      // Attack
      envelope_1.attack(MAX_ENVELOPE_MS * (value * DIV127) + 1);
      envelope_2.attack(MAX_ENVELOPE_MS * (value * DIV127) + 1);
      envelope_3.attack(MAX_ENVELOPE_MS * (value * DIV127) + 1);
      envelope_4.attack(MAX_ENVELOPE_MS * (value * DIV127) + 1);
      envelope_5.attack(MAX_ENVELOPE_MS * (value * DIV127) + 1);
      envelope_6.attack(MAX_ENVELOPE_MS * (value * DIV127) + 1);
      break;

    case 119:
      // Decay
      envelope_1.decay(MAX_ENVELOPE_MS * (value * DIV127));
      envelope_2.decay(MAX_ENVELOPE_MS * (value * DIV127));
      envelope_3.decay(MAX_ENVELOPE_MS * (value * DIV127));
      envelope_4.decay(MAX_ENVELOPE_MS * (value * DIV127));
      envelope_5.decay(MAX_ENVELOPE_MS * (value * DIV127));
      envelope_6.decay(MAX_ENVELOPE_MS * (value * DIV127));
      break;

    case 120:
      // Sustain
      envelope_1.sustain(value * DIV127);
      envelope_2.sustain(value * DIV127);
      envelope_3.sustain(value * DIV127);
      envelope_4.sustain(value * DIV127);
      envelope_5.sustain(value * DIV127);
      envelope_6.sustain(value * DIV127);
      break;

    case 121:
      // Release
      envelope_1.release(MAX_ENVELOPE_MS * (value * DIV127));
      envelope_2.release(MAX_ENVELOPE_MS * (value * DIV127));
      envelope_3.release(MAX_ENVELOPE_MS * (value * DIV127));
      envelope_4.release(MAX_ENVELOPE_MS * (value * DIV127));
      envelope_5.release(MAX_ENVELOPE_MS * (value * DIV127));
      envelope_6.release(MAX_ENVELOPE_MS * (value * DIV127));
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
