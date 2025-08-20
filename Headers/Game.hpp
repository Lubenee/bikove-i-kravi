#if !defined(GAME_H)
#define GAME_H

#include "Utils.hpp"
#include "FileHandler/FileHandler.hpp"
#include "Termcolor/Termcolor.hpp"
#include "RandomNumber.hpp"
#include "Difficulty.hpp"
#include "InputHandler.hpp"

using namespace std::chrono;

#define MAX_ATTEMPTS 8

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

    DifficultySelector::Difficulty difficulty;
};

Game::Game()
    : game_over(false), high_score(0), 
      secret(""), attempts(0), pause(false),
      difficulty(DifficultySelector::Difficulty::Easy)
{
    reset_game();
    high_score = fh::read_high_score();
    if (high_score > 0) 
        std::cout << termcolor::reset << "Current high score: " << high_score << " seconds." << "\n\n";
}

void Game::reset_game() {
    try {
        game_over = false;
        attempts = 0;
        secret = "";
        difficulty = DifficultySelector::select();
        secret = get_random_n_digit_number(static_cast<int>(difficulty));
        pause = false;
    }
    catch (const std::exception& e) {
        std::cout << "Internal error: " << e.what() << std::endl;
        throw e;
    }
}

void Game::run() {
    auto start = std::chrono::steady_clock::now();
    while (!game_over && attempts < MAX_ATTEMPTS)
    {
        std::string input = InputHandler::get_n_digit_number(static_cast<int>(difficulty));
        attempts++;
        print_cows_and_bulls(input);
    }
    auto end = std::chrono::steady_clock::now();
    int duration = get_game_duration(start, end);

    if (attempts < MAX_ATTEMPTS) {
        if (high_score == 0 || duration < high_score) 
            fh::record_high_score(duration);

        std::cout << termcolor::bright_blue << "You won! It took you " 
        << attempts << " attempts and " << duration << " seconds. \n\n";
    }
    else {
        std::cout << termcolor::magenta << "You lost! It took you more than " << MAX_ATTEMPTS - 1 << " attempts. Elapsed time: " << duration << " seconds.\n";
        std::cout << "Your number was: " << secret << ".\n\n";
    }

    play_again();
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
    if (bulls == this->difficulty) {
        this->game_over = true;
    } 
}

void Game::play_again() {
    if (InputHandler::ask_yes_no("Do you want to play again")) {
        std::cout << std::endl;
        reset_game();
        run();
    }
}

#endif // GAME_H
