#include <iostream>
#include "games/buttons_game.h"
#include "games/impl/buttons_game_impl.h"
#include "errors.h"

namespace VTech {

ButtonsGame::ButtonsGame() : impl_(std::make_unique<ButtonsGameImpl>()) { }

ButtonsGame::~ButtonsGame() = default;

void ButtonsGame::run() { impl_->run(); }

void ButtonsGame::onButtonPress(char btn) { impl_->onButtonPress(btn); }

ButtonsGameImpl::ButtonsGameImpl(const std::string &secret_combination)
		: valid_chars_ (std::vector<char>{'A', 'B', 'C'})
{
	if (!secret_combination.empty())
		secret_combination_ = secret_combination;
	else
		generatePass();

	setLights({LedState::OFF, LedState::OFF, LedState::OFF});
}

void ButtonsGameImpl::generatePass() {
	password_generator_ = std::make_unique<PasswordGenerator>(valid_chars_);
	secret_combination_ = password_generator_->generate();
}

LEDstates VTech::ButtonsGameImpl::getLights() {
	return led_states_;
}

void ButtonsGameImpl::run()
{
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

void ButtonsGameImpl::onButtonPress(char btn)
{
	auto checkGuess = [this](char usr_guess, int pos) {
		if (usr_guess == secret_combination_.at(pos))
			return LedState::GREEN;

		// Check if letter is part of the password
		if (secret_combination_.find(usr_guess) != std::string::npos)
			return LedState::ORANGE;

		return LedState::RED;
	};

	inputValidation(btn);
	LEDstates prev_state = getLights();

	// Shift led colors
	LEDstates new_state = {
			prev_state.at(1),
			prev_state.at(2),
			checkGuess(btn, curr_idx_)
	};

	setLights(new_state);

	// Update curr_idx and ensure it's within the range
	curr_idx_ = (curr_idx_ + 1) % 3;
}

void ButtonsGameImpl::setLights(const LEDstates &states) {
	led_states_ = states;
}

void ButtonsGameImpl::inputValidation(char input) {
	bool found = std::find(valid_chars_.begin(), valid_chars_.end(), input) != valid_chars_.end();
	if (!found)
		throw GameErrorInput("The pressed button isn't valid");
}

bool ButtonsGameImpl::passValidation() {
	return secret_combination_ == combination_;
}

// TODO: implement game console output
//	std::ostream &VTech::operator<<(std::ostream &os, const VTech::ButtonsGame &game) {
//		os << "History: " << game.combination_ << "\n";
////	os << "LEDs: " << game.led_states_[0] << "\n";
//		return os;
//	}

}//namespace VTech
