#include "dx_hsq.h"

const std::string Card_dx_hsq_tiandihaodang::name = "天地浩荡";
bool Card_dx_hsq_tiandihaodang::registered = BaseCard::registerCard(Card_dx_hsq_tiandihaodang::name, Card_dx_hsq_tiandihaodang::create);
/*
10/12/14攻，生命+4/6/8，身法+4/5/6（每剩1气势多2）
*/
Card_dx_hsq_tiandihaodang::Card_dx_hsq_tiandihaodang(int level, int position) : BaseCard(level, position) {
    card_name = "天地浩荡";
    is_attacking = true;
    switch (level) {
        case 1:
            attack = 10;
            break;
        case 2:
            attack = 12;
            break;
        case 3:
            attack = 14;
            break;
    }
}

Card_dx_hsq_tiandihaodang* Card_dx_hsq_tiandihaodang::Clone() const {
    return new Card_dx_hsq_tiandihaodang(*this);
}

Card_dx_hsq_tiandihaodang::Card_dx_hsq_tiandihaodang(const Card_dx_hsq_tiandihaodang& other) : BaseCard(other) {}

int Card_dx_hsq_tiandihaodang::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
    int health_gain = 0;
    int shen_fa_gain = 0;
    switch (level) {
        case 1:
            health_gain = 4;
            shen_fa_gain = 4;
            break;
        case 2:
            health_gain = 6;
            shen_fa_gain = 5;
            break;
        case 3:
            health_gain = 8;
            shen_fa_gain = 6;
            break;
    }
    my_status->health->add(health_gain);
    my_status->buffs[BUFF_SHEN_FA]->add(shen_fa_gain + my_status->buffs[BUFF_QI_SHI]->getValue() * 2);
    return 0;
}

BaseCard* Card_dx_hsq_tiandihaodang::create(int level, int position) {
    return new Card_dx_hsq_tiandihaodang(level, position);
}



const std::string Card_dx_hsq_xiuluohou::name = "修罗吼";
bool Card_dx_hsq_xiuluohou::registered = BaseCard::registerCard(Card_dx_hsq_xiuluohou::name, Card_dx_hsq_xiuluohou::create);

/*
双方各加4/6/8层内伤，自身每有2层负面状态加1灵气和1生命
*/
Card_dx_hsq_xiuluohou::Card_dx_hsq_xiuluohou(int level, int position) : BaseCard(level, position) {
    card_name = "修罗吼";
    is_attacking = false;
}

Card_dx_hsq_xiuluohou* Card_dx_hsq_xiuluohou::Clone() const {
    return new Card_dx_hsq_xiuluohou(*this);
}

Card_dx_hsq_xiuluohou::Card_dx_hsq_xiuluohou(const Card_dx_hsq_xiuluohou& other) : BaseCard(other) {}

int Card_dx_hsq_xiuluohou::Effect(Status* my_status, Status* enemy_status) {
    int temp_debuff = 0;
    switch (level) {
        case 1:
            temp_debuff = 4;
            break;
        case 2:
            temp_debuff = 6;
            break;
        case 3:
            temp_debuff = 8;
            break;
    }
    my_status->debuffs[DEBUFF_NEI_SHANG]->add(temp_debuff);
    enemy_status->debuffs[DEBUFF_NEI_SHANG]->add(temp_debuff);
    int debuff_total = DebuffTotal(my_status);
    int temp_ling_qi = debuff_total / 2;
    int temp_health = debuff_total / 2;
    my_status->ling_qi->add(temp_ling_qi);
    my_status->health->add(temp_health);
    return 0;
}

BaseCard* Card_dx_hsq_xiuluohou::create(int level, int position) {
    return new Card_dx_hsq_xiuluohou(level, position);
}



const std::string Card_dx_hsq_weizhensifang::name = "威震四方";
bool Card_dx_hsq_weizhensifang::registered = BaseCard::registerCard(Card_dx_hsq_weizhensifang::name, Card_dx_hsq_weizhensifang::create);

/*
防+8/10/12，气势上限+3/4/5，气势+3/4/5
*/
Card_dx_hsq_weizhensifang::Card_dx_hsq_weizhensifang(int level, int position) : BaseCard(level, position) {
    card_name = "威震四方";
    is_attacking = false;
}

Card_dx_hsq_weizhensifang* Card_dx_hsq_weizhensifang::Clone() const {
    return new Card_dx_hsq_weizhensifang(*this);
}

Card_dx_hsq_weizhensifang::Card_dx_hsq_weizhensifang(const Card_dx_hsq_weizhensifang& other) : BaseCard(other) {}

int Card_dx_hsq_weizhensifang::Effect(Status* my_status, Status* enemy_status) {
    int defence = 0;
    int qi_shi_max_gain = 0;
    int qi_shi_gain = 0;
    switch (level) {
        case 1:
            defence = 8;
            qi_shi_max_gain = 3;
            qi_shi_gain = 3;
            break;
        case 2:
            defence = 10;
            qi_shi_max_gain = 4;
            qi_shi_gain = 4;
            break;
        case 3:
            defence = 12;
            qi_shi_max_gain = 5;
            qi_shi_gain = 5;
            break;
    }
    my_status->defense->add(defence);
    my_status->buffs[BUFF_QI_SHI_MAX]->add(qi_shi_max_gain);
    my_status->buffs[BUFF_QI_SHI]->add(qi_shi_gain);
    return 0;
}

BaseCard* Card_dx_hsq_weizhensifang::create(int level, int position) {
    return new Card_dx_hsq_weizhensifang(level, position);
}



const std::string Card_dx_hsq_xuanxinzhanpo::name = "玄心斩魄";
bool Card_dx_hsq_xuanxinzhanpo::registered = BaseCard::registerCard(Card_dx_hsq_xuanxinzhanpo::name, Card_dx_hsq_xuanxinzhanpo::create);

/*
耗1灵气，向对方施加自身已有的负面状态各2层，10/15/20攻（攻击时自身负面状态的效果当作气势）
*/
Card_dx_hsq_xuanxinzhanpo::Card_dx_hsq_xuanxinzhanpo(int level, int position) : BaseCard(level, position) {
    card_name = "玄心斩魄";
    ling_qi_cost = 1;
    is_attacking = true;
    switch (level) {
        case 1:
            attack = 8;
            break;
        case 2:
            attack = 14;
            break;
        case 3:
            attack = 20;
            break;
    }
}

Card_dx_hsq_xuanxinzhanpo* Card_dx_hsq_xuanxinzhanpo::Clone() const {
    return new Card_dx_hsq_xuanxinzhanpo(*this);
}

Card_dx_hsq_xuanxinzhanpo::Card_dx_hsq_xuanxinzhanpo(const Card_dx_hsq_xuanxinzhanpo& other) : BaseCard(other) {}

int Card_dx_hsq_xuanxinzhanpo::Effect(Status* my_status, Status* enemy_status) {
    for (int debuff_type = 0; debuff_type < DEBUFF_END_INDEX; debuff_type++) {
        if (my_status->debuffs[debuff_type]->getValue() > 0) {
            enemy_status->debuffs[debuff_type]->add(2);
        }
    }
    // 将debuff的值暂时转移到新的数组，并累加到临时气势上，气势上限临时调整
    int temp_qi_shi = 0;
    int temp_qi_shi_max = 9999;
    int saved_qi_shi_max = my_status->buffs[BUFF_QI_SHI_MAX]->getValue(); // 保存原来的气势上限
    my_status->buffs[BUFF_QI_SHI_MAX]->setValue(temp_qi_shi_max);
    // 保存原来的气势上限
    int saved_debuffs[DEBUFF_END_INDEX];
    for (int debuff_type = 0; debuff_type < DEBUFF_END_INDEX; debuff_type++) {
        saved_debuffs[debuff_type] = my_status->debuffs[debuff_type]->getValue();
        temp_qi_shi += saved_debuffs[debuff_type];
        my_status->debuffs[debuff_type]->setValue(0);
    }
    my_status->buffs[BUFF_QI_SHI]->add(temp_qi_shi);
    Attack(my_status, enemy_status, attack, card_sp_attr);
    // 将debuff的值从新的数组转回到原来的数组
    for (int debuff_type = 0; debuff_type < DEBUFF_END_INDEX; debuff_type++) {
        my_status->debuffs[debuff_type]->setValue(saved_debuffs[debuff_type]);
    }
    my_status->buffs[BUFF_QI_SHI]->sub(temp_qi_shi);
    my_status->buffs[BUFF_QI_SHI_MAX]->setValue(saved_qi_shi_max);
    return 0;
}

BaseCard* Card_dx_hsq_xuanxinzhanpo::create(int level, int position) {
    return new Card_dx_hsq_xuanxinzhanpo(level, position);
}



const std::string Card_dx_hsq_baishapojingzhang::name = "百杀破境掌";
bool Card_dx_hsq_baishapojingzhang::registered = BaseCard::registerCard(Card_dx_hsq_baishapojingzhang::name, Card_dx_hsq_baishapojingzhang::create);

/*
2/4/6攻（本轮战斗每加过4/3/2体魄多1攻），每有25体魄追加1次攻击
*/
Card_dx_hsq_baishapojingzhang::Card_dx_hsq_baishapojingzhang(int level, int position) : BaseCard(level, position) {
    card_name = "百杀破境掌";
    is_attacking = true;
    switch (level) {
        case 1:
            attack = 2;
            break;
        case 2:
            attack = 4;
            break;
        case 3:
            attack = 6;
            break;
    }
    card_tag[TI_PO_CARD] = true;
}

Card_dx_hsq_baishapojingzhang* Card_dx_hsq_baishapojingzhang::Clone() const {
    return new Card_dx_hsq_baishapojingzhang(*this);
}

Card_dx_hsq_baishapojingzhang::Card_dx_hsq_baishapojingzhang(const Card_dx_hsq_baishapojingzhang& other) : BaseCard(other) {}

int Card_dx_hsq_baishapojingzhang::Effect(Status* my_status, Status* enemy_status) {
    int temp_attack = 0;
    switch (level) {
        case 1:
            temp_attack = my_status->ti_po->getAddTotal() / 4;
            break;
        case 2:
            temp_attack = my_status->ti_po->getAddTotal() / 3;
            break;
        case 3:
            temp_attack = my_status->ti_po->getAddTotal() / 2;
            break;
    }
    int ex_attack_times = my_status->ti_po->getValue() / 25;
    Attack(my_status, enemy_status, attack + temp_attack, card_sp_attr);
    for (int i = 0; i < ex_attack_times; i++) {
        Attack(my_status, enemy_status, attack + temp_attack, card_sp_attr);
    }
    return 0;
}

BaseCard* Card_dx_hsq_baishapojingzhang::create(int level, int position) {
    return new Card_dx_hsq_baishapojingzhang(level, position);
}



const std::string Card_dx_hsq_duanshenkaihai::name = "锻神开海";
bool Card_dx_hsq_duanshenkaihai::registered = BaseCard::registerCard(Card_dx_hsq_duanshenkaihai::name, Card_dx_hsq_duanshenkaihai::create);

/*
4/8/12攻，体魄+3/4/5，体魄≥50：获得1层加攻。体魄≥65：身法+4/5/6
*/
Card_dx_hsq_duanshenkaihai::Card_dx_hsq_duanshenkaihai(int level, int position) : BaseCard(level, position) {
    card_name = "锻神开海";
    is_attacking = true;
    switch (level) {
        case 1:
            attack = 4;
            break;
        case 2:
            attack = 8;
            break;
        case 3:
            attack = 12;
            break;
    }
    card_tag[TI_PO_CARD] = true;
}

Card_dx_hsq_duanshenkaihai* Card_dx_hsq_duanshenkaihai::Clone() const {
    return new Card_dx_hsq_duanshenkaihai(*this);
}

Card_dx_hsq_duanshenkaihai::Card_dx_hsq_duanshenkaihai(const Card_dx_hsq_duanshenkaihai& other) : BaseCard(other) {}

int Card_dx_hsq_duanshenkaihai::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
    my_status->ti_po->add(level + 2);
    if (my_status->ti_po->getValue() >= 50) {
        my_status->buffs[BUFF_JIA_GONG]->add(1);
    }
    if (my_status->ti_po->getValue() >= 65) {
        my_status->buffs[BUFF_SHEN_FA]->add(level + 4);
    }
    return 0;
}

BaseCard* Card_dx_hsq_duanshenkaihai::create(int level, int position) {
    return new Card_dx_hsq_duanshenkaihai(level, position);
}



const std::string Card_dx_hsq_bengquan_jingchu::name = "崩拳·惊触";
bool Card_dx_hsq_bengquan_jingchu::registered = BaseCard::registerCard(Card_dx_hsq_bengquan_jingchu::name, Card_dx_hsq_bengquan_jingchu::create);

/*
耗8/8/8生命，10/16/22攻，使用下一张崩拳后追加1攻（本场战斗中每失去过5生命多1攻）
*/
Card_dx_hsq_bengquan_jingchu::Card_dx_hsq_bengquan_jingchu(int level, int position) : BaseCard(level, position) {
    card_name = "崩拳·惊触";
    is_attacking = true;
    switch (level) {
        case 1:
            attack = 10;
            break;
        case 2:
            attack = 16;
            break;
        case 3:
            attack = 22;
            break;
    }
    is_health_cost = true;
    health_cost = 8;
    card_tag[BENG_QUAN_CARD] = true;
}

Card_dx_hsq_bengquan_jingchu* Card_dx_hsq_bengquan_jingchu::Clone() const {
    return new Card_dx_hsq_bengquan_jingchu(*this);
}

Card_dx_hsq_bengquan_jingchu::Card_dx_hsq_bengquan_jingchu(const Card_dx_hsq_bengquan_jingchu& other) : BaseCard(other) {}

int Card_dx_hsq_bengquan_jingchu::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
    my_status->task_quene_before_effect->addTask(
        [my_status](BaseCard* card){
            my_status->task_quene_after_effect->addTask(
                [my_status](BaseCard* card){
                    int ex_attack = 1 + int(float(my_status->health->getSubTotal()) / 5);
                    Attack(my_status, my_status, ex_attack);
                },
                [](BaseCard* card){ return true; },
                [](BaseCard* card){ return true; }
            );
        },
        [](BaseCard* card){ return card->card_tag[BENG_QUAN_CARD] ? true : false; },
        [](BaseCard* card){ return true; },
        REMARK_BENG_QUAN
    );
    return 0;
}

BaseCard* Card_dx_hsq_bengquan_jingchu::create(int level, int position) {
    return new Card_dx_hsq_bengquan_jingchu(level, position);
}



const std::string Card_dx_hsq_bengquan_shanji::name = "崩拳·闪击";
bool Card_dx_hsq_bengquan_shanji::registered = BaseCard::registerCard(Card_dx_hsq_bengquan_shanji::name, Card_dx_hsq_bengquan_shanji::create);

/*
耗7生命，5/7/9攻，身法+7/8/9（下一张崩拳也附加此效果）
*/
Card_dx_hsq_bengquan_shanji::Card_dx_hsq_bengquan_shanji(int level, int position) : BaseCard(level, position) {
    card_name = "崩拳·闪击";
    is_attacking = true;
    switch (level) {
        case 1:
            attack = 5;
            break;
        case 2:
            attack = 7;
            break;
        case 3:
            attack = 9;
            break;
    }
    is_health_cost = true;
    health_cost = 7;
    card_tag[BENG_QUAN_CARD] = true;
}

Card_dx_hsq_bengquan_shanji* Card_dx_hsq_bengquan_shanji::Clone() const {
    return new Card_dx_hsq_bengquan_shanji(*this);
}

Card_dx_hsq_bengquan_shanji::Card_dx_hsq_bengquan_shanji(const Card_dx_hsq_bengquan_shanji& other) : BaseCard(other) {}

int Card_dx_hsq_bengquan_shanji::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
    int temp_status = 0;
    switch (level) {
        case 1:
            temp_status = 7;
            break;
        case 2:
            temp_status = 8;
            break;
        case 3:
            temp_status = 9;
            break;
    }
    my_status->buffs[BUFF_SHEN_FA]->add(temp_status);
    my_status->task_quene_before_effect->addTask(
        [my_status, temp_status](BaseCard* card){
            my_status->buffs[BUFF_SHEN_FA]->add(temp_status);
        },
        [](BaseCard* card){ return card->card_tag[BENG_QUAN_CARD] ? true : false; },
        [](BaseCard* card){ return true; },
        REMARK_BENG_QUAN
    );
    return 0;
}

BaseCard* Card_dx_hsq_bengquan_shanji::create(int level, int position) {
    return new Card_dx_hsq_bengquan_shanji(level, position);
}
