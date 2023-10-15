#pragma once
#include <vector>

namespace VT {

enum class LedState {
	OFF,
	GREEN,
	RED,
	ORANGE
};
using LEDstates = std::vector<LedState>;

}//namespace VT
