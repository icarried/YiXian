#ifndef STATUS_VALS_H
#define STATUS_VALS_H

#include "base_status_effect.h"

// 失去血量总和
class HealthSubTotal : public StatusVal {
public:
    HealthSubTotal(Status* linking_status, int val);
};

class TiPoAddTotal : public StatusVal {
public:
    TiPoAddTotal(Status* linking_status, int val);
};

// 生命值上限
class HealthMax : public StatusVal {
public:
    HealthMax(Status* linking_status, int val);
    void add(int val) override;
    void sub(int val) override;
};

// 生命值
class Health : public StatusVal {
public:
    Health(Status* linking_status, int val);
    void add(int val) override;
    void sub(int val) override;
};

// 防
class Defense : public StatusVal {
public:
    Defense(Status* linking_status, int val);
    void add(int val) override;
    void sub(int val) override;
};

// 灵气
class LingQi : public StatusVal {
public:
    LingQi(Status* linking_status, int val);
    void add(int val) override;
    void sub(int val) override;
};

// 修为
class XiuWei : public StatusVal {
public:
    XiuWei(Status* linking_status, int val);
    void add(int val) override;
    void sub(int val) override;
};

// 体魄上限
class TiPoMax : public StatusVal {
public:
    TiPoMax(Status* linking_status, int val);
    void add(int val) override;
    void sub(int val) override;
};

// 体魄
class TiPo : public StatusVal {
public:
    TiPo(Status* linking_status, int val);
    void add(int val) override;
    void sub(int val) override;
};



#endif // STATUS_VALS_H
