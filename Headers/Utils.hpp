#if !defined(UTILS_H)
#define UTILS_H

#include "Termcolor/Termcolor.hpp"

#include <string>
#include <algorithm>
#include <cctype>  
#include <iostream>
#include <random>
#include <chrono>

using namespace std::chrono;


bool includes(std::string secret, char c) {
    for(int i = 0; i < secret.size(); ++i) {
        if (secret[i] == c) {
            return true;
        }
    }
    return false;
}

bool all_unique(std::string str) {
    std::sort(str.begin(), str.end());
    return std::adjacent_find(str.begin(), str.end()) == str.end();
}

bool is_num_valid(std::string input) {
    
    if (input.size() != 4 || !std::all_of(input.begin(), input.end(), ::isdigit)) {
        std::cout << "Invalid input. Must be exactly 4 digits.\n\n";
        return false;
    }
    if (!all_unique(input)) {
        std::cout << "All digits must be unique.\n\n";
        return false;
    }
    return true;
}

bool check_number(std::string num) {
    for (int i = 0; i < num.size(); ++i){
        char c = num[i];
        for(int j = i + 1; j < num.size(); ++j){
            if (c == num[j]) return false;
        }
    }
    return true;
}

std::string get_four_digit_user_input() {

    std::string input;
    do {
        std::cout << termcolor::yellow << "\nEnter a 4-digit number: ";
        std::cin >> input;
    } while (!is_num_valid(input));
    return input;
}

#include <chrono>

int get_game_duration(std::chrono::time_point<std::chrono::steady_clock> start,
                      std::chrono::time_point<std::chrono::steady_clock> end) {
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    return static_cast<int>(duration.count());
}

std::string get_random_four_digit_number() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1000, 9999);
    int secretNum = 0;

    std::string secret = "";

    do {
        secretNum = dist(gen);
        secret = std::to_string(secretNum);
    } while (!check_number(secret));
    return secret;
}

#endif // UTILS_H
