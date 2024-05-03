#ifndef DX_HSQ_H
#define DX_HSQ_H
#include "../base_card.h"

// 锻玄宗_化神期

/*
10/12/14攻，生命+4/6/8，身法+4/5/6（每剩1气势多2）
*/
class Card_dx_hsq_tiandihaodang : public BaseCard {
public:
    Card_dx_hsq_tiandihaodang(int level, int position) : BaseCard(level, position) {
        card_name = "天地浩荡";
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 10;
                break;
            case 2:
                attack = 12;
                break;
            case 3:
                attack = 14;
                break;
        }
    }
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        int health_gain = 0;
        int shen_fa_gain = 0;
        switch (level) {
            case 1:
                health_gain = 4;
                shen_fa_gain = 4;
                break;
            case 2:
                health_gain = 6;
                shen_fa_gain = 5;
                break;
            case 3:
                health_gain = 8;
                shen_fa_gain = 6;
                break;
        }
        my_status->health->add(health_gain);
        my_status->replace_buffs[BUFF_SHEN_FA]->add(shen_fa_gain + my_status->replace_buffs[BUFF_QI_SHI]->getValue() * 2);
        return 0;
    }
};

/*
双方各加4/6/8层内伤，自身每有2层负面状态加1灵气和1生命
*/
class Card_dx_hsq_xiuluohou : public BaseCard {
public:
    Card_dx_hsq_xiuluohou(int level, int position) : BaseCard(level, position) {
        card_name = "修罗吼";
        is_attacking = false;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        int temp_debuff = 0;
        switch (level) {
            case 1:
                temp_debuff = 4;
                break;
            case 2:
                temp_debuff = 6;
                break;
            case 3:
                temp_debuff = 8;
                break;
        }
        my_status->replace_debuffs[DEBUFF_NEI_SHANG]->add(temp_debuff);
        enemy_status->replace_debuffs[DEBUFF_NEI_SHANG]->add(temp_debuff);
        int debuff_total = DebuffTotal(my_status);
        int temp_ling_qi = debuff_total / 2;
        int temp_health = debuff_total / 2;
        my_status->ling_qi->add(temp_ling_qi);
        my_status->health->add(temp_health);
        return 0;
    }
};

/*
防+8/10/12，气势上限+3/4/5，气势+3/4/5
*/
class Card_dx_hsq_weizhensifang : public BaseCard {
public:
    Card_dx_hsq_weizhensifang(int level, int position) : BaseCard(level, position) {
        card_name = "威震四方";
        is_attacking = false;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        int defence = 0;
        int qi_shi_max_gain = 0;
        int qi_shi_gain = 0;
        switch (level) {
            case 1:
                defence = 8;
                qi_shi_max_gain = 3;
                qi_shi_gain = 3;
                break;
            case 2:
                defence = 10;
                qi_shi_max_gain = 4;
                qi_shi_gain = 4;
                break;
            case 3:
                defence = 12;
                qi_shi_max_gain = 5;
                qi_shi_gain = 5;
                break;
        }
        my_status->defense->add(defence);
        my_status->replace_buffs[BUFF_QI_SHI_MAX]->add(qi_shi_max_gain);
        my_status->replace_buffs[BUFF_QI_SHI]->add(qi_shi_gain);
        return 0;
    }
};

/*
耗1灵气，向对方施加自身已有的负面状态各2层，10/15/20攻（攻击时自身负面状态的效果当作气势）
*/
class Card_dx_hsq_xuanxinzhanpo : public BaseCard {
public:
    Card_dx_hsq_xuanxinzhanpo(int level, int position) : BaseCard(level, position) {
        card_name = "玄心斩魄";
        ling_qi_cost = 1;
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 8;
                break;
            case 2:
                attack = 14;
                break;
            case 3:
                attack = 20;
                break;
        }
    }
    int Effect(Status* my_status, Status* enemy_status) {
        for (int debuff_type = 0; debuff_type < DEBUFF_END_INDEX; debuff_type++) {
            if (my_status->replace_debuffs[debuff_type]->getValue() > 0) {
                enemy_status->replace_debuffs[debuff_type]->add(2);
            }
        }
        // 将debuff的值暂时转移到新的数组，并累加到临时气势上，气势上限临时调整
        int temp_qi_shi = 0;
        int temp_qi_shi_max = 9999;
        int saved_qi_shi_max = my_status->replace_buffs[BUFF_QI_SHI_MAX]->getValue(); // 保存原来的气势上限
        my_status->replace_buffs[BUFF_QI_SHI_MAX]->setValue(temp_qi_shi_max);
        // 保存原来的气势上限
        int saved_debuffs[DEBUFF_END_INDEX];
        for (int debuff_type = 0; debuff_type < DEBUFF_END_INDEX; debuff_type++) {
            saved_debuffs[debuff_type] = my_status->replace_debuffs[debuff_type]->getValue();
            temp_qi_shi += saved_debuffs[debuff_type];
            my_status->replace_debuffs[debuff_type]->setValue(0);
        }
        my_status->replace_buffs[BUFF_QI_SHI]->add(temp_qi_shi);
        Attack(my_status, enemy_status, attack, card_sp_attr);
        // 将debuff的值从新的数组转回到原来的数组
        for (int debuff_type = 0; debuff_type < DEBUFF_END_INDEX; debuff_type++) {
            my_status->replace_debuffs[debuff_type]->setValue(saved_debuffs[debuff_type]);
        }
        my_status->replace_buffs[BUFF_QI_SHI]->sub(temp_qi_shi);
        my_status->replace_buffs[BUFF_QI_SHI_MAX]->setValue(saved_qi_shi_max);
        return 0;
    }
};

/*
2/4/6攻（本轮战斗每加过4/3/2体魄多1攻），每有25体魄追加1次攻击
*/
class Card_dx_hsq_baishapojingzhang : public BaseCard {
public:
    Card_dx_hsq_baishapojingzhang(int level, int position) : BaseCard(level, position) {
        card_name = "百杀破境掌";
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 2;
                break;
            case 2:
                attack = 4;
                break;
            case 3:
                attack = 6;
                break;
        }
        card_tag[TI_PO_CARD] = true;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        int temp_attack = 0;
        switch (level) {
            case 1:
                temp_attack = my_status->ti_po_add_total->getValue() / 4;
                break;
            case 2:
                temp_attack = my_status->ti_po_add_total->getValue() / 3;
                break;
            case 3:
                temp_attack = my_status->ti_po_add_total->getValue() / 2;
                break;
        }
        int ex_attack_times = my_status->ti_po->getValue() / 25;
        Attack(my_status, enemy_status, attack + temp_attack, card_sp_attr);
        for (int i = 0; i < ex_attack_times; i++) {
            Attack(my_status, enemy_status, attack + temp_attack, card_sp_attr);
        }
        return 0;
    }
};

/*
4/8/12攻，体魄+3/4/5，体魄≥50：获得1层加攻。体魄≥65：身法+4/5/6
*/
class Card_dx_hsq_duanshenkaihai : public BaseCard {
public:
    Card_dx_hsq_duanshenkaihai(int level, int position) : BaseCard(level, position) {
        card_name = "锻神开海";
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 4;
                break;
            case 2:
                attack = 8;
                break;
            case 3:
                attack = 12;
                break;
        }
        card_tag[TI_PO_CARD] = true;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        my_status->ti_po->add(level + 2);
        if (my_status->ti_po->getValue() >= 50) {
            my_status->replace_buffs[BUFF_JIA_GONG]->add(1);
        }
        if (my_status->ti_po->getValue() >= 65) {
            my_status->replace_buffs[BUFF_SHEN_FA]->add(level + 4);
        }
        return 0;
    }
};

class Card_dx_hsq_bengquan_jingchu : public BaseCard {
public:
    Card_dx_hsq_bengquan_jingchu(int level, int position) : BaseCard(level, position) {
        card_name = "崩拳·惊触";
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 10;
                break;
            case 2:
                attack = 16;
                break;
            case 3:
                attack = 22;
                break;
        }
        is_health_cost = true;
        health_cost = 8;
        card_tag[BENG_QUAN_CARD] = true;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        my_status->task_quene_before_effect->addTask(
            [my_status](BaseCard* card){
                my_status->task_quene_after_effect->addTask(
                    [my_status](BaseCard* card){
                        int ex_attack = 1 + int(float(my_status->health_sub_total->getValue()) / 4);
                        Attack(my_status, my_status, ex_attack);
                    },
                    [](BaseCard* card){ return true; },
                    [](BaseCard* card){ return true; }
                );
            },
            [](BaseCard* card){ return card->card_tag[BENG_QUAN_CARD] ? true : false; },
            [](BaseCard* card){ return true; },
            REMARK_BENG_QUAN
        );
        return 0;
    }
};

class Card_dx_hsq_bengquan_shanji : public BaseCard {
public:
    Card_dx_hsq_bengquan_shanji(int level, int position) : BaseCard(level, position) {
        card_name = "崩拳·闪击";
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
        is_health_cost = true;
        health_cost = 7;
        card_tag[BENG_QUAN_CARD] = true;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        int temp_status = 0;
        switch (level) {
            case 1:
                temp_status = 7;
                break;
            case 2:
                temp_status = 8;
                break;
            case 3:
                temp_status = 9;
                break;
        }
        my_status->replace_buffs[BUFF_SHEN_FA]->add(temp_status);
        my_status->task_quene_before_effect->addTask(
            [my_status, temp_status](BaseCard* card){
                my_status->replace_buffs[BUFF_SHEN_FA]->add(temp_status);
            },
            [](BaseCard* card){ return card->card_tag[BENG_QUAN_CARD] ? true : false; },
            [](BaseCard* card){ return true; },
            REMARK_BENG_QUAN
        );
        return 0;
    }
};


// BaseCard* dx_hsq_create(int card_serial_number, int level, int position) {
//     switch (card_serial_number) {
//         case 1:
//             return new Card_dx_hsq_tiandihaodang(level, position);
//         case 2:
//             return new Card_dx_hsq_xiuluohou(level, position);
//         case 3:
//             return new Card_dx_hsq_weizhensifang(level, position);
//         case 4:
//             return new Card_dx_hsq_xuanxinzhanpo(level, position);
//         case 5:
//             return new Card_dx_hsq_baishapojingzhang(level, position);
//         case 6:
//             return new Card_dx_hsq_duanshenkaihai(level, position);
//         case 7:
//             return new Card_dx_hsq_bengquan_jingchu(level, position);
//         case 8:
//             return new Card_dx_hsq_bengquan_shanji(level, position);
//         default:
//             throw std::invalid_argument("Invalid card type");
//     }
// }

#endif // DX_HSQ_H