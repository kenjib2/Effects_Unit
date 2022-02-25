#include <string>
#include <vector>
#include "src/patch/EffectSubclasses.h"


class EffectFactory {
public:
	static std::vector<std::string> getSlot1EffectList();
	static std::vector<std::string> getSlot2EffectList();
	static Effect* createEffect(std::string effectName);
};
