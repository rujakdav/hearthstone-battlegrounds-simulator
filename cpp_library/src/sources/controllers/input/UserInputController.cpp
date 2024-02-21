#include <iostream>
#include "controllers/input/UserInputController.h"

std::string UserInputController::getUserInput(const std::string &prompt) {
    std::string userInput;
    std::cout << prompt;
    std::getline(std::cin, userInput);  // Read a line of input from the user
    return userInput;
}
