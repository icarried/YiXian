#include "status.h"
#include "deck.h"
#include "head.h"

/*
实现：获取Deck中position位置的卡牌指针
*/
BaseCard* Status::GetCard(int position) {
    return deck->GetCard(position);
}

// 一次攻击结算后，结算BUFF变更
void Status::attack_change() {
    if (this->replace_buffs[BUFF_GONG_JI_WU_SHI_FANG_YU]->getValue() > 0)
        this->replace_buffs[BUFF_GONG_JI_WU_SHI_FANG_YU]->sub(1);
}

// 一次卡牌结算后，结算BUFF变更
void Status::a_card_change() {
    if (is_card_attacked) {
        if (this->replace_buffs[BUFF_JIAN_YI]->getValue() > 0)
            this->replace_buffs[BUFF_JIAN_YI]->sub(1);
    }
    else {
        is_card_attacked = false;
    }
}

// 一次伤害结算后，结算BUFF变更
void Status::a_damage_change(bool attacking, bool hurting) {
    if (attacking) {
        is_card_attacked = true;
        if (this->replace_buffs[BUFF_QI_SHI]->getValue() < 0)
            this->replace_buffs[BUFF_QI_SHI]->setValue(0);
        if (hurting) {
            if (this->replace_buffs[BUFF_FENG_RUI]->getValue() > 0)
                this->replace_buffs[BUFF_FENG_RUI]->sub(1);
        }
    }
}

// 一方回合结束后，结算该方BUFF变更
void Status::a_side_round_change() {
    if (this->replace_debuffs[DEBUFF_PO_ZHAN]->getValue() > 0)
        this->replace_debuffs[DEBUFF_PO_ZHAN]->sub(1);
    if (this->replace_debuffs[DEBUFF_XU_RUO]->getValue() > 0)
        this->replace_debuffs[DEBUFF_XU_RUO]->sub(1);
    if (this->replace_buffs[BUFF_QIAN_DUN]->getValue() > 0)
        this->replace_buffs[BUFF_QIAN_DUN]->sub(1);
    if (this->replace_buffs[BUFF_TIE_GU]->getValue() > 0)
        this->replace_buffs[BUFF_TIE_GU]->sub(1);
}