#ifndef STATUS_VALS_H
#define STATUS_VALS_H

#include "base_status_effect.h"

// 失去血量总和
class HealthSubTotal : public StatusVal {
public:
    HealthSubTotal(Status* linking_status, int val);
    HealthSubTotal* Clone(Status* new_status) const override;
    HealthSubTotal(const HealthSubTotal& other, Status* new_status);
};

class TiPoAddTotal : public StatusVal {
public:
    TiPoAddTotal(Status* linking_status, int val);
    TiPoAddTotal* Clone(Status* new_status) const override;
    TiPoAddTotal(const TiPoAddTotal& other, Status* new_status);
};

// 生命值上限
class HealthMax : public StatusVal {
public:
    HealthMax(Status* linking_status, int val);
    HealthMax* Clone(Status* new_status) const override;
    HealthMax(const HealthMax& other, Status* new_status);
    void add(int val) override;
    void sub(int val) override;
};

// 生命值
class Health : public StatusVal {
public:
    Health(Status* linking_status, int val);
    Health* Clone(Status* new_status) const override;
    Health(const Health& other, Status* new_status);
    void add(int val) override;
    void sub(int val) override;
};

// 防
class Defense : public StatusVal {
public:
    Defense(Status* linking_status, int val);
    Defense* Clone(Status* new_status) const override;
    Defense(const Defense& other, Status* new_status);
    void add(int val) override;
    void sub(int val) override;
};

// 灵气
class LingQi : public StatusVal {
public:
    LingQi(Status* linking_status, int val);
    LingQi* Clone(Status* new_status) const override;
    LingQi(const LingQi& other, Status* new_status);
    void add(int val) override;
    void sub(int val) override;
};

// 修为
class XiuWei : public StatusVal {
public:
    XiuWei(Status* linking_status, int val);
    XiuWei* Clone(Status* new_status) const override;
    XiuWei(const XiuWei& other, Status* new_status);
    void add(int val) override;
    void sub(int val) override;
};

// 速度
class Speed : public StatusVal {
public:
    Speed(Status* linking_status, int val);
    Speed* Clone(Status* new_status) const override;
    Speed(const Speed& other, Status* new_status);
    void add(int val) override;
    void sub(int val) override;
};

// 体魄上限
class TiPoMax : public StatusVal {
public:
    TiPoMax(Status* linking_status, int val);
    TiPoMax* Clone(Status* new_status) const override;
    TiPoMax(const TiPoMax& other, Status* new_status);
    void add(int val) override;
    void sub(int val) override;
};

// 体魄
class TiPo : public StatusVal {
public:
    TiPo(Status* linking_status, int val);
    TiPo* Clone(Status* new_status) const override;
    TiPo(const TiPo& other, Status* new_status);
    void add(int val) override;
    void sub(int val) override;
};



#endif // STATUS_VALS_H
