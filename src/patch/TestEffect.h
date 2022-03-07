#ifndef TEST_EFFECT_H
#define TEST_EFFECT_H


#include "../../patch.h"
#include "../fx/Modulation.h"


class TestEffect : public Effect {
public:
    TestEffect();
    ~TestEffect() override;
    void processEffect(int16_t* effectBuffer) override;

private:
};


#endif	// #ifndef TEST_EFFECT_H