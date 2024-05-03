#include "base_status_effect.h"
#include "../status.h"

BaseStatusEffect::BaseStatusEffect(Status* linking_status, int val) : linked_status(linking_status), value(val) {}

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

StatusVal::StatusVal(Status* linking_status, int val) : BaseStatusEffect(linking_status, val) {
    add_task_quene = new AccountTaskQueue(linking_status);
    sub_task_quene = new AccountTaskQueue(linking_status);
}

StatusVal::~StatusVal() {
    delete add_task_quene;
    delete sub_task_quene;
}

Buff::Buff(Status* linking_status, int val) : BaseStatusEffect(linking_status, val) {
    linking_status->num_buffs++;
}

void Buff::add(int val) {
    BaseStatusEffect::add(val);
    std::cout << "，获得" << val << "层" << name;
}

void Buff::sub(int val) {
    int sub_value = val;
    if (val > this->value) {
        sub_value = this->value;
        this->value = 0;
    } else {
        this->value -= val;
    }
    BaseStatusEffect::sub(sub_value);
    std::cout << "，减少" << sub_value << "层" << name;
}

Debuff::Debuff(Status* linking_status, int val) : BaseStatusEffect(linking_status, val) {
    linking_status->num_debuffs++;
}

// debuff获取
void Debuff::add(int val) {
    // 如果有辟邪，则减少同时减少辟邪和debuff的获取层数
    if (linked_status->buffs[BUFF_BI_XIE]->getValue()) {
        int pi_xie_reduce = linked_status->buffs[BUFF_BI_XIE]->getValue();
        if (pi_xie_reduce > val) {
            pi_xie_reduce = val;
        }
        std::cout << "，辟邪生效";
        val -= pi_xie_reduce;
        linked_status->buffs[BUFF_BI_XIE]->sub(pi_xie_reduce);
    }
    BaseStatusEffect::add(val);
    std::cout << "，获得" << val << "层" << name;
}

void Debuff::sub(int val) {
    int sub_value = val;
    if (val > this->value) {
        sub_value = this->value;
        this->value = 0;
    } else {
        this->value -= val;
    }
    BaseStatusEffect::sub(sub_value);
    std::cout << "，减少" << sub_value << "层" << name;
}