#pragma once
#include <string>
#include <memory>
#include "common.h"
#include "games/buttons_game.h"

namespace VT {

class LightController;
class GeneratorAlgorithm;

/**
 * @brief The ButtonsGameImpl class hides the implementation details of the actual ButtonsGame class.
 *
 * This class handles the implementation of the logic and functionality of a buttons game, where the user needs to guess
 * a secret combination.
 */
class ButtonsGameImpl {
public:
    /**
     * @brief Constructs a ButtonsGameImpl object with an optional secret combination.
     * @param secret_combination The secret combination that the user needs to guess.
     */
    explicit ButtonsGameImpl(const std::string& secret_combination = "");

    /**
     * @brief Destroys the ButtonsGameImpl object.
     */
    ~ButtonsGameImpl();

    /**
     * @brief Runs the buttons game.
     * This function starts the game and handles user input.
     */
    void run();

    /**
     * @brief Handles button press events.
     * @param btn The button that was pressed.
     */
    void onButtonPress(char btn);

    /**
     * @brief Gets the current state of the LED lights.
     * @return The LEDstates object representing the current state of the lights.
     */
    LEDstates getLights() const;

    /**
     * @brief Sets the state of the LED lights.
     * @param states The LEDstates object representing the desired state of the lights.
     */
    void setLights(const LEDstates& states);

    /**
     * @brief Validates user input.
     * @param input The input to be validated.
     */
    void inputValidation(char input);

    /**
     * @brief Generates a password.
     */
    void generatePass();

    /**
     * @brief Performs password validation.
     * @return True if the password is valid, false otherwise.
     */
    bool passValidation() const;

    /**
     * @brief Resets the game to its initial state.
     */
    void reset();

    /**
     * @brief Prints the current game status.
     */
    void printGameStatus();

	std::string combination_;
	std::string secret_combination_;
	std::string btn_history_;
	size_t curr_idx_ = 0;
	std::vector<char> valid_chars_;
	std::unique_ptr<GeneratorAlgorithm> password_generator_;
	std::unique_ptr<LightController> light_controller_;
	bool usr_won_ = false;
};

}//namespace VT

