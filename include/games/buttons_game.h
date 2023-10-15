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
		for (size_t i = 0; i < characters_.size(); ++i)
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


using LEDstates = std::vector<LedState>;
class ButtonsGameImpl;
class ButtonsGame: public GameInterface {
public:
	ButtonsGame();
	virtual ~ButtonsGame();

	void run() override;

	void onButtonPress(char btn);

	friend std::ostream& operator<<(std::ostream& os, const ButtonsGame& game);

protected:
	std::unique_ptr<ButtonsGameImpl> impl_;
};


}// namespace VTech