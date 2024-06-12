#ifndef DX_TUKUI_H
#define DX_TUKUI_H

#include "../base_role.h"

class RoleDxTukui : public BaseRole {
public:
    // ！！未完成
    class ExclusiveDestinyLQQ : public BaseDestiny {
    public:
        ExclusiveDestinyLQQ(BaseRole* role) : BaseDestiny(role) {
            name = "锻躯之道";
            realm = REALM_LQQ;
        }
        ~ExclusiveDestinyLQQ() = default;
    };

    // 获得1张《盛气凌人》
    class ExclusiveDestinyZJQ : public BaseDestiny {
    public:
        ExclusiveDestinyZJQ(BaseRole* role) : BaseDestiny(role) {
            name = "盛气凌人";
            realm = REALM_ZJQ;
        }
        ~ExclusiveDestinyZJQ() = default;
        int PickEffect() override {
            this->role->sor_my_status->deck->AddCardtoHand(new Card_zsxm_zjq_shengqilingren(1, 0));
            return 0;
        }
    };

    // 体魄上限+2；每场战斗开始时获得1层加攻和1层外伤
    class ExclusiveDestinyJDQ : public BaseDestiny {
    public:
        ExclusiveDestinyJDQ(BaseRole* role) : BaseDestiny(role) {
            name = "搏命之勇";
            realm = REALM_JDQ;
        }
        ~ExclusiveDestinyJDQ() = default;
        int PickEffect() override {
            role->sor_my_status->ti_po_max->setValue(role->sor_my_status->ti_po_max->getValue() + 2);
            return 0;
        }
        int BattleStartEffect(int battle_round) override {
            role->battle_my_status->buffs[BUFF_JIA_GONG]->add(1);
            role->battle_my_status->debuffs[DEBUFF_WAI_SHANG]->add(1);
            return 0;
        }
    };

    // 耗生命的牌改为耗生命上限
    class ExclusiveDestinyYYQ : public BaseDestiny {
    public:
        ExclusiveDestinyYYQ(BaseRole* role) : BaseDestiny(role) {
            name = "崩裂之拳";
            realm = REALM_YYQ;
        }
        ~ExclusiveDestinyYYQ() = default;
        int PickEffect() override {
            role->sor_my_status->SetFlag("崩裂之拳", true);
            return 0;
        }
    };

    // 体魄上限+4；战斗中每次使用加体魄的牌后，追加3攻
    class ExclusiveDestinyHSQ : public BaseDestiny {
    public:
        ExclusiveDestinyHSQ(BaseRole* role) : BaseDestiny(role) {
            name = "猛攻之姿";
            realm = REALM_HSQ;
        }
        ~ExclusiveDestinyHSQ() = default;
        int PickEffect() override {
            role->sor_my_status->ti_po_max->setValue(role->sor_my_status->ti_po_max->getValue() + 4);
            return 0;
        }
        int BattleStartEffect(int battle_round) override {
            role->battle_my_status->task_quene_after_effect->addTask( 
                [this](BaseCard* card){ Attack(this->role->battle_my_status, this->role->battle_enemy_status, 3); },
                [](BaseCard* card){ return card->card_tag[TI_PO_CARD] ? true : false; },
                [](BaseCard* card){ return true; },
                REMARK_BENG_QUAN
            );
            return 0;
        }
    };

    RoleDxTukui(Status* my_status, Status* enemy_status) : BaseRole(my_status, enemy_status) {
        name = "屠馗";
        sect = "锻玄宗";
        exclusive_destinies[REALM_LQQ] = new ExclusiveDestinyLQQ(this);
        exclusive_destinies[REALM_ZJQ] = new ExclusiveDestinyZJQ(this);
        exclusive_destinies[REALM_JDQ] = new ExclusiveDestinyJDQ(this);
        exclusive_destinies[REALM_YYQ] = new ExclusiveDestinyYYQ(this);
        exclusive_destinies[REALM_HSQ] = new ExclusiveDestinyHSQ(this);
        BaseDestiny::registerDestiny(REALM_LQQ, "锻躯之道", [](BaseRole* role) {
            return new ExclusiveDestinyLQQ(role);
        });
        BaseDestiny::registerDestiny(REALM_ZJQ, "盛气凌人", [](BaseRole* role) {
            return new ExclusiveDestinyZJQ(role);
        });
        BaseDestiny::registerDestiny(REALM_JDQ, "搏命之勇", [](BaseRole* role) {
            return new ExclusiveDestinyJDQ(role);
        });
        BaseDestiny::registerDestiny(REALM_YYQ, "崩裂之拳", [](BaseRole* role) {
            return new ExclusiveDestinyYYQ(role);
        });
        BaseDestiny::registerDestiny(REALM_HSQ, "猛攻之姿", [](BaseRole* role) {
            return new ExclusiveDestinyHSQ(role);
        });
    }
    ~RoleDxTukui() = default;
    static bool registered;
};


#endif // DX_TUKUI_H