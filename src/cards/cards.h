#ifndef CARDS_H
#define CARDS_H

// ------卡牌效果更新时间：2024.5.3----------
#include "base_card.h"
// #include "./yl/yl_init.h"
// #include "./wx/wx_init.h"
// #include "./qx/qx_init.h"
#include "./dx/dx_init.h"
#include "./zsxm/zsxm_init.h"
// 更多卡牌完成后，将其包含进来

// 继承BaseCard类，实现不同牌的效果
class Card_qt_qtq_pttonggongji : public BaseCard {
public:
    Card_qt_qtq_pttonggongji(int level, int position) : BaseCard(level, position) {
        card_name = "普通攻击";
        is_attacking = true;
        attack = 3;
        card_tag[PU_TONG_GONG_JI_CARD] = true;
    }
    //执行牌的效果，并返回执行状态值
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        return 0;
    }
    ~Card_qt_qtq_pttonggongji() {

    }
};

class Card_dx_lqq_ag : public BaseCard {
public:
    Card_dx_lqq_ag(int level, int position) : BaseCard(level, position) {
        card_name = "示例牌";
        is_attacking = true;
        attack = 2;
        ling_qi_cost = 0;
        is_health_cost = false;
        health_cost = 0;
        card_tag[LING_JIAN_CARD] = true;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        return 0;
    }
};

#endif // !CARDS_H


