#pragma once

#include <stdexcept>

namespace VT {

struct GameError : public std::runtime_error {
	explicit GameError(const std::string &message) : runtime_error(message) {}
};

struct GameErrorInput : public GameError {
	explicit GameErrorInput(const std::string &message) : GameError(message) {}
};

}//namespace VT