#pragma once
#include "common.h"

namespace VT {

/**
 * @class LightController
 * @brief This class emulates real hardware control of LED lights.
 */
class LightController {
public:
    /**
     * @brief Default constructor for LightController.
     */
    LightController();

    /**
     * @brief Get the current state of the LED lights.
     * @return The current LED state.
     */
    LEDstates getLights() const;

    /**
     * @brief Set the state of the LED lights.
     * @param states The new LED state to set.
     */
    void setLights(const LEDstates& states);

protected:
	LEDstates led_states_;
};

}//namespace VT
