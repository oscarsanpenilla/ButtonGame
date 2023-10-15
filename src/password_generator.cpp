#include <ctime>
#include "password_generator.h"

namespace VT {

PasswordGenerator::PasswordGenerator(const std::vector<char> &characters) : characters_(characters)
{
	srand(time(0));
}

std::string PasswordGenerator::generate() const {
	std::string password;
	for (size_t i = 0; i < characters_.size(); ++i)
		password += characters_.at(rand() % characters_.size());

	return password;
}

}//namespace VT
