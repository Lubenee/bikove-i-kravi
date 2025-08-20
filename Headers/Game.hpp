#if !defined(GAME_H)
#define GAME_H

#include "Utils.hpp"
#include "FileHandler/FileHandler.hpp"
#include "Termcolor/Termcolor.hpp"

#include <string>
#include <chrono>

using namespace std::chrono;

class Game
{
public:
    Game();
    void run();

    ~Game() = default;

private:
    void print_cows_and_bulls(std::string input);
    void play_again();
    void reset_game();

private:
    bool game_over;
    int high_score;
    std::string secret;
    int attempts;
    bool pause;

};

Game::Game(): game_over(false), high_score(0), secret(""), attempts(0), pause(false)
{
    secret = get_random_four_digit_number();
    high_score = fh::read_high_score();

    if (high_score > 0) 
        std::cout << "Current high score: " << high_score << " seconds." << "\n\n";
}

void Game::print_cows_and_bulls(std::string input) {
    int bulls = 0, cows = 0;
    for (int i = 0; i < this->secret.size(); ++i) {
        if (input[i] == secret[i]) {
            bulls++;
        }
        else if (includes(secret, input[i])){
            cows++;
        }
    }
    std::cout << termcolor::red << "BULLS: " << bulls << ", ";
    std::cout << termcolor::green << " COWS: " << cows << ".\n" << termcolor::reset;
    if (bulls == 4) {
        this->game_over = true;
    } 
}

void Game::run() {
    auto start = std::chrono::steady_clock::now();
    std::cout << secret;
    while (!game_over && attempts < 8)
    {
        std::string input = get_four_digit_user_input();
        attempts++;
        print_cows_and_bulls(input);
    }
    auto end = std::chrono::steady_clock::now();
    int duration = get_game_duration(start, end);

    if (attempts < 8) {
        if (high_score == 0 || duration < high_score) 
            fh::record_high_score(duration);

        std::cout << termcolor::bright_blue << "You won! It took you " << attempts << " attempts and " 
        << duration << " seconds. \n\n";
    }
    else {
        std::cout << termcolor::magenta << "You lost! It took you more than 7 attempts. Elapsed time: " << duration << " seconds.\n";
        std::cout << "Your number was: " << secret << ".\n\n";
    }

    play_again();
}

void Game::play_again() {
    std::string play_again;
    do {
        std::cout << "Do you want to play again (y/n)?\n";
        std::cin >> play_again; 
    } while (play_again != "y" && play_again != "n");

    if (play_again == "y") {
        std::cout << std::endl;
        reset_game();
        run();
    }
}

void Game::reset_game() {
    game_over = false;
    attempts = 0;
    secret = "";
    secret = get_random_four_digit_number();
    pause = false;
}

#endif // GAME_H
