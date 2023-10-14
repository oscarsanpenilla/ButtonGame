#include <gtest/gtest.h>
#include "games/buttons_game.h"
#include "errors.h"

using namespace VTech;

TEST(VTechGame, init) {
	ButtonsGame game;
	auto leds = game.getLights();
	for (const auto& state: leds)
		EXPECT_EQ(state, LedState::OFF) << "Expected all leds off";
}

TEST(VTechGame, onButtonPressValid) {
	ButtonsGame game;
	game.onButtonPress('A');
	game.onButtonPress('B');
	game.onButtonPress('C');
	try {
		game.onButtonPress('Z');
	}
	catch (GameErrorInput& e) {
		ASSERT_TRUE(true);
	}
	catch (...) {
		ASSERT_TRUE(false) << "Expected to catch an error input";
	}
}

TEST(VTechGame, singlePress) {
	{
		ButtonsGame game("ABC");
		game.onButtonPress('A');

		auto leds = game.getLights();
		ASSERT_EQ(leds[0], LedState::OFF);
		ASSERT_EQ(leds[1], LedState::OFF);
		ASSERT_EQ(leds[2], LedState::GREEN) << "LED3 expected to be GREEN since the position and value matches!"
	}
	{
		ButtonsGame game("ABC");
		game.onButtonPress('B');

		auto leds = game.getLights();
		ASSERT_EQ(leds[0], LedState::OFF);
		ASSERT_EQ(leds[1], LedState::OFF);
		ASSERT_EQ(leds[2], LedState::ORANGE) << "LED3 expected to be ORANGE since B is contained in the password";
	}
	{
		ButtonsGame game("AAA");
		game.onButtonPress('B');

		auto leds = game.getLights();
		ASSERT_EQ(leds[0], LedState::OFF);
		ASSERT_EQ(leds[1], LedState::OFF);
		ASSERT_EQ(leds[2], LedState::RED) << "LED3 expected to be RED since B is NOT in the password";
	}
}

TEST(VTechGame, doublePress) {
	{
		ButtonsGame game("ABC");
		game.onButtonPress('A');
		game.onButtonPress('B');

		auto leds = game.getLights();
		ASSERT_EQ(leds[0], LedState::OFF);
		ASSERT_EQ(leds[1], LedState::GREEN);
		ASSERT_EQ(leds[2], LedState::GREEN);
	}
	{
		ButtonsGame game("ABC");
		game.onButtonPress('A');
		game.onButtonPress('A');

		auto leds = game.getLights();
		ASSERT_EQ(leds[0], LedState::OFF);
		ASSERT_EQ(leds[1], LedState::GREEN);
		ASSERT_EQ(leds[2], LedState::ORANGE);
	}
	{
		ButtonsGame game("ABC");
		game.onButtonPress('C');
		game.onButtonPress('B');

		auto leds = game.getLights();
		ASSERT_EQ(leds[0], LedState::OFF);
		ASSERT_EQ(leds[1], LedState::ORANGE);
		ASSERT_EQ(leds[2], LedState::GREEN);
	}
	{
		ButtonsGame game("AAA");
		game.onButtonPress('C');
		game.onButtonPress('A');

		auto leds = game.getLights();
		ASSERT_EQ(leds[0], LedState::OFF);
		ASSERT_EQ(leds[1], LedState::RED);
		ASSERT_EQ(leds[2], LedState::GREEN);
	}
}

TEST(VTechGame, triplePress) {
	{
		ButtonsGame game("ABC");
		game.onButtonPress('A');
		game.onButtonPress('B');
		game.onButtonPress('B');

		auto leds = game.getLights();
		ASSERT_EQ(leds[0], LedState::GREEN);
		ASSERT_EQ(leds[1], LedState::GREEN);
		ASSERT_EQ(leds[2], LedState::ORANGE);
	}
	{
		ButtonsGame game("ABC");
		game.onButtonPress('A');
		game.onButtonPress('A');
		game.onButtonPress('A');

		auto leds = game.getLights();
		ASSERT_EQ(leds[0], LedState::GREEN);
		ASSERT_EQ(leds[1], LedState::ORANGE);
		ASSERT_EQ(leds[2], LedState::ORANGE);
	}
	{
		ButtonsGame game("ABC");
		game.onButtonPress('A');
		game.onButtonPress('B');
		game.onButtonPress('C');

		auto leds = game.getLights();
		ASSERT_EQ(leds[0], LedState::GREEN);
		ASSERT_EQ(leds[1], LedState::GREEN);
		ASSERT_EQ(leds[2], LedState::GREEN);
	}
	{
		ButtonsGame game("AAA");
		game.onButtonPress('C');
		game.onButtonPress('A');
		game.onButtonPress('B');

		auto leds = game.getLights();
		ASSERT_EQ(leds[0], LedState::RED);
		ASSERT_EQ(leds[1], LedState::GREEN);
		ASSERT_EQ(leds[2], LedState::RED);
	}
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

