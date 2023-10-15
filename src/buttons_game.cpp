#include <iostream>
#include <algorithm>
#include "games/buttons_game.h"
#include "games/impl/buttons_game_impl.h"
#include "errors.h"
#include "password_generator.h"
#include "hardware/light_controller.h"

namespace VT {

static std::ostream& operator << (std::ostream& os, const LedState& s);

ButtonsGame::ButtonsGame() : impl_(std::make_unique<ButtonsGameImpl>()) { }

ButtonsGame::~ButtonsGame() = default;

void ButtonsGame::run() { impl_->run(); }

void ButtonsGame::onButtonPress(char btn) { impl_->onButtonPress(btn); }

ButtonsGameImpl::ButtonsGameImpl(const std::string &secret_combination)
	: valid_chars_ (std::vector<char>{'A', 'B', 'C'})
	, light_controller_(std::make_unique<LightController>())
{
	if (!secret_combination.empty())
		secret_combination_ = secret_combination;
	else
		generatePass();

	reset();
}

ButtonsGameImpl::~ButtonsGameImpl() = default;

void ButtonsGameImpl::generatePass() {
	password_generator_ = std::make_unique<PasswordGenerator>(valid_chars_);
	secret_combination_ = password_generator_->generate();
}

LEDstates VT::ButtonsGameImpl::getLights() const {
	return light_controller_->getLights();
}

void ButtonsGameImpl::reset() {
	usr_won_ = false;
	curr_idx_ = 0;
	btn_history_ = "";
	combination_ = "";
	light_controller_->setLights({LedState::OFF, LedState::OFF, LedState::OFF});
}

void ButtonsGameImpl::run()
{
	std::cout << "  *************   GAME INSTRUCTIONS   ************  \n"
				 "  The  user has to guess a sequence of 3 buttons.\n"
	             "  The sequence can contain any combination\n"
				 "  e.g. BAC, CCB, AAA.\n"
	             "  The LEDs should always represent the result of the "
				 "  last 3 button presses.\n"
	             "   - LED 3 will always represent the most recent button pressed\n"
	             "   - LED 2 the one before that\n"
	             "   - LED 1 the one before that\n"
				 "  ***********************************************  \n";

	while (true) {
		reset();
		generatePass();

		printGameStatus();

		while (!usr_won_) {

		key_in:
			char btn_input;
			try {
				std::cout << "Press one of the Following letters on your keyboard A B C : ";
				std::cin >> btn_input;
				btn_input = toupper(btn_input);
				inputValidation(btn_input);
			} catch (GameErrorInput& ) {
				std::cout << "Invalid input... please try again.\n";
				goto key_in;
			}

			onButtonPress(btn_input);

			printGameStatus();
		}

		std::cout << "Congrats! You've found the secret code.\n";
		std::cout << "Starting new game...\n\n";
	}
}

void ButtonsGameImpl::printGameStatus() {
	std::cout << "History: " << btn_history_ << "\n";
	LEDstates leds = light_controller_->getLights();
	for (size_t i = 0; i < leds.size(); ++i)
		std::cout << "LED" << i + 1 << ": " << leds.at(i) << "\n";
}

void ButtonsGameImpl::onButtonPress(char btn)
{
	auto checkGuess = [this](char usr_guess, size_t pos) {
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
	const size_t pass_size = secret_combination_.size();
	curr_idx_ = (curr_idx_ + 1) % pass_size;
	if (combination_.size() >= pass_size) combination_.clear();
	combination_ += btn;
	btn_history_ += btn;
	usr_won_ = passValidation();

}

void ButtonsGameImpl::setLights(const LEDstates &states) {
	light_controller_->setLights(states);
}

void ButtonsGameImpl::inputValidation(char input) {
	bool found = std::find(valid_chars_.begin(), valid_chars_.end(), input) != valid_chars_.end();
	if (!found)
		throw GameErrorInput("The pressed button isn't valid");
}

bool ButtonsGameImpl::passValidation() const {
	bool won = true;
	for (const auto& s: getLights()) { won &= s == LedState::GREEN; }
	return won;
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

}//namespace VT
