#include "zsxm_jdq.h"

// 定义文件内所有牌的变量
#define FILE_CARDS_SOVJ "专属仙命"
#define FILE_CARDS_REALM REALM_JDQ
// 该文件中的牌不注册门派副职和境界

const std::string Card_zsxm_jdq_fengmo::name = "疯魔";
bool Card_zsxm_jdq_fengmo::registered = BaseCard::registerCard(Card_zsxm_jdq_fengmo::name, Card_zsxm_jdq_fengmo::create);

/*
锻玄宗_叶冥冥 专属仙命卡 疯魔
！！目前未知升级效果
获得2/4/6层"冥"和2/1/0层随机负面状态，体魄+1（每有1层负面状态多加1）
*/
Card_zsxm_jdq_fengmo::Card_zsxm_jdq_fengmo(int level, int position) : BaseCard(level, position) {
    sovj = FILE_CARDS_SOVJ;
    realm = FILE_CARDS_REALM;
    card_name = "疯魔";
    is_attacking = false;
    card_tag[TI_PO_CARD] = true;
}

Card_zsxm_jdq_fengmo::Card_zsxm_jdq_fengmo(const Card_zsxm_jdq_fengmo& other) : BaseCard(other) {}

Card_zsxm_jdq_fengmo* Card_zsxm_jdq_fengmo::Clone() const {
    return new Card_zsxm_jdq_fengmo(*this);
}

int Card_zsxm_jdq_fengmo::Effect(Status* my_status, Status* enemy_status) {
    int ming_gain = 2 * level;
    int ti_po_gain = 1;
    int random_debuff_gain = 3 - level;
    my_status->debuffs[DEBUFF_MING]->add(ming_gain);
    if (random_debuff_gain > 0)
        DebuffRandomAdd(my_status, random_debuff_gain);
    ti_po_gain += DebuffTotal(my_status);
    my_status->ti_po->add(ti_po_gain);
    return 0;
}

BaseCard* Card_zsxm_jdq_fengmo::create(int level, int position) {
    return new Card_zsxm_jdq_fengmo(level, position);
}