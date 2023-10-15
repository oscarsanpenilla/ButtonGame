#pragma once
#include <string>
#include <vector>
#include <memory>

namespace VT {

/**
 * @brief We can use this interface to define a common interface between between other games.
 * One of the benefits of using and interface is that allows us to swap games at runtime when necessary.
 */
struct GameInterface {
	virtual void run () = 0;
};

class ButtonsGameImpl;
class ButtonsGame: public GameInterface {
public:
	/**
	 * @brief Constructs a ButtonsGame object.
	 */
	ButtonsGame();
	virtual ~ButtonsGame();

	/**
	 * @brief Runs the buttons game.
	 * This function starts the game and handles user input.
	 * @details This is a blocking function.
	 */
	void run() override;

	/**
	 * @brief Handles button press events.
	 * @param btn The button that was pressed.
	 */
	void onButtonPress(char btn);

protected:
	std::unique_ptr<ButtonsGameImpl> impl_;
};

}// namespace VT