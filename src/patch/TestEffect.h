#ifndef TEST_EFFECT_H
#define TEST_EFFECT_H


#include "../../patch.h"
#include "../fx/PitchShift.h"
//#include "../granular/GranularBuffer.h"


class TestEffect : public Effect {
public:
    TestEffect();
    ~TestEffect() override;
    void processEffect(int16_t* effectBuffer) override;

private:
//    GrainPool* grainPool;
//    GranularBuffer* granularBuffer;
    PitchShift* pitchShift;
};


#endif	// #ifndef TEST_EFFECT_H