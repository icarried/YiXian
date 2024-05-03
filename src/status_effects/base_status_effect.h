#ifndef BASE_BUFF_H
#define BASE_BUFF_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "../cal.h"

class Status;

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
    virtual ~BaseStatusEffect() = default;

    // 获取数值
    int getValue() const;

    // 设置数值, 用于初始化
    void setValue(int val);

    // value增加
    virtual void add(int val);

    // value减少
    virtual void sub(int val);

    void add_or_sub(int val);
};

// 以下为具体buff类
class StatusVal : public BaseStatusEffect {
public:
    StatusVal(Status* linking_status, int val);
};

// buff，不能小于0
class Buff : public BaseStatusEffect {
public:
    Buff(Status* linking_status, int val);
    void add(int val) override;
    void sub(int val) override;
    std::string name;
    int id;
};

// debuff，不能小于0，可以被辟邪抵消，可被解除
class Debuff : public BaseStatusEffect {
public:
    Debuff(Status* linking_status, int val);
    void add(int val) override;
    void sub(int val) override;
    std::string name;
    int id;
};

#endif // BASE_BUFF_H