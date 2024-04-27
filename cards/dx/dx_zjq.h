#ifndef DX_ZJQ_H
#define DX_ZJQ_H
#include "../base_card.h"

// 锻玄宗_筑基期


/*
灵气+1，防+4/8/12，获得2/3/4层辟邪
*/
class Card_dx_zjq_haoranzhengqi : public BaseCard {
public:
    Card_dx_zjq_haoranzhengqi(int level, int position) : BaseCard(level, position) {
        card_name = "浩然正气";
        is_attacking = false;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        LingQiGain(my_status, 1);
        int defence_gain = 0;
        int pi_xie_gain = 0;
        switch (level) {
            case 1:
                defence_gain = 4;
                pi_xie_gain = 2;
                break;
            case 2:
                defence_gain = 8;
                pi_xie_gain = 3;
                break;
            case 3:
                defence_gain = 12;
                pi_xie_gain = 4;
                break;
        }
        DefenseGain(my_status, defence_gain);
        BuffGain(my_status, BUFF_BI_XIE, pi_xie_gain);
        return 0;
    }
};

/*
灵气+2，生命+2/6/10
*/
class Card_dx_zjq_qichendantian : public BaseCard {
public:
    Card_dx_zjq_qichendantian(int level, int position) : BaseCard(level, position) {
        card_name = "气沉丹田";
        is_attacking = false;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        LingQiGain(my_status, 2);
        int health_gain = 0;
        switch (level) {
            case 1:
                health_gain = 2;
                break;
            case 2:
                health_gain = 6;
                break;
            case 3:
                health_gain = 10;
                break;
        }
        HealthGain(my_status, health_gain);
        return 0;
    }
};

/*
耗2生命，9/12/15攻，耗1灵气：此牌获得碎防并多4/5/6攻
*/
class Card_dx_zjq_shidalichen : public BaseCard {
public:
    Card_dx_zjq_shidalichen(int level, int position) : BaseCard(level, position) {
        card_name = "势大力沉";
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 9;
                break;
            case 2:
                attack = 12;
                break;
            case 3:
                attack = 15;
                break;
        }
        is_health_cost = true;
        health_cost = 2;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        int temp_attack = 0;
        switch (level) {
            case 1:
                temp_attack = 4;
                break;
            case 2:
                temp_attack = 5;
                break;
            case 3:
                temp_attack = 6;
                break;
        }
        bool exeflag = false;
        if (LingQiCostMax(my_status, 1)) {
            exeflag = true;
            this->card_sp_attr[CARD_SP_ATTR_SUI_FANG] += 1;
            this->attack += temp_attack;
        }
        Attack(my_status, enemy_status, attack, card_sp_attr);
        if (exeflag) {
            this->card_sp_attr[CARD_SP_ATTR_SUI_FANG] -= 1;
            this->attack -= temp_attack;
        }
        return 0;
    }
};

/*
防+4/5/6，气势+2/3/4，耗1灵气：生命+5
*/
class Card_dx_zjq_kuiranbudong : public BaseCard {
public:
    Card_dx_zjq_kuiranbudong(int level, int position) : BaseCard(level, position) {
        card_name = "岿然不动";
        is_attacking = false;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        int defence = 0;
        int qi_shi_gain = 0;
        switch (level) {
            case 1:
                defence = 4;
                qi_shi_gain = 2;
                break;
            case 2:
                defence = 5;
                qi_shi_gain = 3;
                break;
            case 3:
                defence = 6;
                qi_shi_gain = 4;
                break;
        }
        DefenseGain(my_status, defence);
        BuffGain(my_status, BUFF_QI_SHI, qi_shi_gain);
        if (LingQiCostMax(my_status, 1)) {
            HealthGain(my_status, 5);
        }
        return 0;
    }
};

/*
耗1灵气，14/18/22攻，无视防御，自身加3层虚弱
*/
class Card_dx_zjq_yeguixiao : public BaseCard {
public:
    Card_dx_zjq_yeguixiao(int level, int position) : BaseCard(level, position) {
        card_name = "夜鬼啸";
        ling_qi_cost = 1;
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 14;
                break;
            case 2:
                attack = 18;
                break;
            case 3:
                attack = 22;
                break;
        }
        card_sp_attr[CARD_SP_ATTR_WU_SHI_FANG_YU] = true;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        DebuffGain(my_status, DEBUFF_XU_RUO, 3);
        return 0;
    }
};

/*
4/6/8攻×2，灵气+2，自身加3层破绽
*/
class Card_dx_zjq_fengmingzhua : public BaseCard {
public:
    Card_dx_zjq_fengmingzhua(int level, int position) : BaseCard(level, position) {
        card_name = "风冥爪";
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 4;
                break;
            case 2:
                attack = 6;
                break;
            case 3:
                attack = 8;
                break;
        }
    }
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        Attack(my_status, enemy_status, attack, card_sp_attr);
        LingQiGain(my_status, 2);
        DebuffGain(my_status, DEBUFF_PO_ZHAN, 3);
        return 0;
    }
};

/*
7/9/11攻，每有2体魄加1防（上限8/11/14）
*/
class Card_dx_zjq_tanmazhang : public BaseCard {
public:
    Card_dx_zjq_tanmazhang(int level, int position) : BaseCard(level, position) {
        card_name = "探马掌";
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
    }
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        int temp_max = 0;
        switch (level) {
            case 1:
                temp_max = 8;
                break;
            case 2:
                temp_max = 11;
                break;
            case 3:
                temp_max = 14;
                break;
        }
        int defense = my_status->ti_po / 2;
        defense = defense > temp_max ? temp_max : defense;
        DefenseGain(my_status, defense);
        return 0;
    }
};

/*
5/7/9攻，体魄+2，体魄≥15：防+4/6/8
*/
class Card_dx_zjq_duanjin : public BaseCard {
public:
    Card_dx_zjq_duanjin(int level, int position) : BaseCard(level, position) {
        card_name = "锻筋";
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 5;
                break;
            case 2:
                attack = 7;
                break;
            case 3:
                attack = 9;
                break;
        }
        card_tag[TI_PO_CARD] = true;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        TiPoGain(my_status, 2);
        if (my_status->ti_po >= 15) {
            int defense = 0;
            switch (level) {
                case 1:
                    defense = 4;
                    break;
                case 2:
                    defense = 6;
                    break;
                case 3:
                    defense = 8;
                    break;
            }
            DefenseGain(my_status, defense);
        }
        return 0;
    }
};

/*
耗4生命，10/11/12攻，使用下一张崩拳时加2/3/4气势
*/
class Card_dx_zjq_bengquan_han : public BaseCard {
public:
    Card_dx_zjq_bengquan_han(int level, int position) : BaseCard(level, position) {
        card_name = "崩拳·撼";
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 10;
                break;
            case 2:
                attack = 11;
                break;
            case 3:
                attack = 12;
                break;
        }
        is_health_cost = true;
        health_cost = 4;
        card_tag[BENG_QUAN_CARD] = true;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        int qi_shi_gain = 0;
        switch (level) {
            case 1:
                qi_shi_gain = 2;
                break;
            case 2:
                qi_shi_gain = 3;
                break;
            case 3:
                qi_shi_gain = 4;
                break;
        }
        my_status->task_quene_before_effect->addTask(
            [my_status, qi_shi_gain](BaseCard* card){
                BuffGain(my_status, BUFF_QI_SHI, qi_shi_gain);
            },
            [](BaseCard* card){ return card->card_tag[BENG_QUAN_CARD] ? true : false; },
            [](BaseCard* card){ return true; },
            REMARK_BENG_QUAN
        );
        return 0;
    }
};

/*
耗4生命，10/11/12攻，使用下一张崩拳时施加1/2/3层外伤
*/
class Card_dx_zjq_bengquan_can : public BaseCard {
public:
    Card_dx_zjq_bengquan_can(int level, int position) : BaseCard(level, position) {
        card_name = "崩拳·缠";
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 10;
                break;
            case 2:
                attack = 11;
                break;
            case 3:
                attack = 12;
                break;
        }
        is_health_cost = true;
        health_cost = 4;
        card_tag[BENG_QUAN_CARD] = true;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        int temp_status = 0;
        switch (level) {
            case 1:
                temp_status = 1;
                break;
            case 2:
                temp_status = 2;
                break;
            case 3:
                temp_status = 3;
                break;
        }
        enemy_status->task_quene_before_effect->addTask(
            [enemy_status, temp_status](BaseCard* card){
                DebuffGain(enemy_status, DEBUFF_WAI_SHANG, temp_status);
            },
            [](BaseCard* card){ return card->card_tag[BENG_QUAN_CARD] ? true : false; },
            [](BaseCard* card){ return true; },
            REMARK_BENG_QUAN
        );
        return 0;
    }
};

/*
耗4生命，10/14/18攻，碎防（下一张崩拳也附加此效果）
*/
class Card_dx_zjq_bengquan_tu : public BaseCard {
public:
    Card_dx_zjq_bengquan_tu(int level, int position) : BaseCard(level, position) {
        card_name = "崩拳·突";
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 10;
                break;
            case 2:
                attack = 14;
                break;
            case 3:
                attack = 18;
                break;
        }
        is_health_cost = true;
        health_cost = 4;
        card_tag[BENG_QUAN_CARD] = true;
        card_sp_attr[CARD_SP_ATTR_SUI_FANG] = true;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        my_status->task_quene_before_effect->addTask(
            [my_status](BaseCard* card){
                card->card_sp_attr[CARD_SP_ATTR_SUI_FANG] += 1;
                my_status->task_quene_after_effect->addTask(
                    [my_status](BaseCard* card){
                        card->card_sp_attr[CARD_SP_ATTR_SUI_FANG] -= 1;
                    },
                    [](BaseCard* card){ return true; },
                    [](BaseCard* card){ return true; }
                );
            },
            [](BaseCard* card){ return card->card_tag[BENG_QUAN_CARD] && card-> is_attacking ? true : false; },
            [](BaseCard* card){ return true; },
            REMARK_BENG_QUAN
        );
        return 0;
    }
};



// BaseCard* dx_zjq_create(int card_serial_number, int level, int position) {
//     switch (card_serial_number) {
//         case 1:
//             return new Card_dx_zjq_haoranzhengqi(level, position);
//             break;
//         case 2:
//             return new Card_dx_zjq_qichendantian(level, position);
//             break;
//         case 3:
//             return new Card_dx_zjq_shidalichen(level, position);
//             break;
//         case 4:
//             return new Card_dx_zjq_kuiranbudong(level, position);
//             break;
//         case 5:
//             return new Card_dx_zjq_yeguixiao(level, position);
//             break;
//         case 6:
//             return new Card_dx_zjq_fengmingzhua(level, position);
//             break;
//         case 7:
//             return new Card_dx_zjq_tanmazhang(level, position);
//             break;
//         case 8:
//             return new Card_dx_zjq_duanjin(level, position);
//             break;
//         case 9:
//             return new Card_dx_zjq_bengquan_han(level, position);
//             break;
//         case 10:
//             return new Card_dx_zjq_bengquan_can(level, position);
//             break;
//         case 11:
//             return new Card_dx_zjq_bengquan_tu(level, position);
//             break;
//         default:
//             throw std::invalid_argument("Invalid type");
//     }
// }


#endif // DX_ZJQ_H