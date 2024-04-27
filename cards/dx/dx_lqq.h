#ifndef DX_LQQ_H
#define DX_LQQ_H
#include "../base_card.h"

// 锻玄宗_炼气期


/*
耗2/3/4生命，8/10/12攻，耗1灵气：追加4/6/8攻
*/
class Card_dx_lqq_xueqifanggang : public BaseCard {
public:
    Card_dx_lqq_xueqifanggang(int level, int position) : BaseCard(level, position) {
        card_name = "血气方刚";
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 8;
                health_cost = 2;
                break;
            case 2:
                attack = 10;
                health_cost = 3;
                break;
            case 3:
                attack = 12;
                health_cost = 4;
                break;
        }
        is_health_cost = true;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        if (LingQiCostMax(my_status, 1)) {
            Attack(my_status, enemy_status, 4, card_sp_attr);
        }
        return 0;
    }
};

/*
6/9/12攻，随机减1层负面状态
*/
class Card_dx_lqq_qianjinzhui : public BaseCard {
public:
    Card_dx_lqq_qianjinzhui(int level, int position) : BaseCard(level, position) {
        card_name = "千斤坠";
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 6;
                break;
            case 2:
                attack = 9;
                break;
            case 3:
                attack = 12;
                break;
        }
    }
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        DebuffRandomReduce(enemy_status, 1);
        return 0;
    }
};


/*
耗1灵气，12/15/18攻，自身加1层内伤
*/
class Card_dx_lqq_pokongzhua : public BaseCard {
public:
    Card_dx_lqq_pokongzhua(int level, int position) : BaseCard(level, position) {
        card_name = "破空爪";
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 12;
                break;
            case 2:
                attack = 15;
                break;
            case 3:
                attack = 18;
                break;
        }
        ling_qi_cost = 1;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        DebuffGain(my_status, DEBUFF_NEI_SHANG, 1);
        return 0;
    }
};

/*
6/9/12攻（每有1层气势多1攻），耗1灵气：气势+2
*/
class Card_dx_lqq_zhaoqipengbo : public BaseCard {
public:
    Card_dx_lqq_zhaoqipengbo(int level, int position) : BaseCard(level, position) {
        card_name = "朝气蓬勃";
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 6;
                break;
            case 2:
                attack = 9;
                break;
            case 3:
                attack = 12;
                break;
        }
    }
    int Effect(Status* my_status, Status* enemy_status) {
        if (LingQiCostMax(my_status, 1)) {
            BuffGain(my_status, BUFF_QI_SHI, 2);
        }
        int temp_attack = my_status->buff.buff[BUFF_QI_SHI];
        Attack(my_status, enemy_status, attack + temp_attack, card_sp_attr);
        return 0;
    }
};

/*
2/5/8攻，灵气+1，气势+2
*/
class Card_dx_lqq_qishi : public BaseCard {
public:
    Card_dx_lqq_qishi(int level, int position) : BaseCard(level, position) {
        card_name = "起势";
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 2;
                break;
            case 2:
                attack = 5;
                break;
            case 3:
                attack = 8;
                break;
        }
    }
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        LingQiGain(my_status, 1);
        BuffGain(my_status, BUFF_QI_SHI, 2);
        return 0;
    }
};

/*
8/11/14攻，灵气+1，自身加1层外伤
*/
class Card_dx_lqq_luochapu : public BaseCard {
public:
    Card_dx_lqq_luochapu(int level, int position) : BaseCard(level, position) {
        card_name = "罗刹扑";
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 8;
                break;
            case 2:
                attack = 11;
                break;
            case 3:
                attack = 14;
                break;
        }
    }
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        LingQiGain(my_status, 1);
        DebuffGain(enemy_status, DEBUFF_WAI_SHANG, 1);
        return 0;
    }
};

/*
灵气+1，体魄+2，生命+1/4/7
*/
class Card_dx_lqq_baoqifa : public BaseCard {
public:
    Card_dx_lqq_baoqifa(int level, int position) : BaseCard(level, position) {
        card_name = "抱气法";
        is_attacking = false;
        card_tag[TI_PO_CARD] = true;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        LingQiGain(my_status, 1);
        TiPoGain(my_status, 2);
        int health_gain = 0;
        switch (level) {
            case 1:
                health_gain = 1;
                break;
            case 2:
                health_gain = 4;
                break;
            case 3:
                health_gain = 7;
                break;
        }
        HealthGain(my_status, health_gain);
        return 0;
    }
};

/*
耗4生命，10/13/16攻，每有2体魄此牌少耗1生命
*/
class Card_dx_lqq_pishanzhang : public BaseCard {
public:
    Card_dx_lqq_pishanzhang(int level, int position) : BaseCard(level, position) {
        card_name = "劈山掌";
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 10;
                break;
            case 2:
                attack = 13;
                break;
            case 3:
                attack = 16;
                break;
        }
        is_health_cost = true;
        is_health_cost_modifiable = true;
        health_cost = 4;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        return 0;
    }
    int HealthCostModify(Status* my_status, Status* enemy_status) {
        int temp_health_cost = health_cost;
        temp_health_cost -= my_status->ti_po / 2;
        if (temp_health_cost < 0) {
            temp_health_cost = 0;
        }
        return temp_health_cost;
    }
};

/*
6/9/12攻，体魄+1
*/
class Card_dx_lqq_duanquan : public BaseCard {
public:
    Card_dx_lqq_duanquan(int level, int position) : BaseCard(level, position) {
        card_name = "锻拳";
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 6;
                break;
            case 2:
                attack = 9;
                break;
            case 3:
                attack = 12;
                break;
        }
        card_tag[TI_PO_CARD] = true;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        TiPoGain(my_status, 1);
        return 0;
    }
};

/*
耗2生命，7/11/14攻，下一张崩拳耗生命时加回所耗生命
*/
class Card_dx_lqq_bengquan_tan : public BaseCard {
public:
    Card_dx_lqq_bengquan_tan(int level, int position) : BaseCard(level, position) {
        card_name = "崩拳·弹";
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 8;
                break;
            case 2:
                attack = 11;
                break;
            case 3:
                attack = 14;
                break;
        }
        is_health_cost = true;
        health_cost = 2;
        card_tag[BENG_QUAN_CARD] = true;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        my_status->task_quene_before_effect->addTask(
            [my_status](BaseCard* card){
                HealthGain(my_status, card->health_cost);
            },
            [](BaseCard* card){ return card->card_tag[BENG_QUAN_CARD] ? true : false; },
            [](BaseCard* card){ return true; },
            REMARK_BENG_QUAN
        );
        return 0;
    }
};

/*
耗3生命，7/9/11攻，防+2/3/4（下一张崩拳也附加此效果）
*/
class Card_dx_lqq_bengquan_feng : public BaseCard {
public:
    Card_dx_lqq_bengquan_feng(int level, int position) : BaseCard(level, position) {
        card_name = "崩拳·封";
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 7;
                break;
            case 2:
                attack = 9;
                break;
            case 3:
                attack = 11;
                break;
        }
        is_health_cost = true;
        health_cost = 3;
        card_tag[BENG_QUAN_CARD] = true;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        int defense = 0;
        switch (level) {
            case 1:
                defense = 2;
                break;
            case 2:
                defense = 3;
                break;
            case 3:
                defense = 4;
                break;
        }
        DefenseGain(my_status, defense);
        my_status->task_quene_before_effect->addTask(
            [my_status, defense](BaseCard* card){
                DefenseGain(my_status, defense);
            },
            [](BaseCard* card){ return card->card_tag[BENG_QUAN_CARD] ? true : false; },
            [](BaseCard* card){ return true; },
            REMARK_BENG_QUAN
        );
        return 0;
    }
};

/*
9/11/13攻 下一张崩拳多2/3/4攻
*/
class Card_dx_lqq_bengquan_chuo : public BaseCard {
public:
    Card_dx_lqq_bengquan_chuo(int level, int position) : BaseCard(level, position) {
        card_name = "崩拳·戳";
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 9;
                break;
            case 2:
                attack = 11;
                break;
            case 3:
                attack = 13;
                break;
        }
        is_health_cost = true;
        health_cost = 3;
        card_tag[BENG_QUAN_CARD] = true;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        int temp_status = 0;
        switch (level) {
            case 1:
                temp_status = 2;
                break;
            case 2:
                temp_status = 3;
                break;
            case 3:
                temp_status = 4;
                break;
        }
        my_status->task_quene_before_effect->addTask(
            [my_status, temp_status](BaseCard* card){
                card->card_sp_attr[CARD_SP_ATTR_DUO_GONG] += temp_status;
                my_status->task_quene_after_effect->addTask(
                    [my_status, temp_status](BaseCard* card){
                        card->card_sp_attr[CARD_SP_ATTR_DUO_GONG] -= temp_status;
                    },
                    [](BaseCard* card){ return true; },
                    [](BaseCard* card){ return true; }
                );
            },
            [](BaseCard* card){ return card->card_tag[BENG_QUAN_CARD] && card->is_attacking ? true : false; },
            [](BaseCard* card){ return true; },
            REMARK_BENG_QUAN
        );
        
        return 0;
    }
};


// BaseCard* dx_lqq_create(int card_serial_number, int level, int position) {
//     switch (card_serial_number) {
//         case 1:
//             return new Card_dx_lqq_xueqifanggang(level, position);
//         case 2:
//             return new Card_dx_lqq_qianjinzhui(level, position);
//         case 3:
//             return new Card_dx_lqq_pokongzhua(level, position);
//         case 4:
//             return new Card_dx_lqq_zhaoqipengbo(level, position);
//         case 5:
//             return new Card_dx_lqq_qishi(level, position);
//         case 6:
//             return new Card_dx_lqq_luochapu(level, position);
//         case 7:
//             return new Card_dx_lqq_baoqifa(level, position);
//         case 8:
//             return new Card_dx_lqq_pishanzhang(level, position);
//         case 9:
//             return new Card_dx_lqq_duanquan(level, position);
//         case 10:
//             return new Card_dx_lqq_bengquan_tan(level, position);
//         case 11:
//             return new Card_dx_lqq_bengquan_feng(level, position);
//         case 12:
//             return new Card_dx_lqq_bengquan_chuo(level, position);
//         default:
//             throw std::invalid_argument("Invalid type");
//     }
// }

#endif // DX_LQQ_H