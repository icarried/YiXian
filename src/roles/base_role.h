#ifndef BASE_ROLE_H
#define BASE_ROLE_H

#include <string>

#include "../head.h"
#include "../status.h"
#include "base_destiny.h"


/*
角色类
包含专属仙命，选取的仙命
当前境界和门派和副职
换牌次数及其上限
*/

class BaseRole {
public:
    BaseRole(Status* my_status, Status* enemy_status) : my_status(my_status), enemy_status(enemy_status) {
        for (int i = 0; i < ROLE_REALM_MAX + 1; i++) {
            picked_destinies[i] = new EmptyDestiny(this);
            exclusive_destinies[i] = nullptr;
        }
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
    // 选取仙命
    void PickDestiny(BaseDestiny* destiny) {
        if (picked_destinies[destiny->realm] != nullptr) {
            delete picked_destinies[destiny->realm];
        }
        picked_destinies[destiny->realm] = destiny;
        destiny->PickEffect();
        this->my_status->task_quene_at_battle_start->addTask(
            [destiny](int battle_round) {
                destiny->BattleStartEffect();
            },
            [](int){ return true; },
            [](int){ return false; }
        );
    }

    // 专属仙命数组
    BaseDestiny* exclusive_destinies[ROLE_REALM_MAX + 1];
    // 选取的仙命数组
    BaseDestiny* picked_destinies[ROLE_REALM_MAX + 1];
    // 角色状态
    Status* my_status;
    Status* enemy_status;

    // 角色名
    std::string name = "空角色名";
    // 当前境界, 初始为炼气期
    int realm = REALM_LQQ;
    // 当前门派, 由角色文件初始化
    int sect = SECT_NONE;
    // 副职
    int vice_job = VICE_JOB_NONE;
    // 换牌次数
    int change_card_times = 0;
    // 换牌次数上限
    int change_card_times_max = 25;
};

#endif // BASE_ROLE_H