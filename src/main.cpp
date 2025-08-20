#include "Game.hpp"

int main() {
    try {
        Game game;
        game.run();
    }
    catch (...) {
        std::cout << "Internal error." << std::flush;
        return 1;
    }
    return 0;
}
