#pragma once
#include <vector>
#include <string>

namespace VT {

class PasswordGenerator {
public:
	explicit PasswordGenerator(const std::vector<char>& characters);

	std::string generate() const;

protected:
	const std::vector<char> characters_;
};

}//namespace VT
