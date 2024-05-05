#ifndef DX_JDQ_H
#define DX_JDQ_H
#include "../base_card.h"

// 锻玄宗_金丹期


/*
耗2生命，最多耗2灵气：每点加1气势，且此牌多3攻。10/11/12攻
*/
class Card_dx_jdq_shirupozhu : public BaseCard {
public:
    Card_dx_jdq_shirupozhu(int level, int position) : BaseCard(level, position) {
        card_name = "势如破竹";
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
        health_cost = 2;
        ling_qi_cost = 2;
    }
    Card_dx_jdq_shirupozhu* Clone() const {
        return new Card_dx_jdq_shirupozhu(*this);
    }
    Card_dx_jdq_shirupozhu(const Card_dx_jdq_shirupozhu& other) : BaseCard(other) {}
    int Effect(Status* my_status, Status* enemy_status) {
        int temp_status = LingQiCostMax(my_status, 2);
        my_status->buffs[BUFF_QI_SHI]->add(temp_status);
        Attack(my_status, enemy_status, attack + 3 * temp_status, card_sp_attr);
        return 0;
    }
};

/*
耗1灵气，气势+3/4/5，身法+6
*/
class Card_dx_jdq_tapojiuxiao : public BaseCard {
public:
    Card_dx_jdq_tapojiuxiao(int level, int position) : BaseCard(level, position) {
        card_name = "踏破九霄";
        is_attacking = false;
    }
    Card_dx_jdq_tapojiuxiao* Clone() const {
        return new Card_dx_jdq_tapojiuxiao(*this);
    }
    Card_dx_jdq_tapojiuxiao(const Card_dx_jdq_tapojiuxiao& other) : BaseCard(other) {}
    int Effect(Status* my_status, Status* enemy_status) {
        int temp_status = 0;
        switch (level) {
            case 1:
                temp_status = 3;
                break;
            case 2:
                temp_status = 4;
                break;
            case 3:
                temp_status = 5;
                break;
        }
        my_status->buffs[BUFF_QI_SHI]->add(temp_status);
        my_status->buffs[BUFF_SHEN_FA]->add(6);
        return 0;
    }
};

/*
灵气+2/3/4，气势+1，自身下2/3/4次攻击时先加1气势
*/
class Card_dx_jdq_qiruoxuanhe : public BaseCard {
public:
    Card_dx_jdq_qiruoxuanhe(int level, int position) : BaseCard(level, position) {
        card_name = "气若悬河";
        is_attacking = false;
    }
    Card_dx_jdq_qiruoxuanhe* Clone() const {
        return new Card_dx_jdq_qiruoxuanhe(*this);
    }
    Card_dx_jdq_qiruoxuanhe(const Card_dx_jdq_qiruoxuanhe& other) : BaseCard(other) {}
    int Effect(Status* my_status, Status* enemy_status) {
        int ling_qi_gain = 0;
        int temp_status = 0;
        switch (level) {
            case 1:
                ling_qi_gain = 2;
                temp_status = 2;
                break;
            case 2:
                ling_qi_gain = 3;
                temp_status = 3;
                break;
            case 3:
                ling_qi_gain = 4;
                temp_status = 4;
                break;
        }
        my_status->buffs[QIRUOXUANHE_TIMES]->add(temp_status);
        my_status->ling_qi->add(ling_qi_gain);
        my_status->buffs[BUFF_QI_SHI]->add(1);
        my_status->task_quene_before_effect->addTask(
            [my_status](BaseCard* card){
                my_status->buffs[BUFF_QI_SHI]->add(1);
            },
            [my_status](BaseCard* card){ return my_status->buffs[QIRUOXUANHE_TIMES]->getValue() > 0 && card->is_attacking ? true : false; },
            [my_status](BaseCard* card){ return my_status->buffs[QIRUOXUANHE_TIMES]->getValue() == 0 ? true : false; }
        );
        return 0;
    }
};

/*
耗1灵气，双方各加1/2/2层内伤和1/2/2层外伤，6/7/8攻×2
*/
class Card_dx_jdq_shuangguipaimeng : public BaseCard {
public:
    Card_dx_jdq_shuangguipaimeng(int level, int position) : BaseCard(level, position) {
        card_name = "双鬼拍门";
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 6;
                break;
            case 2:
                attack = 7;
                break;
            case 3:
                attack = 8;
                break;
        }
    }
    Card_dx_jdq_shuangguipaimeng* Clone() const {
        return new Card_dx_jdq_shuangguipaimeng(*this);
    }
    Card_dx_jdq_shuangguipaimeng(const Card_dx_jdq_shuangguipaimeng& other) : BaseCard(other) {}
    int Effect(Status* my_status, Status* enemy_status) {
        int temp_status = 0;
        switch (level) {
            case 1:
                temp_status = 1;
                break;
            case 2:
                temp_status = 2;
                break;
            case 3:
                temp_status = 2;
                break;
        }
        my_status->debuffs[DEBUFF_NEI_SHANG]->add(temp_status);
        my_status->debuffs[DEBUFF_WAI_SHANG]->add(temp_status);
        enemy_status->debuffs[DEBUFF_NEI_SHANG]->add(temp_status);
        enemy_status->debuffs[DEBUFF_WAI_SHANG]->add(temp_status);
        Attack(my_status, enemy_status, attack, card_sp_attr);
        Attack(my_status, enemy_status, attack, card_sp_attr);
        return 0;
    }
};

/*
耗4灵气，自身每有1层负面状态，此牌少耗1灵气，20/24/28攻
*/
class Card_dx_jdq_ehupushi : public BaseCard {
public:
    Card_dx_jdq_ehupushi(int level, int position) : BaseCard(level, position) {
        card_name = "恶虎扑食";
        ling_qi_cost = 4;
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 18;
                break;
            case 2:
                attack = 22;
                break;
            case 3:
                attack = 26;
                break;
        }
        is_ling_qi_cost_modifiable = true;
    }
    Card_dx_jdq_ehupushi* Clone() const {
        return new Card_dx_jdq_ehupushi(*this);
    }
    Card_dx_jdq_ehupushi(const Card_dx_jdq_ehupushi& other) : BaseCard(other) {}
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        return 0;
    }
    int LingQiCostModify(Status* my_status, Status* enemy_status) {
        int temp_ling_qi_cost = ling_qi_cost - DebuffTotal(my_status);
        temp_ling_qi_cost = temp_ling_qi_cost < 0 ? 0 : temp_ling_qi_cost;
        return temp_ling_qi_cost;
    }
};

/*
4/5/6攻×2，每有6体魄多1攻（上限3/5/7）
*/
class Card_dx_jdq_yingfengzhang : public BaseCard {
public:
    Card_dx_jdq_yingfengzhang(int level, int position) : BaseCard(level, position) {
        card_name = "迎风掌";
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 4;
                break;
            case 2:
                attack = 5;
                break;
            case 3:
                attack = 6;
                break;
        }
    }
    Card_dx_jdq_yingfengzhang* Clone() const {
        return new Card_dx_jdq_yingfengzhang(*this);
    }
    Card_dx_jdq_yingfengzhang(const Card_dx_jdq_yingfengzhang& other) : BaseCard(other) {}
    int Effect(Status* my_status, Status* enemy_status) {
        int temp_max = 0;
        switch (level) {
            case 1:
                temp_max = 3;
                break;
            case 2:
                temp_max = 5;
                break;
            case 3:
                temp_max = 7;
                break;
        }
        int temp_attack = my_status->ti_po->getValue() / 6;
        temp_attack = temp_attack > temp_max ? temp_max : temp_attack;
        Attack(my_status, enemy_status, attack + temp_attack, card_sp_attr);
        Attack(my_status, enemy_status, attack + temp_attack, card_sp_attr);
        return 0;
    }
};

/*
体魄+3，自身加2/3/4层困缚，防+8/11/14（每有1层负面状态多1）
*/
class Card_dx_jdq_hezhongqianxing : public BaseCard {
public:
    Card_dx_jdq_hezhongqianxing(int level, int position) : BaseCard(level, position) {
        card_name = "荷重前行";
        is_attacking = false;
        card_tag[TI_PO_CARD] = true;
    }
    Card_dx_jdq_hezhongqianxing* Clone() const {
        return new Card_dx_jdq_hezhongqianxing(*this);
    }
    Card_dx_jdq_hezhongqianxing(const Card_dx_jdq_hezhongqianxing& other) : BaseCard(other) {}
    int Effect(Status* my_status, Status* enemy_status) {
        my_status->ti_po->add(3);
        int defence_gain = 0;
        int kun_fu_gain = 0;
        switch (level) {
            case 1:
                defence_gain = 8;
                kun_fu_gain = 2;
                break;
            case 2:
                defence_gain = 11;
                kun_fu_gain = 3;
                break;
            case 3:
                defence_gain = 14;
                kun_fu_gain = 4;
                break;
        }
        my_status->debuffs[DEBUFF_KUN_FU]->add(kun_fu_gain);
        defence_gain += DebuffTotal(my_status);
        my_status->defense->add(defence_gain);
        return 0;
    }
};

/*
体魄+1，生命+3/4/5，下2/3/4次攻击时多3攻并加1体魄
*/
class Card_dx_jdq_duangu : public BaseCard {
public:
    Card_dx_jdq_duangu(int level, int position) : BaseCard(level, position) {
        card_name = "锻骨";
        is_attacking = false;
        card_tag[TI_PO_CARD] = true;
    }
    Card_dx_jdq_duangu* Clone() const {
        return new Card_dx_jdq_duangu(*this);
    }
    Card_dx_jdq_duangu(const Card_dx_jdq_duangu& other) : BaseCard(other) {}
    int Effect(Status* my_status, Status* enemy_status) {
        my_status->ti_po->add(1);
        int health_gain = 0;
        int temp_status = 0;
        switch (level) {
            case 1:
                health_gain = 3;
                temp_status = 2;
                break;
            case 2:
                health_gain = 4;
                temp_status = 3;
                break;
            case 3:
                health_gain = 5;
                temp_status = 4;
                break;
        }
        my_status->buffs[DUANGU_TIMES]->add(temp_status);
        my_status->health->add(health_gain);
        my_status->task_quene_before_effect->addTask(
            [my_status](BaseCard* card){
                my_status->buffs[DUANGU_TIMES]->sub(1);
                my_status->ti_po->add(1);
                card->card_sp_attr[CARD_SP_ATTR_DUO_GONG] += 3;
                my_status->task_quene_after_effect->addTask(
                    [my_status](BaseCard* card){
                        card->card_sp_attr[CARD_SP_ATTR_DUO_GONG] -= 3;
                    },
                    [](BaseCard* card){ return true; },
                    [](BaseCard* card){ return true; }
                );
            },
            [my_status](BaseCard* card){ return my_status->buffs[DUANGU_TIMES]->getValue() > 0 && card->is_attacking ? true : false; },
            [my_status](BaseCard* card){ return my_status->buffs[DUANGU_TIMES]->getValue() == 0 ? true : false; }
        );
        return 0;
    }
};

/*
耗5生命，10/12/14攻，使用下一张崩拳时加5/7/9防并多5/7/9攻
*/
class Card_dx_jdq_bengquan_xianglong : public BaseCard {
public:
    Card_dx_jdq_bengquan_xianglong(int level, int position) : BaseCard(level, position) {
        card_name = "崩拳·降龙";
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
        is_health_cost = true;
        health_cost = 5;
        card_tag[BENG_QUAN_CARD] = true;
    }
    Card_dx_jdq_bengquan_xianglong* Clone() const {
        return new Card_dx_jdq_bengquan_xianglong(*this);
    }
    Card_dx_jdq_bengquan_xianglong(const Card_dx_jdq_bengquan_xianglong& other) : BaseCard(other) {}
    int Effect(Status* my_status, Status* enemy_status) {
        Attack(my_status, enemy_status, attack, card_sp_attr);
        int temp_status = 0;
        switch (level) {
            case 1:
                temp_status = 5;
                break;
            case 2:
                temp_status = 7;
                break;
            case 3:
                temp_status = 9;
                break;
        }
        my_status->task_quene_before_effect->addTask(
            [my_status, temp_status](BaseCard* card){
                my_status->defense->add(temp_status);
                card->card_sp_attr[CARD_SP_ATTR_DUO_GONG] += temp_status;
                my_status->task_quene_after_effect->addTask(
                    [my_status, temp_status](BaseCard* card){
                        card->card_sp_attr[CARD_SP_ATTR_DUO_GONG] -= temp_status;
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

/*
耗4生命，随机转移自身1层负面状态给对手（下一张崩拳也附加此效果），9/13/17攻
*/
class Card_dx_jdq_bengquan_jiemai : public BaseCard {
public:
    Card_dx_jdq_bengquan_jiemai(int level, int position) : BaseCard(level, position) {
        card_name = "崩拳·截脉";
        is_attacking = true;
        switch (level) {
            case 1:
                attack = 9;
                break;
            case 2:
                attack = 13;
                break;
            case 3:
                attack = 17;
                break;
        }
        is_health_cost = true;
        health_cost = 4;
        card_tag[BENG_QUAN_CARD] = true;
    }
    Card_dx_jdq_bengquan_jiemai* Clone() const {
        return new Card_dx_jdq_bengquan_jiemai(*this);
    }
    Card_dx_jdq_bengquan_jiemai(const Card_dx_jdq_bengquan_jiemai& other) : BaseCard(other) {}
    int Effect(Status* my_status, Status* enemy_status) {
        DebuffRandomReduce(my_status, 1, true, enemy_status);
        Attack(my_status, enemy_status, attack, card_sp_attr);
        my_status->task_quene_before_effect->addTask(
            [my_status, enemy_status](BaseCard* card){
                DebuffRandomReduce(my_status, 1, true, enemy_status);
            },
            [](BaseCard* card){ return card->card_tag[BENG_QUAN_CARD] ? true : false; },
            [](BaseCard* card){ return true; },
            REMARK_BENG_QUAN
        );
        return 0;
    }
};

/*
灵气+1/2/3，身法+4，持续：所有牌都可算作“崩拳”
*/
class Card_dx_jdq_bengtianbu : public BaseCard {
public:
    Card_dx_jdq_bengtianbu(int level, int position) : BaseCard(level, position) {
        card_name = "崩天步";
        is_attacking = false;
        card_tag[CHI_XU_CARD] = true;
    }
    Card_dx_jdq_bengtianbu* Clone() const {
        return new Card_dx_jdq_bengtianbu(*this);
    }
    Card_dx_jdq_bengtianbu(const Card_dx_jdq_bengtianbu& other) : BaseCard(other) {}
    int Effect(Status* my_status, Status* enemy_status) {
        int ling_qi_gain = 0;
        switch (level) {
            case 1:
                ling_qi_gain = 1;
                break;
            case 2:
                ling_qi_gain = 2;
                break;
            case 3:
                ling_qi_gain = 3;
                break;
        }
        my_status->ling_qi->add(ling_qi_gain);
        my_status->buffs[BUFF_SHEN_FA]->add(4);
        my_status->task_quene_before_effect->addTask(
            [my_status](BaseCard* card){
                card->card_tag[BENG_QUAN_CARD] = 1;
            },
            [](BaseCard* card){ return true; },
            [](BaseCard* card){ return false; }
        );
        return 0;
    }
};


// BaseCard* dx_jdq_create(int card_serial_number, int level, int position) {
//     switch (card_serial_number) {
//         case 1:
//             return new Card_dx_jdq_shirupozhu(level, position);
//             break;
//         case 2:
//             return new Card_dx_jdq_tapojiuxiao(level, position);
//             break;
//         case 3:
//             return new Card_dx_jdq_qiruoxuanhe(level, position);
//             break;
//         case 4:
//             return new Card_dx_jdq_shuangguipaimeng(level, position);
//             break;
//         case 5:
//             return new Card_dx_jdq_ehupushi(level, position);
//             break;
//         case 6:
//             return new Card_dx_jdq_yingfengzhang(level, position);
//             break;
//         case 7:
//             return new Card_dx_jdq_hezhongqianxing(level, position);
//             break;
//         case 8:
//             return new Card_dx_jdq_duangu(level, position);
//             break;
//         case 9:
//             return new Card_dx_jdq_bengquan_xianglong(level, position);
//             break;
//         case 10:
//             return new Card_dx_jdq_bengquan_jiemai(level, position);
//             break;
//         case 11:
//             return new Card_dx_jdq_bengtianbu(level, position);
//             break;
//         default:
//             throw std::invalid_argument("Invalid type");
//     }
// }


#endif // DX_JDQ_H