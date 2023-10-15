#pragma once
#include <string>
#include <vector>

namespace VT {

struct GameInterface {
	virtual void run () = 0;
};

class ButtonsGameImpl;
class ButtonsGame: public GameInterface {
public:
	ButtonsGame();
	virtual ~ButtonsGame();

	void run() override;

	void onButtonPress(char btn);

protected:
	std::unique_ptr<ButtonsGameImpl> impl_;
};

}// namespace VT