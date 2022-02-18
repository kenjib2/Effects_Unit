class Distortion {
public:
    float gain; // Range from 0.0 to 10.0
    float level; // Range from 0.0 to 1.0

    int16_t processSample(int16_t sample) {
        float saturatedSample = (float)sample / 32768.0 * gain;
        saturatedSample = (2.f / PI) * atan(saturatedSample);
        return (int)(saturatedSample * 32768 * level);
    }
};
