#pragma once
#include <string>
#include <memory>
#include "games/buttons_game.h"

namespace VTech {

class ButtonsGameImpl {
public:
	explicit ButtonsGameImpl(const std::string& secret_combination="");

	void run();
	void onButtonPress(char btn);

	LEDstates getLights();
	void setLights(const LEDstates& states);
	void inputValidation(char input);
	void generatePass();
	bool passValidation();
	void reset();
	void printGameStatus();

	std::string combination_;
	std::string secret_combination_;
	std::string btn_history_;
	int curr_idx_ = 0;
	LEDstates led_states_;
	std::vector<char> valid_chars_;
	std::unique_ptr<PasswordGenerator> password_generator_;
};

}//namespace VTech

