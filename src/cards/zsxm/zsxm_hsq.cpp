#include "zsxm_hsq.h"

const std::string Card_zsxm_hsq_mingyuechanguang::name = "冥月蟾光";
bool Card_zsxm_hsq_mingyuechanguang::registered = BaseCard::registerCard(Card_zsxm_hsq_mingyuechanguang::name, Card_zsxm_hsq_mingyuechanguang::create);

/*
锻玄宗_叶冥冥 专属仙命卡 冥月蟾光
！！目前未知升级效果
体魄+2，冥+2，身法+10
*/
Card_zsxm_hsq_mingyuechanguang::Card_zsxm_hsq_mingyuechanguang(int level, int position) : BaseCard(level, position) {
    card_name = "冥月蟾光";
    is_attacking = false;
    card_tag[TI_PO_CARD] = true;
}

Card_zsxm_hsq_mingyuechanguang::Card_zsxm_hsq_mingyuechanguang(const Card_zsxm_hsq_mingyuechanguang& other) : BaseCard(other) {}

Card_zsxm_hsq_mingyuechanguang* Card_zsxm_hsq_mingyuechanguang::Clone() const {
    return new Card_zsxm_hsq_mingyuechanguang(*this);
}

int Card_zsxm_hsq_mingyuechanguang::Effect(Status* my_status, Status* enemy_status) {
    int ti_po_gain = 2;
    int ming_gain = 2;
    int shen_fa_gain = 10;
    my_status->ti_po->add(ti_po_gain);
    my_status->debuffs[DEBUFF_MING]->add(ming_gain);
    my_status->buffs[BUFF_SHEN_FA]->add(shen_fa_gain);
    return 0;
}

BaseCard* Card_zsxm_hsq_mingyuechanguang::create(int level, int position) {
    return new Card_zsxm_hsq_mingyuechanguang(level, position);
}