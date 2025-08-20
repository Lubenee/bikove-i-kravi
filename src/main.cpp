#include "Game.hpp"

int main() {
    try {
        Game game;
        game.run();
    }
    catch (...) {
        return 1;
    }
    return 0;
}
