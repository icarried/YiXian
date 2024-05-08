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
    
    static std::map<int, std::map<std::string, std::function<BaseDestiny*(BaseRole*)>>>& getRegistry() {
        static std::map<int, std::map<std::string, std::function<BaseDestiny*(BaseRole*)>>> registry;
        return registry;
    }

    static bool registerDestiny(int realm, const std::string& name, std::function<BaseDestiny*(BaseRole*)> constructor) {
        getRegistry()[realm][name] = constructor;
        return true;
    }

    static BaseDestiny* createInstance(int realm, const std::string& name, BaseRole* role) {
        auto it = getRegistry()[realm].find(name);
        if (it != getRegistry()[realm].end()) {
            return it->second(role);
        }
        throw std::runtime_error("Destiny not found: " + name + " in realm " + std::to_string(realm));
        return nullptr;
    }
    // 选取效果, 使用状态时使用this->role->sor_my_status
    virtual int PickEffect() {
        return 0;
    }
    // 战斗开始效果, 使用状态时使用this->role->battle_my_status
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
    static bool registered;
};


#endif // BASE_DESTINY_H