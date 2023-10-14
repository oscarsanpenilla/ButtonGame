#include <iostream>
#include "games/buttons_game.h"
#include "errors.h"

VTech::ButtonsGame::ButtonsGame(const std::string &secret_combination)
	: valid_chars_ (std::vector<char>{'A', 'B', 'C'})
{
	setLights({LedState::OFF, LedState::OFF, LedState::OFF});
}

void VTech::ButtonsGame::run() {
	while (true) {

		generatePass();

		// Print game status here

		while (!passValidation()) {

			std::cout << "Press one of the Following letters on your keyboard A B C : ";
			char btn_input;
			std::cin >> btn_input;
			inputValidation(btn_input);

			onButtonPress(btn_input);

			// Print game status here
		}

		std::cout << "Congrats! You've found the secret code.\n";
		std::cout << "Starting new game...\n";
	}
}

void VTech::ButtonsGame::onButtonPress(char btn) {
	auto checkGuess = [this](char usr_guess, int pos) {
		if (usr_guess == secret_combination_.at(pos))
			return LedState::GREEN;

		// Check if letter is part of the password
		if (secret_combination_.find(usr_guess) != std::string::npos)
			return LedState::ORANGE;

		return LedState::RED;
	};

//	inputValidation(btn);
	LEDstates prev_state = getLights();

	// Shift led colors
	LEDstates new_state = {
			prev_state.at(1),
			prev_state.at(2),
			checkGuess(btn, curr_idx_)
	};

	setLights(new_state);
}

void VTech::ButtonsGame::generatePass() {
	password_generator_ = std::make_unique<PasswordGenerator>(valid_chars_);
	secret_combination_ = password_generator_->generate();
}

VTech::ButtonsGame::LEDstates VTech::ButtonsGame::getLights() {
	return led_states_;
}

void VTech::ButtonsGame::setLights(const VTech::ButtonsGame::LEDstates &states) {
	led_states_ = states;
}

void VTech::ButtonsGame::inputValidation(char input) {
	bool found = std::find(valid_chars_.begin(), valid_chars_.end(), input) != valid_chars_.end();
	if (!found)
		throw GameErrorInput("The pressed button isn't valid");
}

bool VTech::ButtonsGame::passValidation() {
	return secret_combination_ == combination_;
}

std::ostream &VTech::operator<<(std::ostream &os, const VTech::ButtonsGame &game) {
	os << "History: " << game.combination_ << "\n";
//	os << "LEDs: " << game.led_states_[0] << "\n";
	return os;
}

VTech::ButtonsGame::~ButtonsGame() {

}


