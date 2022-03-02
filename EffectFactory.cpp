#include "EffectFactory.h"


std::vector<std::string> EffectFactory::getSlot1EffectList() {
	return {
		"Bypass"
    , "Bloom Reverb"
		, "Lost In Space"
    , "Repeater"
    , "Rhythmic Delay"
		, "Subtractive Synth"
		, "Temporal Collapse"
		, "The Full Rack"
	};
}


std::vector<std::string> EffectFactory::getSlot2EffectList() {
	return {
		"Bypass"
    , "Bloom Reverb"
		, "Lost In Space"
    , "Repeater"
    , "Rhythmic Delay"
		, "Temporal Collapse"
		, "The Full Rack"
	};
}


Effect* EffectFactory::createEffect(std::string effectName) {
	if (effectName.compare("Bypass") == 0) {
		return new BypassEffect();
	}
  else if (effectName.compare("Bloom Reverb") == 0) {
    return new BloomReverbEffect();
  }
	else if (effectName.compare("Lost In Space") == 0) {
		return new LostInSpaceEffect();
	}
  else if (effectName.compare("Repeater") == 0) {
    return new RepeaterEffect();
  }
  else if (effectName.compare("Rhythmic Delay") == 0) {
    return new RhythmicDelayEffect();
  }
	else if (effectName.compare("Subtractive Synth") == 0) {
		return new SubtractiveSynthEffect();
	}
	else if (effectName.compare("Temporal Collapse") == 0) {
		return new TemporalCollapseEffect();
	}
	else if (effectName.compare("The Full Rack") == 0) {
		return new TheFullRackEffect();
	}

	return new BypassEffect();
}
