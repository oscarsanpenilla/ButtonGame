#pragma once
#include "common.h"

namespace VT {

class LightController {
public:
	LightController();

	LEDstates getLights() const;
	void setLights(const LEDstates& states);

protected:
	LEDstates led_states_;
};

}//namespace VT
