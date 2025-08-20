#if !defined(DIFFICULTY_SELECTOR_H)
#define DIFFICULTY_SELECTOR_H

#include <string>
#include <iostream>
#include <algorithm>
#include "Termcolor/Termcolor.hpp"

class DifficultySelector {
public:
    enum Difficulty {
        Easy = 4,
        Medium = 5,
        Hard = 6
    };

    static Difficulty select() {
        while (true) {
            std::cout << termcolor::cyan
                      << "Select game difficulty:\n"
                      << "Easy (4 digits), Medium (5 digits), Hard (6 digits).\n"
                      << "Type 'easy', 'medium', or 'hard': ";

            std::string input;
            std::getline(std::cin, input);

            std::transform(input.begin(), input.end(), input.begin(), ::tolower);

            if (input == "easy") return Difficulty::Easy;
            if (input == "medium") return Difficulty::Medium;
            if (input == "hard") return Difficulty::Hard;

            std::cout << "Invalid input. Please try again.\n\n";
        }
    }

    static int max_attempts(Difficulty diff) {
        switch (diff) {
            case Easy:   return 7;
            case Medium: return 10;
            case Hard:   return 13;
            default:     return 8;
        }
    }
};

#endif // DIFFICULTY_SELECTOR_H
