#ifndef DEBUFFS_H
#define DEBUFFS_H

#include "base_status_effect.h"

#define DEBUFF_PO_ZHAN 0 //破绽
#define DEBUFF_WAI_SHANG 1 //外伤
#define DEBUFF_JIAN_GONG 2 //减攻
#define DEBUFF_XU_RUO 3 //虚弱
#define DEBUFF_NEI_SHANG 4 //内伤
#define DEBUFF_KUN_FU 5 //困缚
#define DEBUFF_END_INDEX 6 //负面buff结束索引

class DebuffPoZhan : public replace_Debuff {
public:
    DebuffPoZhan(Status* linking_status, int val);
};

class DebuffWaiShang : public replace_Debuff {
public:
    DebuffWaiShang(Status* linking_status, int val);
};

class DebuffJianGong : public replace_Debuff {
public:
    DebuffJianGong(Status* linking_status, int val);
};

class DebuffXuRuo : public replace_Debuff {
public:
    DebuffXuRuo(Status* linking_status, int val);
};

class DebuffNeiShang : public replace_Debuff {
public:
    DebuffNeiShang(Status* linking_status, int val);
};

class DebuffKunFu : public replace_Debuff {
public:
    DebuffKunFu(Status* linking_status, int val);
};

replace_Debuff* debuff_create(int id, Status* linking_status, int val);

#endif // !DEBUFFS_H
