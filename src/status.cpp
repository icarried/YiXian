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
    if (this->buffs[BUFF_GONG_JI_WU_SHI_FANG_YU]->getValue() > 0)
        this->buffs[BUFF_GONG_JI_WU_SHI_FANG_YU]->sub(1);
    if (this->buffs[BUFF_QI_SHI]->getValue() > 0)
        this->buffs[BUFF_QI_SHI]->sub(1);
    is_card_attacked = true;
}

// 一次卡牌结算后，结算BUFF变更
void Status::a_action_change() {
    if (is_card_attacked) {
        if (this->buffs[BUFF_JIAN_YI]->getValue() > 0)
            this->buffs[BUFF_JIAN_YI]->sub(1);
    }
    is_card_attacked = false;
}


// 一次伤害结算后，结算BUFF变更
void Status::a_damage_change(bool attacking, bool hurting) {
    if (attacking) {
        if (hurting) {
            if (this->buffs[BUFF_FENG_RUI]->getValue() > 0)
                this->buffs[BUFF_FENG_RUI]->sub(this->buffs[BUFF_FENG_RUI]->getValue());
        }
    }
}

// 一方回合结束后，结算该方BUFF变更
void Status::a_side_round_change() {
    if (this->debuffs[DEBUFF_PO_ZHAN]->getValue() > 0)
        this->debuffs[DEBUFF_PO_ZHAN]->sub(1);
    if (this->debuffs[DEBUFF_XU_RUO]->getValue() > 0)
        this->debuffs[DEBUFF_XU_RUO]->sub(1);
    if (this->buffs[BUFF_QIAN_DUN]->getValue() > 0)
        this->buffs[BUFF_QIAN_DUN]->sub(1);
    if (this->buffs[BUFF_TIE_GU]->getValue() > 0)
        this->buffs[BUFF_TIE_GU]->sub(1);
}

/*
输入为当前位置，返回前一格位置
*/
int Status::PreviousCardPosition(int position, bool skip_unusable) {
    do {
        position--;
        if (position < 0) {
            position = this->deck->opened_card_end_index - 1;
        }
    } while (skip_unusable && !is_usable[position]);
    return position;
}

/*
输入为当前位置，返回后一格位置
*/
int Status::NextCardPosition(int position, bool skip_unusable) {
    do {
        position++;
        if (position >= this->deck->opened_card_end_index) {
            position = 0;
        }
    } while (skip_unusable && !is_usable[position]);
    return position;
}

/*
切换到上一张卡牌位置
如果牌已被消耗，则跳过
*/
void Status::ToPreviousCardPosition(){
    do {
        this->using_card_position--;
        if (this->using_card_position < 0) {
            this->using_card_position = this->deck->opened_card_end_index - 1;
        }
    } while (!is_usable[this->using_card_position]);
}

/*
切换到下一张卡牌位置
如果牌已被消耗，则跳过
*/
void Status::ToNextCardPosition(){
    do {
        this->using_card_position++;
        if (this->using_card_position >= this->deck->opened_card_end_index) {
            this->using_card_position = 0;
        }
    } while (!is_usable[this->using_card_position]);
}