#include "zsxm_hsq.h"

// 定义文件内所有牌的变量
#define FILE_CARDS_SOVJ "专属仙命"
#define FILE_CARDS_REALM REALM_HSQ
// 该文件中的牌不注册门派副职和境界

const std::string Card_zsxm_hsq_mingyuechanguang::name = "冥月蟾光";
bool Card_zsxm_hsq_mingyuechanguang::registered = BaseCard::registerCard(Card_zsxm_hsq_mingyuechanguang::name, Card_zsxm_hsq_mingyuechanguang::create);

/*
锻玄宗_叶冥冥 专属仙命卡 冥月蟾光
！！目前未知升级效果
体魄+1/2/3，冥+2/3/4，身法+10/11/12
*/
Card_zsxm_hsq_mingyuechanguang::Card_zsxm_hsq_mingyuechanguang(int level, int position) : BaseCard(level, position) {
    sovj = FILE_CARDS_SOVJ;
    realm = FILE_CARDS_REALM;
    card_name = "冥月蟾光";
    is_attacking = false;
    card_tag[TI_PO_CARD] = true;
}

Card_zsxm_hsq_mingyuechanguang::Card_zsxm_hsq_mingyuechanguang(const Card_zsxm_hsq_mingyuechanguang& other) : BaseCard(other) {}

Card_zsxm_hsq_mingyuechanguang* Card_zsxm_hsq_mingyuechanguang::Clone() const {
    return new Card_zsxm_hsq_mingyuechanguang(*this);
}

int Card_zsxm_hsq_mingyuechanguang::Effect(Status* my_status, Status* enemy_status) {
    int ti_po_gain = level;
    int ming_gain = 1 + level;
    int shen_fa_gain = 9 + level;
    my_status->ti_po->add(ti_po_gain);
    my_status->debuffs[DEBUFF_MING]->add(ming_gain);
    my_status->buffs[BUFF_SHEN_FA]->add(shen_fa_gain);
    return 0;
}

BaseCard* Card_zsxm_hsq_mingyuechanguang::create(int level, int position) {
    return new Card_zsxm_hsq_mingyuechanguang(level, position);
}