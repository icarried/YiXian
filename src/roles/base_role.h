#ifndef BASE_ROLE_H
#define BASE_ROLE_H

#include <string>

#include "../head.h"
#include "../status.h"
#include "../destinys/base_destiny.h"


/*
角色类
包含专属仙命，选取的仙命
当前境界和门派和副职
换牌次数及其上限
*/

class BaseRole {
public:
    BaseRole(Status* my_status, Status* enemy_status) : sor_my_status(my_status), sor_enemy_status(enemy_status) {
        for (int i = 0; i < ROLE_REALM_MAX + 1; i++) {
            picked_destinies[i] = new EmptyDestiny(this);
            exclusive_destinies[i] = nullptr;
        }
        battle_my_status = nullptr;
        battle_enemy_status = nullptr;
    }
    virtual ~BaseRole() {
        for (int i = 0; i < ROLE_REALM_MAX + 1; i++) {
            if (picked_destinies[i] != nullptr) {
                delete picked_destinies[i];
            }
            if (exclusive_destinies[i] != nullptr) {
                delete exclusive_destinies[i];
            }
        }
    }
    // 选取仙命，！！目前会有删除原仙命导致已加入任务队列的战斗开始效果无法执行的问题
    void PickDestiny(BaseDestiny* destiny) {
        if (picked_destinies[destiny->realm] != nullptr) {
            delete picked_destinies[destiny->realm];
        }
        picked_destinies[destiny->realm] = destiny;
        if (destiny->name == "空仙命") {
            return;
        }
        destiny->PickEffect();
        this->sor_my_status->task_quene_at_battle_start->addTask(
            [destiny](int battle_round) {
                destiny->BattleStartEffect(battle_round);
            },
            [](int){ return true; },
            [](int){ return false; }
        );
    }

    static std::map<std::string, std::function<BaseRole*(Status*, Status*)>>& getRegistry() {
        static std::map<std::string, std::function<BaseRole*(Status*, Status*)>> registry;
        return registry;
    }

    static bool registerRole(const std::string& name, std::function<BaseRole*(Status*, Status*)> constructor) {
        getRegistry()[name] = constructor;
        return true;
    }

    static BaseRole* createInstance(const std::string& name, Status* my_status, Status* enemy_status) {
        auto it = getRegistry().find(name);
        if (it != getRegistry().end()) {
            return it->second(my_status, enemy_status);
        }
        throw std::runtime_error("Role not found: " + name);
        return nullptr;
    }

    // 专属仙命数组
    BaseDestiny* exclusive_destinies[ROLE_REALM_MAX + 1];
    // 选取的仙命数组
    BaseDestiny* picked_destinies[ROLE_REALM_MAX + 1];
    // 角色状态
    Status* sor_my_status;
    Status* sor_enemy_status;
    Status* battle_my_status;
    Status* battle_enemy_status;

    // 角色名
    std::string name = "空角色名";
    // 当前境界, 初始为炼气期
    int realm = REALM_LQQ;
    // 当前门派, 由角色文件初始化
    std::string sect = "";
    // 副职
    std::string vice_job = "";
    // 换牌次数
    int change_card_times = 0;
    // 换牌次数上限
    int change_card_times_max = 25;
};

#endif // BASE_ROLE_H