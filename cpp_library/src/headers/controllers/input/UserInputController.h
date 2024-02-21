#pragma once


#include <string>

/**
 * @brief The UserInputController class
 * This class is used to get user input
 */
class UserInputController {
public:
    /**
     * @brief Returns the user input
     * @param prompt
     * @return std::string
     */
    std::string getUserInput(const std::string &prompt);
};


