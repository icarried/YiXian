#include "zsxm_zjq.h"

const std::string Card_zsxm_zjq_shengqilingren::name = "盛气凌人";
bool Card_zsxm_zjq_shengqilingren::registered = BaseCard::registerCard(Card_zsxm_zjq_shengqilingren::name, Card_zsxm_zjq_shengqilingren::create);

/*
锻玄宗_屠馗 专属仙命卡 盛气凌人
消耗2生命，气势+2/3/4，持续：每减一点气势时向对方造成2伤害
*/
Card_zsxm_zjq_shengqilingren::Card_zsxm_zjq_shengqilingren(int level, int position) : BaseCard(level, position) {
    card_name = "盛气凌人";
    is_attacking = false;
    health_cost = 2;
    card_tag[CHI_XU_CARD] = true;
}

Card_zsxm_zjq_shengqilingren::Card_zsxm_zjq_shengqilingren(const Card_zsxm_zjq_shengqilingren& other) : BaseCard(other) {}

Card_zsxm_zjq_shengqilingren* Card_zsxm_zjq_shengqilingren::Clone() const {
    return new Card_zsxm_zjq_shengqilingren(*this);
}

int Card_zsxm_zjq_shengqilingren::Effect(Status* my_status, Status* enemy_status) {
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

BaseCard* Card_zsxm_zjq_shengqilingren::create(int level, int position) {
    return new Card_zsxm_zjq_shengqilingren(level, position);
}



const std::string Card_zsxm_zjq_duantibuxi::name = "锻体不息";
bool Card_zsxm_zjq_duantibuxi::registered = BaseCard::registerCard(Card_zsxm_zjq_duantibuxi::name, Card_zsxm_zjq_duantibuxi::create);

/*
锻玄宗_小布 专属仙命卡 锻体不息
4/6/8攻, 体魄加3/4/5, 生命加3/4/5
*/
Card_zsxm_zjq_duantibuxi::Card_zsxm_zjq_duantibuxi(int level, int position) : BaseCard(level, position) {
    card_name = "锻体不息";
    is_attacking = true;
    attack = 2 * level + 2;
    card_tag[TI_PO_CARD] = true;
}

Card_zsxm_zjq_duantibuxi::Card_zsxm_zjq_duantibuxi(const Card_zsxm_zjq_duantibuxi& other) : BaseCard(other) {}

Card_zsxm_zjq_duantibuxi* Card_zsxm_zjq_duantibuxi::Clone() const {
    return new Card_zsxm_zjq_duantibuxi(*this);
}

int Card_zsxm_zjq_duantibuxi::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
    int ti_po_gain = 0;
    int health_gain = 0;
    switch (level) {
        case 1:
            ti_po_gain = 3;
            health_gain = 3;
            break;
        case 2:
            ti_po_gain = 4;
            health_gain = 4;
            break;
        case 3:
            ti_po_gain = 5;
            health_gain = 5;
            break;
    }
    my_status->ti_po->add(ti_po_gain);
    my_status->health->add(health_gain);
    return 0;
}

BaseCard* Card_zsxm_zjq_duantibuxi::create(int level, int position) {
    return new Card_zsxm_zjq_duantibuxi(level, position);
}