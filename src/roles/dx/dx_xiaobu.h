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

    // 获得1张《锻体不息》
    class ExclusiveDestinyZJQ : public BaseDestiny {
    public:
        ExclusiveDestinyZJQ(BaseRole* role) : BaseDestiny(role) {
            name = "锻体不息";
            realm = REALM_ZJQ;
        }
        ~ExclusiveDestinyZJQ() = default;
        int PickEffect() override {
            this->role->sor_my_status->deck->AddCardtoHand(new Card_zsxm_zjq_duantibuxi(1, 0));
            return 0;
        }
    };

    // 使用卡牌时若灵气不足，每点灵气耗3生命和1体魄代替（生命或体魄不足则无效）
    class ExclusiveDestinyJDQ : public BaseDestiny {
    public:
        ExclusiveDestinyJDQ(BaseRole* role) : BaseDestiny(role) {
            name = "灵涌不竭";
            realm = REALM_JDQ;
        }
        ~ExclusiveDestinyJDQ() = default;
        int BattleStartEffect(int battle_round) override {
            this->role->battle_my_status->task_quene_before_ling_qi_cost->addTask(
                [this](BaseCard* card) {
                    int required_ling_qi = card->ling_qi_cost - this->role->battle_my_status->ling_qi->getValue();
                    if (this->role->battle_my_status->health->getValue() >= 3 * required_ling_qi && this->role->battle_my_status->ti_po->getValue() >= required_ling_qi) {
                        this->role->battle_my_status->health->sub(3 * required_ling_qi);
                        this->role->battle_my_status->ti_po->sub(1 * required_ling_qi);
                        this->role->battle_my_status->ling_qi->add(required_ling_qi);
                    }
                },
                [this](BaseCard* card){ return card->ling_qi_cost > this->role->battle_my_status->ling_qi->getValue();},
                [](BaseCard* card){ return false; }
            );
            return 0;
        }
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
            role->sor_my_status->health_max->setValue(role->sor_my_status->health_max->getValue() + 5);
            role->sor_my_status->health->setValue(role->sor_my_status->health->getValue() + 5);
            return 0;
        }
        int BattleStartEffect(int battle_round) override {
            for (int debuff_type = 0; debuff_type < DEBUFF_END_INDEX; debuff_type++) {
                this->role->battle_my_status->debuffs[debuff_type]->add_task_quene->addTask(
                    [this](int debuff_add_val){
                        this->role->battle_my_status->health->add(debuff_add_val);
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
        BaseDestiny::registerDestiny(REALM_LQQ, "磨砺不止", [](BaseRole* role) {
            return new ExclusiveDestinyLQQ(role);
        });
        BaseDestiny::registerDestiny(REALM_ZJQ, "锻体不息", [](BaseRole* role) {
            return new ExclusiveDestinyZJQ(role);
        });
        BaseDestiny::registerDestiny(REALM_JDQ, "灵涌不竭", [](BaseRole* role) {
            return new ExclusiveDestinyJDQ(role);
        });
        BaseDestiny::registerDestiny(REALM_YYQ, "生机不灭", [](BaseRole* role) {
            return new ExclusiveDestinyYYQ(role);
        });
        BaseDestiny::registerDestiny(REALM_HSQ, "修玄不泯", [](BaseRole* role) {
            return new ExclusiveDestinyHSQ(role);
        });
    }
    ~RoleDxXiaobu() = default;
    static bool registered;
};


#endif // DX_XIAOBU_H