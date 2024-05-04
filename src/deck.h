#ifndef DECK_H
#define DECK_H

#include <iostream>
#include "head.h"
class BaseCard;

// 手牌数量
#define HAND_CARD_END_INDEX 30

struct CardCountList {
    int count_xiao_hao_chi_xu;
    int count_normal_cards;
    int count_non_pu_tong_gong_ji;
};

class Deck {
public:
    Deck();
    Deck(const Deck &deck);
    ~Deck();
    
    void SwapCard(int position1, int position2);
    void SwapHandCard(int position1, int position2);
    CardCountList SortHandCard();
    void SwapCard(int position1, bool is_deck1, int position2, bool is_deck2);
    void PutAllDeckToHand();
    void ShowDeck();
    int AddCardtoHand(BaseCard* card);
    BaseCard* GetCard(int position);

    BaseCard *cards[DECK_END_INDEX];
    BaseCard *hand_cards[HAND_CARD_END_INDEX];
};

#endif // !DECK_H
