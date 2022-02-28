#include "CjFilter.h"


int16_t CjFilter::doFilter(int16_t sampleIn, float cut, float res) {
    float input = (float)sampleIn / 32768.f * 5.f;

    // Normalize the Resonance Input to 0-1.f
    res *= 3.6;
    // Damp Resonanced on hgiher frequencies
    if (cut > 0.5f) {
        damp = 1.f + (0.5f - cut);
    }
    else {
        damp = 1.f;
    }
    cut *= cut;
    // Damp Resonance on higher frequencies
    res = (1.f - (cut * 0.64f)) * res;

    if (counter >= 8) {
        counter = 0;
    }
    output = input * .2f;
    for (int i = 0; i < 4; i++) {
        // Resonance is only fed back into the first filter
        if (i == 0) {
            output = (output * cut) + (feedback[i][counter + 7] * (1.f - cut)) + damp * feedback[3][counter + 6] * res * -1.f * cut;
            feedback[i][counter] = output;
            feedback[i][counter + 8] = output;
            filterOut[i] = output * 5.f;
        }
        else {
            output = (output * cut) + (feedback[i][counter + 7] * (1.f - cut));
            feedback[i][counter] = output;
            feedback[i][counter + 8] = output;
            filterOut[i] = output * 5.f;
        }
    }
    counter++;
    return (int16_t)(*filterOut / 5.f * 32768.f);
}
