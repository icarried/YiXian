#include "buffs.h"
#include "../status.h"

BuffJiaGong::BuffJiaGong(Status* linking_status, int val) : Buff(linking_status, val) {
    name = "加攻";
    id = BUFF_JIA_GONG;
}
BuffJiaGong* BuffJiaGong::Clone(Status* new_status) const {
    return new BuffJiaGong(*this, new_status);
}
BuffJiaGong::BuffJiaGong(const BuffJiaGong& other, Status* new_status) : Buff(other, new_status) {}


BuffJianYi::BuffJianYi(Status* linking_status, int val) : Buff(linking_status, val) {
    name = "剑意";
    id = BUFF_JIAN_YI;
}
BuffJianYi* BuffJianYi::Clone(Status* new_status) const {
    return new BuffJianYi(*this, new_status);
}
BuffJianYi::BuffJianYi(const BuffJianYi& other, Status* new_status) : Buff(other, new_status) {}


BuffFengRui::BuffFengRui(Status* linking_status, int val) : Buff(linking_status, val) {
    name = "锋锐";
    id = BUFF_FENG_RUI;
}
BuffFengRui* BuffFengRui::Clone(Status* new_status) const {
    return new BuffFengRui(*this, new_status);
}
BuffFengRui::BuffFengRui(const BuffFengRui& other, Status* new_status) : Buff(other, new_status) {}


BuffXingLi::BuffXingLi(Status* linking_status, int val) : Buff(linking_status, val) {
    name = "星力";
    id = BUFF_XING_LI;
}
BuffXingLi* BuffXingLi::Clone(Status* new_status) const {
    return new BuffXingLi(*this, new_status);
}
BuffXingLi::BuffXingLi(const BuffXingLi& other, Status* new_status) : Buff(other, new_status) {}


BuffQiShi::BuffQiShi(Status* linking_status, int val) : Buff(linking_status, val) {
    name = "气势";
    id = BUFF_QI_SHI;
}
BuffQiShi* BuffQiShi::Clone(Status* new_status) const {
    return new BuffQiShi(*this, new_status);
}
BuffQiShi::BuffQiShi(const BuffQiShi& other, Status* new_status) : Buff(other, new_status) {}
void BuffQiShi::add(int val) {
    // 气势超过上限部分转为防
    if (linked_status->buffs[BUFF_QI_SHI]->getValue() + val > linked_status->buffs[BUFF_QI_SHI_MAX]->getValue()) {
        int exceed_value = linked_status->buffs[BUFF_QI_SHI]->getValue() + val - linked_status->buffs[BUFF_QI_SHI_MAX]->getValue();
        val -= exceed_value;
        linked_status->defense->add(exceed_value);
        Buff::add(val);
        if (exceed_value > 0) {
            std::cout << ", " << linked_status->style << "超出部分转为" << exceed_value << "点防" << DEFAULT_STYLE;
        }
    }
    else {
        Buff::add(val);
    }
}


BuffQiShiMax::BuffQiShiMax(Status* linking_status, int val) : Buff(linking_status, val) {
    name = "气势上限";
    id = BUFF_QI_SHI_MAX;
}
BuffQiShiMax* BuffQiShiMax::Clone(Status* new_status) const {
    return new BuffQiShiMax(*this, new_status);
}
BuffQiShiMax::BuffQiShiMax(const BuffQiShiMax& other, Status* new_status) : Buff(other, new_status) {}


BuffQianDun::BuffQianDun(Status* linking_status, int val) : Buff(linking_status, val) {
    name = "潜遁";
    id = BUFF_QIAN_DUN;
}
BuffQianDun* BuffQianDun::Clone(Status* new_status) const {
    return new BuffQianDun(*this, new_status);
}
BuffQianDun::BuffQianDun(const BuffQianDun& other, Status* new_status) : Buff(other, new_status) {}


BuffTieGu::BuffTieGu(Status* linking_status, int val) : Buff(linking_status, val) {
    name = "铁骨";
    id = BUFF_TIE_GU;
}
BuffTieGu* BuffTieGu::Clone(Status* new_status) const {
    return new BuffTieGu(*this, new_status);
}
BuffTieGu::BuffTieGu(const BuffTieGu& other, Status* new_status) : Buff(other, new_status) {}


BuffBiXie::BuffBiXie(Status* linking_status, int val) : Buff(linking_status, val) {
    name = "辟邪";
    id = BUFF_BI_XIE;
}
BuffBiXie* BuffBiXie::Clone(Status* new_status) const {
    return new BuffBiXie(*this, new_status);
}
BuffBiXie::BuffBiXie(const BuffBiXie& other, Status* new_status) : Buff(other, new_status) {}


BuffShenFa::BuffShenFa(Status* linking_status, int val) : Buff(linking_status, val) {
    name = "身法";
    id = BUFF_SHEN_FA;
}
BuffShenFa* BuffShenFa::Clone(Status* new_status) const {
    return new BuffShenFa(*this, new_status);
}
BuffShenFa::BuffShenFa(const BuffShenFa& other, Status* new_status) : Buff(other, new_status) {}

BuffHuTi::BuffHuTi(Status* linking_status, int val) : Buff(linking_status, val) {
    name = "护体";
    id = BUFF_HU_TI;
}
BuffHuTi* BuffHuTi::Clone(Status* new_status) const {
    return new BuffHuTi(*this, new_status);
}
BuffHuTi::BuffHuTi(const BuffHuTi& other, Status* new_status) : Buff(other, new_status) {}


BuffGongJiWuShiFangYu::BuffGongJiWuShiFangYu(Status* linking_status, int val) : Buff(linking_status, val) {
    name = "攻击无视防御";
    id = BUFF_GONG_JI_WU_SHI_FANG_YU;
}
BuffGongJiWuShiFangYu* BuffGongJiWuShiFangYu::Clone(Status* new_status) const {
    return new BuffGongJiWuShiFangYu(*this, new_status);
}
BuffGongJiWuShiFangYu::BuffGongJiWuShiFangYu(const BuffGongJiWuShiFangYu& other, Status* new_status) : Buff(other, new_status) {}


BuffSkipCard::BuffSkipCard(Status* linking_status, int val) : Buff(linking_status, val) {
    name = "跳过牌";
    id = SKIP_CARD;
}
BuffSkipCard* BuffSkipCard::Clone(Status* new_status) const {
    return new BuffSkipCard(*this, new_status);
}
BuffSkipCard::BuffSkipCard(const BuffSkipCard& other, Status* new_status) : Buff(other, new_status) {}


BuffWuFaXingDong::BuffWuFaXingDong(Status* linking_status, int val) : Buff(linking_status, val) {
    name = "无法行动";
    id = WU_FA_XING_DONG;
}
BuffWuFaXingDong* BuffWuFaXingDong::Clone(Status* new_status) const {
    return new BuffWuFaXingDong(*this, new_status);
}
BuffWuFaXingDong::BuffWuFaXingDong(const BuffWuFaXingDong& other, Status* new_status) : Buff(other, new_status) {}


BuffDuanGuTimes::BuffDuanGuTimes(Status* linking_status, int val) : Buff(linking_status, val) {
    name = "锻骨剩余次数";
    id = DUANGU_TIMES;
}
BuffDuanGuTimes* BuffDuanGuTimes::Clone(Status* new_status) const {
    return new BuffDuanGuTimes(*this, new_status);
}
BuffDuanGuTimes::BuffDuanGuTimes(const BuffDuanGuTimes& other, Status* new_status) : Buff(other, new_status) {}


BuffQiRuoXuanHeTimes::BuffQiRuoXuanHeTimes(Status* linking_status, int val) : Buff(linking_status, val) {
    name = "气若悬河剩余次数";
    id = QIRUOXUANHE_TIMES;
}
BuffQiRuoXuanHeTimes* BuffQiRuoXuanHeTimes::Clone(Status* new_status) const {
    return new BuffQiRuoXuanHeTimes(*this, new_status);
}
BuffQiRuoXuanHeTimes::BuffQiRuoXuanHeTimes(const BuffQiRuoXuanHeTimes& other, Status* new_status) : Buff(other, new_status) {}

Buff* buff_create(int id, Status* linking_status, int val) {
    switch (id) {
        case BUFF_JIA_GONG:
            return new BuffJiaGong(linking_status, val);
        case BUFF_JIAN_YI:
            return new BuffJianYi(linking_status, val);
        case BUFF_FENG_RUI:
            return new BuffFengRui(linking_status, val);
        case BUFF_XING_LI:
            return new BuffXingLi(linking_status, val);
        case BUFF_QI_SHI:
            return new BuffQiShi(linking_status, val);
        case BUFF_QI_SHI_MAX:
            return new BuffQiShiMax(linking_status, val);
        case BUFF_QIAN_DUN:
            return new BuffQianDun(linking_status, val);
        case BUFF_TIE_GU:
            return new BuffTieGu(linking_status, val);
        case BUFF_BI_XIE:
            return new BuffBiXie(linking_status, val);
        case BUFF_SHEN_FA:
            return new BuffShenFa(linking_status, val);
        case BUFF_HU_TI:
            return new BuffHuTi(linking_status, val);
        case BUFF_GONG_JI_WU_SHI_FANG_YU:
            return new BuffGongJiWuShiFangYu(linking_status, val);
        case SKIP_CARD:
            return new BuffSkipCard(linking_status, val);
        case WU_FA_XING_DONG:
            return new BuffWuFaXingDong(linking_status, val);
        case DUANGU_TIMES:
            return new BuffDuanGuTimes(linking_status, val);
        case QIRUOXUANHE_TIMES:
            return new BuffQiRuoXuanHeTimes(linking_status, val);
        default:
            return nullptr;
    }
}
