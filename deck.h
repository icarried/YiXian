#ifndef DECK_H
#define DECK_H


#include <iostream>
#include "./cards/cards.h"
#include "head.h"
#define HAND_CARD_END_INDEX 30

struct CardCountList {
    int count_xiao_hao_chi_xu;
    int count_normal_cards;
    int count_non_pu_tong_gong_ji;
};


// 卡组类
class Deck {
public:
    // 构造函数
    Deck() {
        // 初始化卡组为普通攻击牌
        for (int i = 0; i < DECK_END_INDEX; i++) {
            cards[i] = new Card_qt_qtq_pttonggongji(1, i);
        }

        // 第一张牌改为崩拳·戳
        delete cards[0];
        cards[0] = new Card_dx_lqq_bengquan_chuo(1, 0);

        // // 第二张牌改为崩拳·连崩
        // delete cards[1];
        // cards[1] = new Card_dx_yyq_bengquan_lianbeng(1, 1);

        // 第三张牌改为崩拳·连崩
        delete cards[2];
        cards[2] = new Card_dx_yyq_bengquan_lianbeng(1, 2);

        // 第四张牌改为崩拳·连崩
        delete cards[3];
        cards[3] = new Card_dx_yyq_bengquan_lianbeng(1, 3);

        // 初始化手牌
        for (int i = 0; i < HAND_CARD_END_INDEX; i++) {
            hand_cards[i] = new Card_qt_qtq_pttonggongji(1, i);
        }
    }
    // 拷贝构造函数
    Deck(const Deck &deck) {
        for (int i = 0; i < DECK_END_INDEX; i++) {
            cards[i] = deck.cards[i];
        }
        for (int i = 0; i < HAND_CARD_END_INDEX; i++) {
            hand_cards[i] = deck.hand_cards[i];
        }
    }

    // 析构函数
    ~Deck() {
        for (int i = 0; i < DECK_END_INDEX; i++) {
            delete cards[i];
        }
        for (int i = 0; i < HAND_CARD_END_INDEX; i++) {
            delete hand_cards[i];
        }
    }
    // 交换卡组中的两张牌
    void SwapCard(int position1, int position2) {
        BaseCard *temp = cards[position1];
        cards[position1] = cards[position2];
        cards[position2] = temp;
    }
    // 交换手牌中的两张牌
    void SwapHandCard(int position1, int position2) {
        BaseCard *temp = hand_cards[position1];
        hand_cards[position1] = hand_cards[position2];
        hand_cards[position2] = temp;
    }
    // 判断一张牌是否是普通攻击使用cards[position]->card_tag[PU_TONG_GONG_JI_CARD] == true判断
    // 整理手牌
    // 使得非普通攻击牌均在前，普通攻击均在后，并记录非普通攻击牌的数量
    // 将非普通攻击牌中的(消耗牌||持续牌)放在前面，并记录(消耗牌||持续牌)的数量
    CardCountList SortHandCard() {
        // 使得非普通攻击牌均在前，普通攻击均在后，并记录非普通攻击牌的数量
        int count_non_pu_tong_gong_ji = 0;
        for (int i = 0; i < HAND_CARD_END_INDEX; i++) {
            if (hand_cards[i]->card_tag[PU_TONG_GONG_JI_CARD] == false) {
                if (i != count_non_pu_tong_gong_ji) {
                    SwapHandCard(i, count_non_pu_tong_gong_ji);
                }
                count_non_pu_tong_gong_ji++;
            }
        }
        // 将非普通攻击牌中的(消耗牌||持续牌)放在前面，并记录(消耗牌||持续牌)的数量
        int count_xiao_hao_chi_xu = 0;
        for (int i = 0; i < count_non_pu_tong_gong_ji; i++) {
            if (hand_cards[i]->card_tag[XIAO_HAO_CARD] == true || hand_cards[i]->card_tag[CHI_XU_CARD] == true) {
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
    void SwapCard(int position1, bool is_deck1, int position2, bool is_deck2) {
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
    void PutAllDeckToHand() {
        for (int i = 0; i < DECK_END_INDEX; i++) {
            if (cards[i]->card_tag[PU_TONG_GONG_JI_CARD] == false) {
                for (int j = 0; j < HAND_CARD_END_INDEX; j++) {
                    if (hand_cards[j]->card_tag[PU_TONG_GONG_JI_CARD] == true) {
                        SwapHandCard(i, j);
                        break;
                    }
                }
            }
        }
    }


    // 显示卡组
    void ShowDeck() {
        for (int i = 0; i < DECK_END_INDEX; i++) {
            std::cout << cards[i]->level << "级《" << cards[i]->card_name << "》 ";
        }
        std::cout << std::endl;
    }

    //定义卡组（场上的牌）
    BaseCard *cards[DECK_END_INDEX];

    //定义手牌
    BaseCard *hand_cards[HAND_CARD_END_INDEX];
};

#endif // !DECK_H