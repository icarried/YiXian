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
    virtual Deck* Clone() const;
    Deck(const Deck &deck);
    virtual ~Deck();
    
    void SwapCard(int position1, int position2);
    void SwapHandCard(int position1, int position2);
    CardCountList SortHandCard();
    void SwapCard(int position1, bool is_deck1, int position2, bool is_deck2);
    void PutAllDeckToHand();
    void ShowDeck();
    void ShowHand();
    int AddCardtoHand(BaseCard* card); // 把一张牌新的牌放入手牌, 返回值为新牌的位置, 如果没有空位则返回-1, 并删除新牌
    BaseCard* GetCard(int position); // 获取卡组中position位置的卡牌指针
    static bool LevelModify(BaseCard* card, int level_change); // 改变牌的等级，通过is_level_modifiable启用，返回值is_level_modifiable，可以通过返回值判断是否修改成功

    BaseCard *cards[DECK_END_INDEX];
    BaseCard *hand_cards[HAND_CARD_END_INDEX];
    int opened_card_end_index; // 已经打开的卡牌槽位置, 为battle_round + 2 且不超过8
};

#endif // !DECK_H
