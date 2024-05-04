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
            this->role->my_status->deck->AddCardtoHand(new Card_zsxm_zjq_shengqilingren(1, 0));
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
            role->my_status->ti_po_max->setValue(role->my_status->ti_po_max->getValue() + 2);
            return 0;
        }
        int BattleStartEffect() override {
            role->my_status->buffs[BUFF_JIA_GONG]->add(1);
            role->my_status->debuffs[DEBUFF_WAI_SHANG]->add(1);
            return 0;
        }
    };

    // ！！未完成
    class ExclusiveDestinyYYQ : public BaseDestiny {
    public:
        ExclusiveDestinyYYQ(BaseRole* role) : BaseDestiny(role) {
            name = "崩裂之拳";
            realm = REALM_YYQ;
        }
        ~ExclusiveDestinyYYQ() = default;
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
            role->my_status->ti_po_max->setValue(role->my_status->ti_po_max->getValue() + 4);
            return 0;
        }
        int BattleStartEffect() override {
            role->my_status->task_quene_after_effect->addTask( 
                [this](BaseCard* card){ Attack(this->role->my_status, this->role->enemy_status, 3); },
                [](BaseCard* card){ return card->card_tag[TI_PO_CARD] ? true : false; },
                [](BaseCard* card){ return true; },
                REMARK_BENG_QUAN
            );
            return 0;
        }
    };

    RoleDxTukui(Status* my_status, Status* enemy_status) : BaseRole(my_status, enemy_status) {
        name = "屠馗";
        sect = SECT_DX;
        exclusive_destinies[REALM_LQQ] = new ExclusiveDestinyLQQ(this);
        exclusive_destinies[REALM_ZJQ] = new ExclusiveDestinyZJQ(this);
        exclusive_destinies[REALM_JDQ] = new ExclusiveDestinyJDQ(this);
        exclusive_destinies[REALM_YYQ] = new ExclusiveDestinyYYQ(this);
        exclusive_destinies[REALM_HSQ] = new ExclusiveDestinyHSQ(this);
    }
    ~RoleDxTukui() = default;

    std::string name = "屠馗";

};


#endif // DX_TUKUI_H