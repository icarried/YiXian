#ifndef BASE_BUFF_H
#define BASE_BUFF_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "../cal.h"

class Status;
class AccountTaskQueue;

/*
# 对于伤害结算影响的buff有：
# 增加buff 加攻、剑意、锋锐、星力、气势、破绽（对方、负面）、外伤（对方、负面）
# 减少buff 减攻（负面）、虚弱（负面）、潜遁（对方）、铁骨（对方）

# 优先级：
# 先加减并最终至少为1：加攻、剑意、锋锐、星力、外伤（对方）、减攻
# 乘以百分比（多个百分比之间先相加）最终至少为1：气势、破绽（对方）、虚弱
# 额外结算，最终至少为1：潜遁、铁骨


# 其他buff：
# 正面buff 辟邪、......
# 负面buff 内伤(负面) 困缚(负面)

# buff值若大于0则减少1
*/

// 以下为基础状态效果类

class BaseStatusEffect {
protected:
    int value;

public:
    Status* linked_status;
    BaseStatusEffect(Status* linking_status, int val);
    virtual BaseStatusEffect* Clone(Status* new_status) const; // 虚拷贝函数
    BaseStatusEffect(const BaseStatusEffect& other, Status* new_status); // 拷贝构造函数
    virtual ~BaseStatusEffect();
    int getValue() const; // 获取数值
    void setValue(int val); // 设置数值, 用于初始化
    virtual void add(int val); // value增加
    virtual void sub(int val); // value减少
    void add_or_sub(int val); // value增加或减少
    void add(int val, bool just_set_value); // value增加，不触发任务队列，重载实现
    void sub(int val, bool just_set_value); // value减少，不触发任务队列，重载实现
    AccountTaskQueue* add_task_quene; // 增加时触发的任务队列
    AccountTaskQueue* sub_task_quene; // 减少时触发的任务队列
};

// 状态值
class StatusVal : public BaseStatusEffect {
public:
    StatusVal(Status* linking_status, int val);
    StatusVal* Clone(Status* new_status) const override; // 虚拷贝函数
    StatusVal(const StatusVal& other, Status* new_status); // 拷贝构造函数
};

// buff，不能小于0
class Buff : public BaseStatusEffect {
public:
    Buff(Status* linking_status, int val);
    Buff* Clone(Status* new_status) const override; // 虚拷贝函数
    Buff(const Buff& other, Status* new_status); // 拷贝构造函数
    void add(int val) override;
    void sub(int val) override;
    std::string name;
    int id;
};

// debuff，不能小于0，可以被辟邪抵消，可被解除
class Debuff : public BaseStatusEffect {
public:
    Debuff(Status* linking_status, int val);
    Debuff* Clone(Status* new_status) const override; // 虚拷贝函数
    Debuff(const Debuff& other, Status* new_status); // 拷贝构造函数
    void add(int val) override;
    void sub(int val) override;
    std::string name;
    int id;
};

#endif // BASE_BUFF_H