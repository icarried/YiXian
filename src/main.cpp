
#include <iostream>
#include "battle.h"

int main() {
    
    Battle *battle = new Battle(10);
    std::cout << "我方卡组" << std::endl;
    battle->decks[0]->ShowDeck();
    std::cout << "敌方卡组" << std::endl;
    battle->decks[1]->ShowDeck();
    std::cout << "Game Start!" << std::endl;
    int result = battle->BattleStart();
    if (result > 0) {
        std::cout << "我方胜利" << std::endl;
    } else if (result < 0) {
        std::cout << "敌方胜利" << std::endl;
    } else {
        std::cout << "平局" << std::endl;
    }
    std::cout << "Game Over!" << std::endl;
    delete battle;
    return 0;
}