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
    default:
        return nullptr;
    }
}
