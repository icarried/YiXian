#include "debuffs.h"
#include "../status.h"

DebuffPoZhan::DebuffPoZhan(Status* linking_status, int val) : Debuff(linking_status, val) {
    name = "破绽";
    id = DEBUFF_PO_ZHAN;
}
DebuffPoZhan* DebuffPoZhan::Clone(Status* new_status) const {
    return new DebuffPoZhan(*this, new_status);
}
DebuffPoZhan::DebuffPoZhan(const DebuffPoZhan& other, Status* new_status) : Debuff(other, new_status) {}


DebuffWaiShang::DebuffWaiShang(Status* linking_status, int val) : Debuff(linking_status, val) {
    name = "外伤";
    id = DEBUFF_WAI_SHANG;
}
DebuffWaiShang* DebuffWaiShang::Clone(Status* new_status) const {
    return new DebuffWaiShang(*this, new_status);
}
DebuffWaiShang::DebuffWaiShang(const DebuffWaiShang& other, Status* new_status) : Debuff(other, new_status) {}


DebuffJianGong::DebuffJianGong(Status* linking_status, int val) : Debuff(linking_status, val) {
    name = "减攻";
    id = DEBUFF_JIAN_GONG;
}
DebuffJianGong* DebuffJianGong::Clone(Status* new_status) const {
    return new DebuffJianGong(*this, new_status);
}
DebuffJianGong::DebuffJianGong(const DebuffJianGong& other, Status* new_status) : Debuff(other, new_status) {}


DebuffXuRuo::DebuffXuRuo(Status* linking_status, int val) : Debuff(linking_status, val) {
    name = "虚弱";
    id = DEBUFF_XU_RUO;
}
DebuffXuRuo* DebuffXuRuo::Clone(Status* new_status) const {
    return new DebuffXuRuo(*this, new_status);
}
DebuffXuRuo::DebuffXuRuo(const DebuffXuRuo& other, Status* new_status) : Debuff(other, new_status) {}


DebuffNeiShang::DebuffNeiShang(Status* linking_status, int val) : Debuff(linking_status, val) {
    name = "内伤";
    id = DEBUFF_NEI_SHANG;
}
DebuffNeiShang* DebuffNeiShang::Clone(Status* new_status) const {
    return new DebuffNeiShang(*this, new_status);
}
DebuffNeiShang::DebuffNeiShang(const DebuffNeiShang& other, Status* new_status) : Debuff(other, new_status) {}


DebuffKunFu::DebuffKunFu(Status* linking_status, int val) : Debuff(linking_status, val) {
    name = "困缚";
    id = DEBUFF_KUN_FU;
}
DebuffKunFu* DebuffKunFu::Clone(Status* new_status) const {
    return new DebuffKunFu(*this, new_status);
}
DebuffKunFu::DebuffKunFu(const DebuffKunFu& other, Status* new_status) : Debuff(other, new_status) {}

DebuffMing::DebuffMing(Status* linking_status, int val) : Debuff(linking_status, val) {
    name = "冥";
    id = DEBUFF_MING;
}
DebuffMing* DebuffMing::Clone(Status* new_status) const {
    return new DebuffMing(*this, new_status);
}
DebuffMing::DebuffMing(const DebuffMing& other, Status* new_status) : Debuff(other, new_status) {}
void DebuffMing::add(int val) {
    // 如果有辟邪，则减少同时减少辟邪和debuff的获取层数
    std::cout << ", ";
    std::cout << linked_status->style;
    if (linked_status->buffs[BUFF_BI_XIE]->getValue()) {
        int pi_xie_reduce = linked_status->buffs[BUFF_BI_XIE]->getValue();
        if (pi_xie_reduce > val) {
            pi_xie_reduce = val;
        }
        std::cout << "辟邪生效, ";
        val -= pi_xie_reduce;
        linked_status->buffs[BUFF_BI_XIE]->sub(pi_xie_reduce);
    }
    BaseStatusEffect::add(val);
    std::cout<< "获得" << val << "层" << name << DEFAULT_STYLE;
    if (linked_status->flag.flag[FLAG_YEMINGMING]) {
        linked_status->health->add(3 * val);
    }
    else {
        linked_status->health->sub(3 * val);
    }
    this->add_task_quene->executeTaskQueue(val);
}
void DebuffMing::sub(int val) {
    int sub_value = val;
    if (val > this->value) {
        sub_value = this->value;
        this->value = 0;
    } else {
        this->value -= val;
    }
    BaseStatusEffect::sub(sub_value);
    std::cout << ", " << linked_status->style << "减少" << sub_value << "层" << name << DEFAULT_STYLE;
    if (linked_status->flag.flag[FLAG_YEMINGMING]) {
        linked_status->health->add(3 * val);
    }
    else {
        linked_status->health->sub(3 * val);
    }
    this->sub_task_quene->executeTaskQueue(sub_value);
}


Debuff* debuff_create(int id, Status* linking_status, int val) {
    switch (id) {
    case DEBUFF_PO_ZHAN:
        return new DebuffPoZhan(linking_status, val);
    case DEBUFF_WAI_SHANG:
        return new DebuffWaiShang(linking_status, val);
    case DEBUFF_JIAN_GONG:
        return new DebuffJianGong(linking_status, val);
    case DEBUFF_XU_RUO:
        return new DebuffXuRuo(linking_status, val);
    case DEBUFF_NEI_SHANG:
        return new DebuffNeiShang(linking_status, val);
    case DEBUFF_KUN_FU:
        return new DebuffKunFu(linking_status, val);
    case DEBUFF_MING:
        return new DebuffMing(linking_status, val);
    default:
        return nullptr;
    }
}
