#ifndef ZSXM_ZJQ_H
#define ZSXM_ZJQ_H
#include "../base_card.h"

// 专属仙命_筑基期

/*
锻玄宗_屠馗 专属仙命卡 盛气凌人
消耗2生命，气势+2/3/4，持续：每减一点气势时向对方造成2伤害
*/
class Card_zsxm_zjq_shengqilingren : public BaseCard {
public:
    Card_zsxm_zjq_shengqilingren(int level, int position) : BaseCard(level, position) {
        card_name = "盛气凌人";
        is_attacking = false;
        health_cost = 2;
        card_tag[CHI_XU_CARD] = true;
    }
    int Effect(Status* my_status, Status* enemy_status) {
        int qi_shi_gain = 0;
        switch (level) {
            case 1:
                qi_shi_gain = 2;
                break;
            case 2:
                qi_shi_gain = 3;
                break;
            case 3:
                qi_shi_gain = 4;
                break;
        }
        my_status->buffs[BUFF_QI_SHI]->add(qi_shi_gain);
        my_status->buffs[BUFF_QI_SHI]->sub_task_quene->addTask(
            [my_status, enemy_status](int qi_shi_sub_val){
                Damage(my_status, enemy_status, 2 * qi_shi_sub_val);
            },
            [](int){ return true; },
            [](int){ return false; }
        );
        return 0;
    }
};

#endif // ZSXM_ZJQ_H