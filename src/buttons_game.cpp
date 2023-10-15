#include <iostream>
#include "games/buttons_game.h"
#include "games/impl/buttons_game_impl.h"
#include "errors.h"

namespace VTech {

static std::ostream& operator << (std::ostream& os, const LedState& s);

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

	reset();
}

void ButtonsGameImpl::generatePass() {
	password_generator_ = std::make_unique<PasswordGenerator>(valid_chars_);
	secret_combination_ = password_generator_->generate();
}

LEDstates VTech::ButtonsGameImpl::getLights() {
	return led_states_;
}

void ButtonsGameImpl::reset() {
	curr_idx_ = 0;
	btn_history_ = "";
	combination_ = "";
	led_states_ = {LedState::OFF, LedState::OFF, LedState::OFF};
}

void ButtonsGameImpl::run()
{
	while (true) {
		reset();
		generatePass();

		printGameStatus();

		while (!passValidation()) {

			std::cout << "Press one of the Following letters on your keyboard A B C : ";
			char btn_input;
			std::cin >> btn_input;
			inputValidation(btn_input);

			onButtonPress(btn_input);

			printGameStatus();
		}

		std::cout << "Congrats! You've found the secret code.\n";
		std::cout << "Starting new game...\n\n";
	}
}

void ButtonsGameImpl::printGameStatus() {
	std::cout << "History: " << btn_history_ << "\n";
	std::cout << "Current: " << combination_ << "\n";
	for (size_t i = 0; i < led_states_.size(); ++i)
		std::cout << "LED" << i + 1 << ": " << led_states_.at(i) << "\n";
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
	if (combination_.size() >= 3) combination_.clear();
	combination_ += btn;
	btn_history_ += btn;

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

std::ostream &operator<<(std::ostream &os, const LedState &s) {
	switch (s) {
		case LedState::OFF: os << "OFF"; break;
		case LedState::GREEN: os << "GREEN"; break;
		case LedState::RED: os << "RED"; break;
		case LedState::ORANGE: os << "ORANGE"; break;
	}
	return os;
}

}//namespace VTech
