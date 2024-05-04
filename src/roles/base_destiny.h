#ifndef BASE_DESTINY_H
#define BASE_DESTINY_H

#include <string>
#include "../head.h"
#include "../cards/base_card.h"
#include "../cards/cards.h"
#include "../deck.h"

class BaseRole;
/*
仙命类
暂时只给出给战斗内有影响的效果

专属于某个角色的仙命类，继承自BaseDestiny
：Exclusive Destiny
*/

class BaseDestiny {
public:
    BaseDestiny(BaseRole* role) : role(role) {}
    virtual ~BaseDestiny() = default;
    // 选取效果
    virtual int PickEffect() {
        return 0;
    }
    // 战斗开始效果
    virtual int BattleStartEffect() {
        return 0;
    }
    // 战斗结束效果 ！！！！未加入选取效果中，需要在选取效果中加入
    virtual int BattleEndEffect() {
        return 0;
    }
    std::string name;
    int realm = REALM_NONE;
    BaseRole* role;
};

// 空仙命
class EmptyDestiny : public BaseDestiny {
public:
    EmptyDestiny(BaseRole* role) : BaseDestiny(role) {
        name = "空仙命";
        realm = REALM_NONE;
    }
    ~EmptyDestiny() = default;
};

#endif // BASE_DESTINY_H