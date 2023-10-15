#include "hardware/light_controller.h"

namespace VT {

LightController::LightController()
	: led_states_({LedState::OFF, LedState::OFF, LedState::OFF})
{

}

LEDstates LightController::getLights() const {
	return led_states_;
}

void LightController::setLights(const LEDstates &states) {
	led_states_ = states;
}

}//namespace VT
