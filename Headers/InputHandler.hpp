#if !defined(INPUT_HANDLER_H)
#define INPUT_HANDLER_H

#include "Utils.hpp"

#include <string>
#include <iostream>
#include <limits>
#include <algorithm>

class InputHandler {
public:
    static bool ask_yes_no(const std::string& prompt) {
        std::string input;
        do {
            std::cout << prompt << " (y/n): ";
            std::getline(std::cin, input);

            std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        } while (input != "y" && input != "n");

        return input == "y";
    }

    static std::string get_n_digit_number(int n) {
        std::string input;
        do {
            std::cout << termcolor::yellow << "\nEnter a " << n << "-digit number: ";
            std::cin >> input;
        } while (!is_num_valid(input, n));
        return input;
    }
};

#endif // INPUT_HANDLER_H
