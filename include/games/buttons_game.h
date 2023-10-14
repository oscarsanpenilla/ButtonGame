#pragma once

#include <string>
#include <vector>

namespace VTech {

struct GameInterface {
	virtual void run () = 0;
};

enum class LedState {
	OFF,
	GREEN,
	RED,
	ORANGE
};

class PasswordGenerator {
public:
	explicit PasswordGenerator(const std::vector<char>& characters) : characters_(characters)
	{
		srand(time(0));
	}

	std::string generate() const {
		std::string password;
		for (int i = 0; i < characters_.size(); ++i)
			password += characters_.at(rand() % characters_.size());

		return password;
	}
protected:
	const std::vector<char> characters_;
};

class ButtonsGame;
struct ButtonsGamePrinter {
	static std::string print(const ButtonsGame& game);
};


class ButtonsGame: public GameInterface {
public:
	using LEDstates = std::vector<LedState>;

	explicit ButtonsGame(const std::string& secret_combination="");
	virtual ~ButtonsGame();

	void run() override;

	void onButtonPress(char btn);

	friend std::ostream& operator<<(std::ostream& os, const ButtonsGame& game);

protected:
	// TODO: use impl idiom to hide implementatin details
	void generatePass();
	LEDstates getLights();
	void setLights(const LEDstates& states);
	void inputValidation(char input);
	bool passValidation();

	std::string combination_;
	std::string secret_combination_;
	int curr_idx_ = 0;
	LEDstates led_states_;
	std::vector<char> valid_chars_;
	std::unique_ptr<PasswordGenerator> password_generator_;
};


}// namespace VTech