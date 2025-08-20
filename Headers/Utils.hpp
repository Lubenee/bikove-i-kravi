#if !defined(UTILS_H)
#define UTILS_H

#include "Termcolor/Termcolor.hpp"

#include <string>
#include <algorithm>
#include <cctype>  
#include <iostream>
#include <random>
#include <chrono>
#include <stdexcept>

using namespace std::chrono;

// Checks if a string includes the passed character
bool includes(std::string secret, char c) {
    for(int i = 0; i < secret.size(); ++i)
        if (secret[i] == c)
            return true;
    return false;
}

// Checks if all characters are unique
bool all_unique(std::string str) {
    std::sort(str.begin(), str.end());
    return std::adjacent_find(str.begin(), str.end()) == str.end();
}

// Checks if the user input string is valid for the bulls-and-cows rules,
// e.g. has ${game_difficulty} digits and they don't repeat
bool is_num_valid(std::string input, int n) {
    if (input.size() != n || !std::all_of(input.begin(), input.end(), ::isdigit)) {
        std::cout << "Invalid input. Must be exactly " << n << " digits.\n\n";
        return false;
    }
    if (!all_unique(input)) {
        std::cout << "All digits must be unique.\n\n";
        return false;
    }
    return true;
}

// Returns the game duration in seconds
int get_game_duration(std::chrono::time_point<std::chrono::steady_clock> start,
                      std::chrono::time_point<std::chrono::steady_clock> end) {
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    return static_cast<int>(duration.count());
}

#endif // UTILS_H
