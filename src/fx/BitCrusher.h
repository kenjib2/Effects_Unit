class BitCrusher {
private:
	int lastDownsample;
	float downsampleAccrued;

public:
	float bits = 0.f;
	float downsample = 0.f;
	//    bits 14.f, downsample 16.f <--- interesting sounds to try out

	BitCrusher() {
		lastDownsample = 0;
		downsampleAccrued = 0;
	}

	int16_t processSample(int16_t sample) {
		int crushedSample = sample;

		if (downsample > 0.00001f) {
			downsampleAccrued += 1.f;
			if (downsampleAccrued > downsample) {
				downsampleAccrued -= downsample;
				lastDownsample = sample;
			}
			else {
				crushedSample = lastDownsample;
			}
		}

		if (bits > 0.00001f) {
			float floatSample = crushedSample + 32768;
			float factor = powf(2.f, 16.f - bits);
			floatSample = floatSample - (fmod(crushedSample, factor));
			crushedSample = (int)(floatSample - 32768);
		}

		return crushedSample;
	}
};
