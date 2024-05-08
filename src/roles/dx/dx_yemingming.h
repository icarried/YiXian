#ifndef DX_YEMINGMING_H
#define DX_YEMINGMING_H

#include "../base_role.h"

class RoleDxYemingming : public BaseRole {
public:
    // 奇数轮开始时多加1次换牌机会, 偶数轮战斗中速度+3
    class ExclusiveDestinyLQQ : public BaseDestiny {
    public:
        ExclusiveDestinyLQQ(BaseRole* role) : BaseDestiny(role) {
            name = "阴晴圆缺";
            realm = REALM_LQQ;
        }
        ~ExclusiveDestinyLQQ() = default;
        int BattleStartEffect() override {
            // this->role->battle_my_status->task_quene_at_battle_start->addTask(
            //     [this](int round) {
            //         if (round % 2 == 1) {
            //             this->role->change_card_times += 1;
            //         }
            //         else {
            //             this->role->battle_my_status->speed->add(3);
            //         }
            //     },
            //     [](int){ return true; },
            //     [](int){ return false; }
            // );
            return 0;
        }
    };

    // 每场战斗开始获得1层冥状态
    class ExclusiveDestinyZJQ : public BaseDestiny {
    public:
        ExclusiveDestinyZJQ(BaseRole* role) : BaseDestiny(role) {
            name = "入冥";
            realm = REALM_ZJQ;
        }
        ~ExclusiveDestinyZJQ() = default;
        int BattleStartEffect() override {
            // this->role->battle_my_status->task_quene_at_battle_start->addTask(
            //     [this](int round) {
            //         this->role->battle_my_status->debuffs[DEBUFF_MING]->add(1);
            //     },
            //     [](int){ return true; },
            //     [](int){ return false; }
            // );
            // return 0;
            this->role->battle_my_status->debuffs[DEBUFF_MING]->add(1);
        }
    };

    // 获得一张《疯魔》
    class ExclusiveDestinyJDQ : public BaseDestiny {
    public:
        ExclusiveDestinyJDQ(BaseRole* role) : BaseDestiny(role) {
            name = "疯魔";
            realm = REALM_JDQ;
        }
        ~ExclusiveDestinyJDQ() = default;
        int PickEffect() override {
            this->role->sor_my_status->deck->AddCardtoHand(new Card_zsxm_jdq_fengmo(1, 0));
            return 0;
        }
    };

    // 获得一张《崩拳·冥夜》
    class ExclusiveDestinyYYQ : public BaseDestiny {
    public:
        ExclusiveDestinyYYQ(BaseRole* role) : BaseDestiny(role) {
            name = "崩拳·冥夜";
            realm = REALM_YYQ;
        }
        ~ExclusiveDestinyYYQ() = default;
        int PickEffect() override {
            this->role->sor_my_status->deck->AddCardtoHand(new Card_zsxm_yyq_bengquan_mingye(1, 0));
            return 0;
        }
    };

    // 获得一张《冥月蟾光》
    class ExclusiveDestinyHSQ : public BaseDestiny {
    public:
        ExclusiveDestinyHSQ(BaseRole* role) : BaseDestiny(role) {
            name = "冥月蟾光";
            realm = REALM_HSQ;
        }
        ~ExclusiveDestinyHSQ() = default;
        int PickEffect() override {
            this->role->sor_my_status->deck->AddCardtoHand(new Card_zsxm_hsq_mingyuechanguang(1, 0));
            return 0;
        }
    };

    RoleDxYemingming(Status* my_status, Status* enemy_status) : BaseRole(my_status, enemy_status) {
        name = "叶冥冥";
        sect = SECT_DX;
        exclusive_destinies[REALM_LQQ] = new ExclusiveDestinyLQQ(this);
        exclusive_destinies[REALM_ZJQ] = new ExclusiveDestinyZJQ(this);
        exclusive_destinies[REALM_JDQ] = new ExclusiveDestinyJDQ(this);
        exclusive_destinies[REALM_YYQ] = new ExclusiveDestinyYYQ(this);
        exclusive_destinies[REALM_HSQ] = new ExclusiveDestinyHSQ(this);
        // 增加独特flag，受到debuff冥的增加或减少改为回复生命
        my_status->flag.flag[FLAG_YEMINGMING] = true;
        BaseDestiny::registerDestiny(REALM_LQQ, "阴晴圆缺", [](BaseRole* role) {
            return new ExclusiveDestinyLQQ(role);
        });
        BaseDestiny::registerDestiny(REALM_ZJQ, "入冥", [](BaseRole* role) {
            return new ExclusiveDestinyZJQ(role);
        });
        BaseDestiny::registerDestiny(REALM_JDQ, "疯魔", [](BaseRole* role) {
            return new ExclusiveDestinyJDQ(role);
        });
        BaseDestiny::registerDestiny(REALM_YYQ, "崩拳·冥夜", [](BaseRole* role) {
            return new ExclusiveDestinyYYQ(role);
        });
        BaseDestiny::registerDestiny(REALM_HSQ, "冥月蟾光", [](BaseRole* role) {
            return new ExclusiveDestinyHSQ(role);
        });
    }
    ~RoleDxYemingming() = default;
    static bool registered;
};


#endif // DX_YEMINGMING_H