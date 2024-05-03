#include "debuffs.h"
#include "../status.h"

DebuffPoZhan::DebuffPoZhan(Status* linking_status, int val) : Debuff(linking_status, val) {
    name = "破绽";
    id = DEBUFF_PO_ZHAN;
}

DebuffWaiShang::DebuffWaiShang(Status* linking_status, int val) : Debuff(linking_status, val) {
    name = "外伤";
    id = DEBUFF_WAI_SHANG;
}

DebuffJianGong::DebuffJianGong(Status* linking_status, int val) : Debuff(linking_status, val) {
    name = "减攻";
    id = DEBUFF_JIAN_GONG;
}

DebuffXuRuo::DebuffXuRuo(Status* linking_status, int val) : Debuff(linking_status, val) {
    name = "虚弱";
    id = DEBUFF_XU_RUO;
}

DebuffNeiShang::DebuffNeiShang(Status* linking_status, int val) : Debuff(linking_status, val) {
    name = "内伤";
    id = DEBUFF_NEI_SHANG;
}

DebuffKunFu::DebuffKunFu(Status* linking_status, int val) : Debuff(linking_status, val) {
    name = "困缚";
    id = DEBUFF_KUN_FU;
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
    default:
        return nullptr;
    }
}
