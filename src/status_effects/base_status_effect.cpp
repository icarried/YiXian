#include "base_status_effect.h"
#include "../status.h"

BaseStatusEffect::BaseStatusEffect(Status* linking_status, int val) : linked_status(linking_status), value(val) {
    add_task_quene = new AccountTaskQueue(linking_status);
    sub_task_quene = new AccountTaskQueue(linking_status);
}

// 虚拷贝函数
BaseStatusEffect* BaseStatusEffect::Clone(Status* new_status) const {
    return new BaseStatusEffect(*this, new_status);
}

// 拷贝构造函数
BaseStatusEffect::BaseStatusEffect(const BaseStatusEffect& other, Status* new_status) {
    linked_status = new_status;
    value = other.value;
    add_task_quene = other.add_task_quene->Clone(new_status);
    sub_task_quene = other.sub_task_quene->Clone(new_status);
}

BaseStatusEffect::~BaseStatusEffect() {
    delete add_task_quene;
    delete sub_task_quene;
}

int BaseStatusEffect::getValue() const {
    return value;
}

void BaseStatusEffect::setValue(int val) {
    value = val;
}

void BaseStatusEffect::add(int val) {
    value += val;
}

void BaseStatusEffect::sub(int val) {
    value -= val;
}

void BaseStatusEffect::add_or_sub(int val) {
    if (val > 0) {
        add(val);
    } else {
        sub(-val);
    }
}

void BaseStatusEffect::setAdd(int val) {
    value += val;
}

void BaseStatusEffect::setSub(int val) {
    value -= val;
}

StatusVal::StatusVal(Status* linking_status, int val) : BaseStatusEffect(linking_status, val) {}

// 虚拷贝函数
StatusVal* StatusVal::Clone(Status* new_status) const {
    return new StatusVal(*this, new_status);
}

// 拷贝构造函数
StatusVal::StatusVal(const StatusVal& other, Status* new_status) : BaseStatusEffect(other, new_status) {}

Buff::Buff(Status* linking_status, int val) : BaseStatusEffect(linking_status, val) {
    name = "无名buff";
    id = 0;
}

// 虚拷贝函数
Buff* Buff::Clone(Status* new_status) const {
    return new Buff(*this, new_status);
}

// 拷贝构造函数
Buff::Buff(const Buff& other, Status* new_status) : BaseStatusEffect(other, new_status) {
    name = other.name;
    id = other.id;
}

void Buff::add(int val) {
    BaseStatusEffect::add(val);
    std::cout << ", "<< linked_status->style <<"获得" << val << "层" << name << DEFAULT_STYLE;
    this->add_task_quene->executeTaskQueue(val);
}

void Buff::sub(int val) {
    int sub_value = val;
    if (val > this->value) {
        sub_value = this->value;
    } else {
        sub_value = val;
    }
    BaseStatusEffect::sub(sub_value);
    std::cout << ", "<< linked_status->style <<"减少" << sub_value << "层" << name <<DEFAULT_STYLE;
    this->sub_task_quene->executeTaskQueue(sub_value);
}

Debuff::Debuff(Status* linking_status, int val) : BaseStatusEffect(linking_status, val) {
    name = "无名debuff";
    id = 0;
}

// 虚拷贝函数
Debuff* Debuff::Clone(Status* new_status) const {
    return new Debuff(*this, new_status);
}

// 拷贝构造函数
Debuff::Debuff(const Debuff& other, Status* new_status) : BaseStatusEffect(other, new_status) {
    name = other.name;
    id = other.id;
}

// debuff获取
void Debuff::add(int val) {
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
    this->add_task_quene->executeTaskQueue(val);
}

void Debuff::sub(int val) {
    int sub_value = val;
    if (val > this->value) {
        sub_value = this->value;
    } else {
        sub_value = val;
    }
    BaseStatusEffect::sub(sub_value);
    std::cout << ", " << linked_status->style << "减少" << sub_value << "层" << name << DEFAULT_STYLE;
    this->sub_task_quene->executeTaskQueue(sub_value);
}