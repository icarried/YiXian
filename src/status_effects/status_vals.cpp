#include "status_vals.h"
#include "../status.h"
// 临时放于根目录编译

// 失去生命值总和的构造函数
HealthSubTotal::HealthSubTotal(Status* linking_status, int val) : StatusVal(linking_status, val) {}
HealthSubTotal* HealthSubTotal::Clone(Status* new_status) const {
    return new HealthSubTotal(*this, new_status);
}
HealthSubTotal::HealthSubTotal(const HealthSubTotal& other, Status* new_status) : StatusVal(other, new_status) {}


// 体魄增加总和的构造函数
TiPoAddTotal::TiPoAddTotal(Status* linking_status, int val) : StatusVal(linking_status, val) {}
TiPoAddTotal* TiPoAddTotal::Clone(Status* new_status) const {
    return new TiPoAddTotal(*this, new_status);
}
TiPoAddTotal::TiPoAddTotal(const TiPoAddTotal& other, Status* new_status) : StatusVal(other, new_status) {}


// 生命值上限的构造函数及方法
HealthMax::HealthMax(Status* linking_status, int val) : StatusVal(linking_status, val) {}
HealthMax* HealthMax::Clone(Status* new_status) const {
    return new HealthMax(*this, new_status);
}
HealthMax::HealthMax(const HealthMax& other, Status* new_status) : StatusVal(other, new_status) {}
void HealthMax::add(int val) {
    if (val > 0) {
        this->value += val;
        std::cout << "，增加" << val << "点血量上限，剩余" << this->value << "点血量上限";
        this->add_task_quene->executeTaskQueue(val);
    }
}
void HealthMax::sub(int val) {
    if (val > 0) {
        this->value -= val;
        std::cout << "，失去" << val << "点血量上限，剩余" << this->value << "点血量上限";
        if (linked_status->health->getValue() > this->value) {
            std::cout << "，血量上限减少导致血量减少";
            linked_status->health->sub(linked_status->health->getValue() - this->value);
        }
        this->sub_task_quene->executeTaskQueue(val);
    }
}


// 生命值的构造函数及方法
Health::Health(Status* linking_status, int val) : StatusVal(linking_status, val) {}
Health* Health::Clone(Status* new_status) const {
    return new Health(*this, new_status);
}
Health::Health(const Health& other, Status* new_status) : StatusVal(other, new_status) {}
// 生命值增加，目前是先增加，再判断是否超过上限，如果超过上限，则设为上限
void Health::add(int val) {
    if (val > 0) {
        this->value += val;
        if (linked_status->health_max->getValue() - linked_status->health->getValue() < val) {
            this->value = linked_status->health_max->getValue();
        }
        std::cout << "，恢复" << val << "点血，剩余" << this->value << "/" << linked_status->health_max->getValue() << "点血";
        this->add_task_quene->executeTaskQueue(val);
    }
}
// 生命值可以为负数
void Health::sub(int val) {
    if (val > 0) {
        linked_status->health_sub_total->add(val);
        this->value -= val;
        std::cout << "失去" << val << "点血，剩余" << this->value << "/" << linked_status->health_max->getValue() << "点血";
        this->sub_task_quene->executeTaskQueue(val);
    }
}


// 防的构造函数
Defense::Defense(Status* linking_status, int val) : StatusVal(linking_status, val) {}
Defense* Defense::Clone(Status* new_status) const {
    return new Defense(*this, new_status);
}
Defense::Defense(const Defense& other, Status* new_status) : StatusVal(other, new_status) {}
void Defense::add(int val) {
    if (val > 0) {
        this->value += val;
        std::cout << "，增加" << val << "点防御，剩余" << this->value << "点防御";
        this->add_task_quene->executeTaskQueue(val);
    }
}
// 防最少为0
void Defense::sub(int val) {
    if (val > 0) {
        this->value -= val;
        if (this->value < 0) {
            this->value = 0;
        }
        std::cout << "，失去" << val << "点防御，剩余" << this->value << "点防御";
        this->sub_task_quene->executeTaskQueue(val);
    }
}


// 灵气的构造函数
LingQi::LingQi(Status* linking_status, int val) : StatusVal(linking_status, val) {}
LingQi* LingQi::Clone(Status* new_status) const {
    return new LingQi(*this, new_status);
}
LingQi::LingQi(const LingQi& other, Status* new_status) : StatusVal(other, new_status) {}
void LingQi::add(int val) {
    if (val > 0) {
        this->value += val;
        std::cout << "，增加" << val << "点灵气，剩余" << this->value << "点灵气";
        this->add_task_quene->executeTaskQueue(val);
    }
}
// 灵气最少为0
void LingQi::sub(int val) {
    if (val > 0) {
        this->value -= val;
        if (this->value < 0) {
            this->value = 0;
        }
        std::cout << "，失去" << val << "点灵气，剩余" << this->value << "点灵气";
        this->sub_task_quene->executeTaskQueue(val);
    }
}


// 修为的构造函数
XiuWei::XiuWei(Status* linking_status, int val) : StatusVal(linking_status, val) {}
XiuWei* XiuWei::Clone(Status* new_status) const {
    return new XiuWei(*this, new_status);
}
XiuWei::XiuWei(const XiuWei& other, Status* new_status) : StatusVal(other, new_status) {}
void XiuWei::add(int val) {
    if (val > 0) {
        this->value += val;
        std::cout << "，增加" << val << "点修为，剩余" << this->value << "点修为";
        this->add_task_quene->executeTaskQueue(val);
    }
}
// 修为最少为0
void XiuWei::sub(int val) {
    if (val > 0) {
        this->value -= val;
        if (this->value < 0) {
            this->value = 0;
        }
        std::cout << "，失去" << val << "点修为，剩余" << this->value << "点修为";
        this->sub_task_quene->executeTaskQueue(val);
    }
}


// 体魄上限的构造函数及方法
TiPoMax::TiPoMax(Status* linking_status, int val) : StatusVal(linking_status, val) {}
TiPoMax* TiPoMax::Clone(Status* new_status) const {
    return new TiPoMax(*this, new_status);
}
TiPoMax::TiPoMax(const TiPoMax& other, Status* new_status) : StatusVal(other, new_status) {}
void TiPoMax::add(int val) {
    if (val > 0) {
        this->value += val;
        std::cout << "，增加" << val << "点体魄上限，剩余" << this->value << "点体魄上限";
        this->add_task_quene->executeTaskQueue(val);
    }
}
// 体魄上限最少为0, 特别的：体魄在战斗中可以超出上限，体魄上限减少不会导致体魄减少
void TiPoMax::sub(int val) {
    if (val > 0) {
        this->value -= val;
        if (this->value < 0) {
            this->value = 0;
        }
        std::cout << "，失去" << val << "点体魄上限，剩余" << this->value << "点体魄上限";
        this->sub_task_quene->executeTaskQueue(val);
    }
}


// 体魄的构造函数及方法, 增加体魄将同时增加等量生命值上限，战斗内体魄可以超过体魄上限，超过体魄上限的部分将额外回复等量生命值
TiPo::TiPo(Status* linking_status, int val) : StatusVal(linking_status, val) {}
TiPo* TiPo::Clone(Status* new_status) const {
    return new TiPo(*this, new_status);
}
TiPo::TiPo(const TiPo& other, Status* new_status) : StatusVal(other, new_status) {}
// 增加体魄将同时增加等量生命值上限, 超出体魄上限的部分额外回复等量生命值
// 若在增加体魄前，体魄已经超出上限，则回复的生命值等于增加的体魄；若在增加体魄后，体魄超出上限，则回复的生命值等于超出上限的部分
void TiPo::add(int val) {
    if (val > 0) {
        int health_val = 0;
        if (linked_status->ti_po->getValue() > linked_status->ti_po_max->getValue()) {
            health_val = val;
        } else if (linked_status->ti_po->getValue() + val > linked_status->ti_po_max->getValue()) {
            health_val = linked_status->ti_po->getValue() + val - linked_status->ti_po_max->getValue();
        }
        this->value += val;
        std::cout << "，增加" << val << "点体魄，剩余" << this->value << "点体魄";
        linked_status->ti_po_add_total->add(val);
        linked_status->health_max->add(val);
        linked_status->health->add(health_val);
        this->add_task_quene->executeTaskQueue(val);
    }
}
// 体魄最少为0, 体魄减少不会导致生命值减少, 但会导致生命值上限减少
void TiPo::sub(int val) {
    if (val > 0) {
        this->value -= val;
        if (this->value < 0) {
            this->value = 0;
        }
        std::cout << "，失去" << val << "点体魄，剩余" << this->value << "点体魄";
        linked_status->health_max->sub(val);
        this->sub_task_quene->executeTaskQueue(val);
    }
}




