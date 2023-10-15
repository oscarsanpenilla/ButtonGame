#pragma once
#include <vector>
#include <string>

namespace VT {


/**
 * @brief We can use this interface to swap the algorithm at runtime if required.
 */
struct GeneratorAlgorithm {
	virtual std::string generate() = 0;
};

/**
 * @brief The PasswordGenerator class is responsible for generating passwords based on a given set of characters.
 */
class PasswordGenerator : public GeneratorAlgorithm{
public:
    /**
     * @brief Constructs a PasswordGenerator object with a specified set of characters.
     * @param characters The vector of characters that can be used to generate passwords.
     */
    explicit PasswordGenerator(const std::vector<char>& characters);

    /**
     * @brief Generates a password using the specified set of characters.
     * @return The generated password as a string.
     */
    std::string generate() override;

protected:
	const std::vector<char> characters_;
};

}//namespace VT
