#if !defined(GAME_H)
#define GAME_H

#include "Utils.hpp"
#include "FileHandler/FileHandler.hpp"
#include "Termcolor/Termcolor.hpp"
#include "RandomNumber.hpp"
#include "Difficulty.hpp"
#include "Timer.hpp"
#include "InputHandler.hpp"
#include "Renderer.hpp"

using namespace std::chrono;

class Game
{
public:
    Game();
    void run();

    ~Game() = default;
private:
    void print_cows_and_bulls(std::string input);
    void play_single_game();
    void reset_game();

private:
    bool game_over;
    int high_score;
    std::string secret;
    int attempts;
    bool pause;
    int max_attempts;

    DifficultySelector::Difficulty difficulty;
    Renderer render;
};

Game::Game()
    : game_over(false), high_score(0), 
      secret(""), attempts(0), pause(false),
      difficulty(DifficultySelector::Difficulty::Easy),
      max_attempts(DifficultySelector::max_attempts(difficulty))
{
    high_score = fh::read_high_score();
    render.high_score(high_score);
}

void Game::reset_game() {
    game_over       = false;
    attempts        = 0;
    secret          = "";
    difficulty      = DifficultySelector::select();
    secret          = get_random_n_digit_number(static_cast<int>(difficulty));
    max_attempts    = DifficultySelector::max_attempts(difficulty);
    pause           = false;
}

void Game::run() {
    do {
        reset_game();
        play_single_game();
    } while (InputHandler::ask_yes_no("Do you want to play again"));
}

void Game::play_single_game() {
    render.message("\nMax attempts: " + std::to_string(max_attempts));
    Timer timer;
    timer.start();
    while (!game_over && attempts < max_attempts)
    {
        std::string input = InputHandler::get_n_digit_number(static_cast<int>(difficulty));
        attempts++;
        print_cows_and_bulls(input);
    }
    int duration = timer.elapsed_seconds();

    if (attempts < max_attempts) {
        if (high_score == 0 || duration < high_score) 
            fh::record_high_score(duration);
        render.win_message(attempts, duration);
    }
    else {
        render.loss_message(max_attempts, duration, secret);
    }
}

void Game::print_cows_and_bulls(std::string input) {
    int bulls = 0, cows = 0;
    for (int i = 0; i < secret.size(); ++i) {
        if (input[i] == secret[i]) bulls++;
        else if (includes(secret, input[i])) cows++;
    }
    render.bulls_and_cows(bulls, cows);
    if (bulls == difficulty) game_over = true;
}

#endif // GAME_H
