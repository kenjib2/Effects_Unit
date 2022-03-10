#ifndef PITCH_SHIFT_H
#define PITCH_SHIFT_H


/*
https://www.kvraudio.com/forum/viewtopic.php?t=476173

Have you tried granular pitch shifting ? It's a time domain technique that is really fast. It involves keeping
a sample history and having two buffer reads that are positioned half the buffer size apart. These read the past
samples at the desired speed, and to prevent the buffer loop being heard, each read is faded in and out at the
buffer boundaries. Because they loop alternatively you don't hear the loop as one fades in as the other fades out.

It's a neat technique but the loop size has to be about 2000 samples or so as to not lose the lowest frequencies
in the audio.
*/


#include "../../Util.h"
#include "../delay/AudioBuffer.h"
#include "../fx/CjFilter.h"


const int PITCH_SHIFT_BUFFER_SIZE = 3000;
const int FADE_SIZE = 700;
const int SWAP_MARGIN = 10;
const float LOW_PASS_FILTER_FACTOR = 0.06f;


class PitchShift : public WriteInsert {
protected:
	int bufferSize;
	int fadeSize;
	float hpFilterFactor;
	int16_t* buffer;
	int writeIndex;
	float floatIndex;
	float floatIndex2;
	CjFilter* hpFilter;
	CjFilter* lpFilter;


public:
	float playbackSpeed;


	PitchShift(int bufferSize = PITCH_SHIFT_BUFFER_SIZE, int fadeSize = FADE_SIZE)
		: bufferSize(bufferSize)
		, fadeSize(fadeSize)
		, writeIndex(0)
		, floatIndex(bufferSize / 4.f)
		, floatIndex2(bufferSize * 3 / 4.f)
		, playbackSpeed(2.f)
	{
		buffer = new int16_t[bufferSize]();
		hpFilter = new CjFilter();
		lpFilter = new CjFilter();
		hpFilterFactor = 1.f;
	}


	~PitchShift() {
		delete buffer;
		delete hpFilter;
		delete lpFilter;
	}


	float samplesAhead() {
		float relativeIndex = floatIndex;
		if (relativeIndex < writeIndex) {
			relativeIndex += bufferSize;
		}

		return (relativeIndex - writeIndex) / playbackSpeed;
	}


	float samplesRemaining() {
		float relativeIndex = floatIndex;
		if (relativeIndex > writeIndex) {
			relativeIndex -= bufferSize;
		}

		return (writeIndex - relativeIndex) / playbackSpeed;
	}


	int16_t processSample(int16_t sample) override {
		if (playbackSpeed > 1.f) {
			hpFilterFactor = 1.f / playbackSpeed;
			buffer[writeIndex] = hpFilter->doFilter(sample, hpFilterFactor, 0.f);
		}
		else {
			buffer[writeIndex] = sample;
		}

		int16_t readSample = linearInterpolation(buffer, bufferSize, floatIndex);

		float remaining = 0.f;
		if (playbackSpeed >= 1.f) {
			remaining = samplesRemaining();
		}
		else {
			remaining = samplesAhead();
		}

		if (remaining <= fadeSize + SWAP_MARGIN) {
			int16_t readSample2 = linearInterpolation(buffer, bufferSize, floatIndex2);
			float fade = ((remaining - SWAP_MARGIN) / fadeSize) * (M_PI / 2);
			readSample = readSample * sin(fade) + readSample2 * cos(fade);
			//			float ratio = (remaining - SWAP_MARGIN) / fadeSize;
			//			readSample = readSample * ratio + readSample2 * (1 - ratio);
			//			readSample = readSample * sqrt(ratio) + readSample2 * sqrt(1 - ratio);
		}

		// High pass filter to remove some of the beating sound from the grains
//		int hpfSample = hpFilter->doFilter(readSample, LOW_PASS_FILTER_FACTOR, 0.8f);
//		readSample -= hpfSample;

		writeIndex++;
		if (writeIndex >= bufferSize) {
			writeIndex -= bufferSize;
		}

		floatIndex += playbackSpeed;
		floatIndex2 += playbackSpeed;
		while (floatIndex >= bufferSize) {
			floatIndex -= bufferSize;
		}
		while (floatIndex2 >= bufferSize) {
			floatIndex2 -= bufferSize;
		}

		if (playbackSpeed >= 1.f) {
			remaining = samplesRemaining();
		}
		else {
			remaining = samplesAhead();
		}
		if (remaining <= SWAP_MARGIN) {
			float temp = floatIndex;
			floatIndex = floatIndex2;
			floatIndex2 = temp;
		}

		return readSample;
	}

};


#endif // #ifndef PITCH_SHIFT_H