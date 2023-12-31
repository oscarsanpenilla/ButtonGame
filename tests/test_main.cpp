#include <gtest/gtest.h>
#include "games/impl/buttons_game_impl.h"
#include "errors.h"

using namespace VT;

TEST(ButtonsGame, init) {
	ButtonsGameImpl game;
	auto leds = game.getLights();
	for (const auto& state: leds)
		EXPECT_EQ(state, LedState::OFF) << "Expected all leds off";
}

TEST(ButtonsGame, onButtonPressValid) {
	ButtonsGameImpl game;
	game.onButtonPress('A');
	game.onButtonPress('B');
	game.onButtonPress('C');
	try {
		game.onButtonPress('Z');
	}
	catch (GameErrorInput& ) {
		ASSERT_TRUE(true);
	}
	catch (...) {
		ASSERT_TRUE(false) << "Expected to catch an error input";
	}
}

TEST(ButtonsGame, singlePress) {
	{
		ButtonsGameImpl game("ABC");
		game.onButtonPress('A');

		auto leds = game.getLights();
		ASSERT_EQ(leds[0], LedState::OFF);
		ASSERT_EQ(leds[1], LedState::OFF);
		ASSERT_EQ(leds[2], LedState::GREEN) << "LED3 expected to be GREEN since the position and value matches!";
	}
	{
		ButtonsGameImpl game("ABC");
		game.onButtonPress('B');

		auto leds = game.getLights();
		ASSERT_EQ(leds[0], LedState::OFF);
		ASSERT_EQ(leds[1], LedState::OFF);
		ASSERT_EQ(leds[2], LedState::ORANGE) << "LED3 expected to be ORANGE since B is contained in the password";
	}
	{
		ButtonsGameImpl game("AAA");
		game.onButtonPress('B');

		auto leds = game.getLights();
		ASSERT_EQ(leds[0], LedState::OFF);
		ASSERT_EQ(leds[1], LedState::OFF);
		ASSERT_EQ(leds[2], LedState::RED) << "LED3 expected to be RED since B is NOT in the password";
	}
}

TEST(ButtonsGame, doublePress) {
	{
		ButtonsGameImpl game("ABC");
		game.onButtonPress('A');
		game.onButtonPress('B');

		auto leds = game.getLights();
		ASSERT_EQ(leds[0], LedState::OFF);
		ASSERT_EQ(leds[1], LedState::GREEN);
		ASSERT_EQ(leds[2], LedState::GREEN);
	}
	{
		ButtonsGameImpl game("ABC");
		game.onButtonPress('A');
		game.onButtonPress('A');

		auto leds = game.getLights();
		ASSERT_EQ(leds[0], LedState::OFF);
		ASSERT_EQ(leds[1], LedState::GREEN);
		ASSERT_EQ(leds[2], LedState::ORANGE);
	}
	{
		ButtonsGameImpl game("ABC");
		game.onButtonPress('C');
		game.onButtonPress('B');

		auto leds = game.getLights();
		ASSERT_EQ(leds[0], LedState::OFF);
		ASSERT_EQ(leds[1], LedState::ORANGE);
		ASSERT_EQ(leds[2], LedState::GREEN);
	}
	{
		ButtonsGameImpl game("AAA");
		game.onButtonPress('C');
		game.onButtonPress('A');

		auto leds = game.getLights();
		ASSERT_EQ(leds[0], LedState::OFF);
		ASSERT_EQ(leds[1], LedState::RED);
		ASSERT_EQ(leds[2], LedState::GREEN);
	}
}

TEST(ButtonsGame, triplePress) {
	{
		ButtonsGameImpl game("ABC");
		game.onButtonPress('A');
		game.onButtonPress('B');
		game.onButtonPress('B');

		auto leds = game.getLights();
		ASSERT_EQ(leds[0], LedState::GREEN);
		ASSERT_EQ(leds[1], LedState::GREEN);
		ASSERT_EQ(leds[2], LedState::ORANGE);
	}
	{
		ButtonsGameImpl game("ABC");
		game.onButtonPress('A');
		game.onButtonPress('A');
		game.onButtonPress('A');

		auto leds = game.getLights();
		ASSERT_EQ(leds[0], LedState::GREEN);
		ASSERT_EQ(leds[1], LedState::ORANGE);
		ASSERT_EQ(leds[2], LedState::ORANGE);
	}
	{
		ButtonsGameImpl game("ABC");
		game.onButtonPress('A');
		game.onButtonPress('B');
		game.onButtonPress('C');

		auto leds = game.getLights();
		ASSERT_EQ(leds[0], LedState::GREEN);
		ASSERT_EQ(leds[1], LedState::GREEN);
		ASSERT_EQ(leds[2], LedState::GREEN);
	}
	{
		ButtonsGameImpl game("AAA");
		game.onButtonPress('C');
		game.onButtonPress('A');
		game.onButtonPress('B');

		auto leds = game.getLights();
		ASSERT_EQ(leds[0], LedState::RED);
		ASSERT_EQ(leds[1], LedState::GREEN);
		ASSERT_EQ(leds[2], LedState::RED);
	}
}

TEST(ButtonsGame, treeGreenWin) {
	ButtonsGameImpl game("AAA");
	game.onButtonPress('A');
	game.onButtonPress('A');
	game.onButtonPress('A');
	ASSERT_TRUE(game.usr_won_) << "User supposed to won here!";

	game.reset();

	game.onButtonPress('B');
	game.onButtonPress('A');
	game.onButtonPress('A');
	ASSERT_FALSE(game.usr_won_);
	game.onButtonPress('A');
	ASSERT_TRUE(game.usr_won_) << "User supposed to won after 3 green lights!";
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

