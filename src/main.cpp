
#include <iostream>
#include "game.h"

int main() {
    BaseCard::DisplayCountMatrixGrid();

    Game *game = new Game();
    if (!game->is_game_ready) {
        std::cout << "出现问题，无法开始" << std::endl;
        return 0;
    }
    game->BattleStart();
    return 0;
}