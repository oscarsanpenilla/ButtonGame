#pragma once

#include <string>
#include <vector>

namespace VTech {

struct GameInterface {
	virtual void start () = 0;
	virtual void end() = 0;
};

enum class LedState {
	OFF,
	GREEN,
	RED,
	ORANGE
};

class ButtonsGame: public GameInterface {
public:
	explicit ButtonsGame(const std::string& secret_combination="");

	void start() override;

	void end() override;

	std::vector<LedState> getLights();

	void onButtonPress(char letter);

protected:
	std::string combination_;
	std::string secret_combination_;
};


}// namespace VTech