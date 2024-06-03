#include "Deck.h"
#include "./cards/cards.h"

Deck::Deck() {
    opened_card_end_index = 8;
     // 初始化卡组为普通攻击牌
    for (int i = 0; i < DECK_END_INDEX; i++) {
        cards[i] = new Card_qt_lqq_pttonggongji(1, i);
    }
    
    // 初始化手牌为普通攻击牌
    for (int i = 0; i < HAND_CARD_END_INDEX; i++) {
        hand_cards[i] = new Card_qt_lqq_pttonggongji(1, i);
    }
}

// 虚拷贝函数
Deck* Deck::Clone() const {
    return new Deck(*this);
}

// 拷贝构造函数
Deck::Deck(const Deck &deck) {
    opened_card_end_index = deck.opened_card_end_index;
    for (int i = 0; i < DECK_END_INDEX; i++) {
        cards[i] = deck.cards[i]->Clone();
    }

    for (int i = 0; i < HAND_CARD_END_INDEX; i++) {
        hand_cards[i] = deck.hand_cards[i]->Clone();
    }
}

// 析构函数
Deck::~Deck() {
    for (int i = 0; i < DECK_END_INDEX; i++) {
        delete cards[i];
    }
    
    for (int i = 0; i < HAND_CARD_END_INDEX; i++) {
        delete hand_cards[i];
    }
}

// 交换卡组中的两张牌
void Deck::SwapCard(int position1, int position2) {
    BaseCard *temp = cards[position1];
    cards[position1] = cards[position2];
    cards[position2] = temp;
}

// 交换手牌中的两张牌
void Deck::SwapHandCard(int position1, int position2) {
    BaseCard *temp = hand_cards[position1];
    hand_cards[position1] = hand_cards[position2];
    hand_cards[position2] = temp;
}

// 判断一张牌是否是普通攻击使用cards[position]->card_tag[PU_TONG_GONG_JI_CARD] == true判断
// 整理手牌
// 使得非普通攻击牌均在前，普通攻击均在后，并记录非普通攻击牌的数量
// 将非普通攻击牌中的(消耗牌||持续牌)放在前面，并记录(消耗牌||持续牌)的数量
CardCountList Deck::SortHandCard() {
    int count_non_pu_tong_gong_ji = 0;
    for (int i = 0; i < HAND_CARD_END_INDEX; i++) {
        if (!hand_cards[i]->card_tag[PU_TONG_GONG_JI_CARD]) {
            if (i != count_non_pu_tong_gong_ji) {
                SwapHandCard(i, count_non_pu_tong_gong_ji);
            }
            count_non_pu_tong_gong_ji++;
        }
    }

    int count_xiao_hao_chi_xu = 0;
    for (int i = 0; i < count_non_pu_tong_gong_ji; i++) {
        if (hand_cards[i]->card_tag[XIAO_HAO_CARD] || hand_cards[i]->card_tag[CHI_XU_CARD]) {
            if (i != count_xiao_hao_chi_xu) {
                SwapHandCard(i, count_xiao_hao_chi_xu);
            }
            count_xiao_hao_chi_xu++;
        }
    }
    
    int count_normal_cards = count_non_pu_tong_gong_ji - count_xiao_hao_chi_xu;
    return {count_xiao_hao_chi_xu, count_normal_cards, count_non_pu_tong_gong_ji};
}

// 任意交换卡组和手牌中的牌，额外变量代表第一张牌是卡组还是手牌，第二张牌是卡组还是手牌
void Deck::SwapCard(int position1, bool is_deck1, int position2, bool is_deck2) {
    BaseCard *temp;
    if (is_deck1) {
        if (is_deck2) {
            temp = cards[position1];
            cards[position1] = cards[position2];
            cards[position2] = temp;
        }
        else {
            temp = cards[position1];
            cards[position1] = hand_cards[position2];
            hand_cards[position2] = temp;
        }
    }
    else {
        if (is_deck2) {
            temp = hand_cards[position1];
            hand_cards[position1] = cards[position2];
            cards[position2] = temp;
        }
        else {
            temp = hand_cards[position1];
            hand_cards[position1] = hand_cards[position2];
            hand_cards[position2] = temp;
        }
    }
}

// 把所有卡组中的牌放入手牌（即将卡组中所有非普通攻击牌替换手牌中的普通攻击）
void Deck::PutAllDeckToHand() {
    for (int i = 0; i < DECK_END_INDEX; i++) {
        if (!cards[i]->card_tag[PU_TONG_GONG_JI_CARD]) {
            for (int j = 0; j < HAND_CARD_END_INDEX; j++) {
                if (hand_cards[j]->card_tag[PU_TONG_GONG_JI_CARD]) {
                    SwapHandCard(i, j);
                    break;
                }
            }
        }
    }
}

// 把一张牌新的牌放入手牌
// 返回值为新牌的位置, 如果没有空位则返回-1, 并删除新牌
// 用于获取不在卡牌堆的牌
int Deck::AddCardtoHand(BaseCard* card) {
    for (int i = 0; i < HAND_CARD_END_INDEX; i++) {
        if (hand_cards[i]->card_tag[PU_TONG_GONG_JI_CARD]) {
            delete hand_cards[i];
            hand_cards[i] = card;
            return i;
        }
    }
    delete card;
    return -1;
}

// 获取卡组中position位置的卡牌指针
BaseCard* Deck::GetCard(int position) {
    return cards[position];
}

// 显示卡组
void Deck::ShowDeck() {
    for (int i = 0; i < opened_card_end_index; i++) {
        std::cout << cards[i]->level << "级《" << cards[i]->card_name << "》 ";
    }
    std::cout << std::endl;
}

// 显示手牌
void Deck::ShowHand() {
    for (int i = 0; i < HAND_CARD_END_INDEX; i++) {
        std::cout << hand_cards[i]->level << "级《" << hand_cards[i]->card_name << "》 ";
    }
    std::cout << std::endl;
}
