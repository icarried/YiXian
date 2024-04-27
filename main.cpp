
#include <iostream>
#include "battle.h"

int main() {
    
    Battle *battle = new Battle();
    std::cout << "我方卡组" << std::endl;
    battle->decks[0]->ShowDeck();
    std::cout << "敌方卡组" << std::endl;
    battle->decks[1]->ShowDeck();
    std::cout << "Game Start!" << std::endl;
    int result = battle->BattleStart();
    std::cout << result << std::endl;
    std::cout << "Game Over!" << std::endl;
    delete battle;
    return 0;
}