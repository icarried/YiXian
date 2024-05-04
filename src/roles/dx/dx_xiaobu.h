#ifndef DX_XIAOBU_H
#define DX_XIAOBU_H

#include "../base_role.h"

class RoleDxXiaobu : public BaseRole {
public:
    // ！！未完成
    class ExclusiveDestinyLQQ : public BaseDestiny {
    public:
        ExclusiveDestinyLQQ(BaseRole* role) : BaseDestiny(role) {
            name = "磨砺不止";
            realm = REALM_LQQ;
        }
        ~ExclusiveDestinyLQQ() = default;
    };

    // ！！未完成
    class ExclusiveDestinyZJQ : public BaseDestiny {
    public:
        ExclusiveDestinyZJQ(BaseRole* role) : BaseDestiny(role) {
            name = "锻体不息";
            realm = REALM_ZJQ;
        }
        ~ExclusiveDestinyZJQ() = default;
    };

    // ！！未完成
    class ExclusiveDestinyJDQ : public BaseDestiny {
    public:
        ExclusiveDestinyJDQ(BaseRole* role) : BaseDestiny(role) {
            name = "灵涌不竭";
            realm = REALM_JDQ;
        }
        ~ExclusiveDestinyJDQ() = default;
    };

    // ！！未完成
    class ExclusiveDestinyYYQ : public BaseDestiny {
    public:
        ExclusiveDestinyYYQ(BaseRole* role) : BaseDestiny(role) {
            name = "生机不灭";
            realm = REALM_YYQ;
        }
        ~ExclusiveDestinyYYQ() = default;
    };

    // 生命上限+5；战斗中每获得1层负面状态时加1生命
    class ExclusiveDestinyHSQ : public BaseDestiny {
    public:
        ExclusiveDestinyHSQ(BaseRole* role) : BaseDestiny(role) {
            name = "修玄不泯";
            realm = REALM_HSQ;
        }
        ~ExclusiveDestinyHSQ() = default;
        int PickEffect() override {
            role->my_status->health_max->setValue(role->my_status->health_max->getValue() + 5);
            role->my_status->health->setValue(role->my_status->health->getValue() + 5);
            return 0;
        }
        int BattleStartEffect() override {
            for (int debuff_type = 0; debuff_type < DEBUFF_END_INDEX; debuff_type++) {
                this->role->my_status->debuffs[debuff_type]->add_task_quene->addTask(
                    [this](int debuff_add_val){
                        this->role->my_status->health->add(debuff_add_val);
                    },
                    [](int){ return true; },
                    [](int){ return false; }
                );
            }
            return 0;
        }
    };

    RoleDxXiaobu(Status* my_status, Status* enemy_status) : BaseRole(my_status, enemy_status) {
        name = "小布";
        sect = SECT_DX;
        exclusive_destinies[REALM_LQQ] = new ExclusiveDestinyLQQ(this);
        exclusive_destinies[REALM_ZJQ] = new ExclusiveDestinyZJQ(this);
        exclusive_destinies[REALM_JDQ] = new ExclusiveDestinyJDQ(this);
        exclusive_destinies[REALM_YYQ] = new ExclusiveDestinyYYQ(this);
        exclusive_destinies[REALM_HSQ] = new ExclusiveDestinyHSQ(this);
    }
    ~RoleDxXiaobu() = default;
};


#endif // DX_XIAOBU_H