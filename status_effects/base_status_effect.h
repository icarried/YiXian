#ifndef BASE_BUFF_H
#define BASE_BUFF_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

class Status;

// 以下为基础状态效果类

class BaseStatusEffect {
protected:
    Status* linked_status;
    int value;

public:
    BaseStatusEffect(Status* linking_status, int val) : linked_status(linking_status), value(val) {}

    // .getValue()获取数值
    int getValue() const {
        return value;
    }

    // .setValue()设置数值, 用于初始化
    void setValue(int val) {
        value = val;
    }

    // value增加
    virtual void add(int val) {
        value += val;
    }

    // value减少
    virtual void sub(int val) {
        value -= val;
    }

    void add_or_sub(int val) {
        if (val > 0) {
            add(val);
        } else {
            sub(-val);
        }
    }
};

// 以下为具体buff类
class StatusVal : public BaseStatusEffect {
public:
    StatusVal(Status* linking_status, int val) : BaseStatusEffect(linking_status, val) {}

    // // value增加
    // void add(int val) override {
    //     BaceStatusEffect::add(val);
    // }

    // // value减少
    // void sub(int val) override {
    //     BaceStatusEffect::sub(val);
    // }
};

// class Buff : public BaseStatusEffect {
// public:
//     Buff(Status* linking_status, int val) : BaseStatusEffect(linking_status, val) {}

//     // // value增加
//     // void add(int val) override {
//     //     BaceStatusEffect::add(val);
//     // }

//     // // value减少
//     // void sub(int val) override {
//     //     BaceStatusEffect::sub(val);
//     // }
// };

// class Debuff : public BaseStatusEffect {
// public:
//     Debuff(Status* linking_status, int val) : BaseStatusEffect(linking_status, val) {}

//     // // value增加
//     // void add(int val) override {
//     //     BaceStatusEffect::add(val);
//     // }

//     // // value减少
//     // void sub(int val) override {
//     //     BaceStatusEffect::sub(val);
//     // }
// };

#endif // BASE_BUFF_H