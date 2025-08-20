#if !defined(RENDERER_H)
#define RENDERER_H

#include <iostream>
#include <string>
#include "Termcolor/Termcolor.hpp"

class Renderer {
public:
    void high_score(int score) const {
        if (score > 0) {
            std::cout << termcolor::reset << "Current high score: " 
                      << score << " seconds.\n\n";
        }
    }

    void bulls_and_cows(int bulls, int cows) const {
        std::cout << termcolor::red << "BULLS: " << bulls << ", "
                  << termcolor::green << "COWS: " << cows << ".\n"
                  << termcolor::reset;
    }

    void win_message(int attempts, int duration) const {
        std::cout << termcolor::bright_blue 
                  << "You won! It took you " << attempts 
                  << " attempts and " << duration << " seconds.\n\n";
    }

    void loss_message(int max_attempts, int duration, const std::string& secret) const {
        std::cout << termcolor::magenta 
                  << "You lost! It took you more than " << max_attempts-1 
                  << " attempts. Elapsed time: " << duration << " seconds.\n";
        std::cout << "Your number was: " << secret << ".\n\n";
    }

    void message(const std::string& msg) const {
        std::cout << msg;
    }
};

#endif // RENDERER_H
