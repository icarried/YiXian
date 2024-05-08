#ifndef DEBUFFS_H
#define DEBUFFS_H

#include "base_status_effect.h"

#define DEBUFF_PO_ZHAN 0 //破绽
#define DEBUFF_WAI_SHANG 1 //外伤
#define DEBUFF_JIAN_GONG 2 //减攻
#define DEBUFF_XU_RUO 3 //虚弱
#define DEBUFF_NEI_SHANG 4 //内伤
#define DEBUFF_KUN_FU 5 //困缚
#define DEBUFF_MING 6 //冥
#define DEBUFF_END_INDEX 7 //负面buff结束索引

class DebuffPoZhan : public Debuff {
public:
    DebuffPoZhan(Status* linking_status, int val);
    DebuffPoZhan* Clone(Status* new_status) const override;
    DebuffPoZhan(const DebuffPoZhan& other, Status* new_status);
};

class DebuffWaiShang : public Debuff {
public:
    DebuffWaiShang(Status* linking_status, int val);
    DebuffWaiShang* Clone(Status* new_status) const override;
    DebuffWaiShang(const DebuffWaiShang& other, Status* new_status);
};

class DebuffJianGong : public Debuff {
public:
    DebuffJianGong(Status* linking_status, int val);
    DebuffJianGong* Clone(Status* new_status) const override;
    DebuffJianGong(const DebuffJianGong& other, Status* new_status);
};

class DebuffXuRuo : public Debuff {
public:
    DebuffXuRuo(Status* linking_status, int val);
    DebuffXuRuo* Clone(Status* new_status) const override;
    DebuffXuRuo(const DebuffXuRuo& other, Status* new_status);
};

class DebuffNeiShang : public Debuff {
public:
    DebuffNeiShang(Status* linking_status, int val);
    DebuffNeiShang* Clone(Status* new_status) const override;
    DebuffNeiShang(const DebuffNeiShang& other, Status* new_status);
};

class DebuffKunFu : public Debuff {
public:
    DebuffKunFu(Status* linking_status, int val);
    DebuffKunFu* Clone(Status* new_status) const override;
    DebuffKunFu(const DebuffKunFu& other, Status* new_status);
};

class DebuffMing : public Debuff {
public:
    DebuffMing(Status* linking_status, int val);
    DebuffMing* Clone(Status* new_status) const override;
    DebuffMing(const DebuffMing& other, Status* new_status);
    void add(int val) override;
    void sub(int val) override;
};

Debuff* debuff_create(int id, Status* linking_status, int val);

#endif // !DEBUFFS_H
