#include "dx_lqq.h"

const std::string Card_dx_lqq_xueqifanggang::name = "血气方刚";
bool Card_dx_lqq_xueqifanggang::registered = BaseCard::registerCard(Card_dx_lqq_xueqifanggang::name, Card_dx_lqq_xueqifanggang::create);
/*
耗2/3/4生命，8/10/12攻，耗1灵气：追加4/6/8攻
*/
Card_dx_lqq_xueqifanggang::Card_dx_lqq_xueqifanggang(int level, int position) : BaseCard(level, position) {
    card_name = "血气方刚";
    is_attacking = true;
    switch (level) {
        case 1:
            attack = 8;
            health_cost = 2;
            break;
        case 2:
            attack = 10;
            health_cost = 3;
            break;
        case 3:
            attack = 12;
            health_cost = 4;
            break;
    }
    is_health_cost = true;
}

Card_dx_lqq_xueqifanggang* Card_dx_lqq_xueqifanggang::Clone() const {
    return new Card_dx_lqq_xueqifanggang(*this);
}

Card_dx_lqq_xueqifanggang::Card_dx_lqq_xueqifanggang(const Card_dx_lqq_xueqifanggang& other) : BaseCard(other) {}

int Card_dx_lqq_xueqifanggang::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
    if (LingQiCostMax(my_status, 1)) {
        Attack(my_status, enemy_status, 4, card_sp_attr);
    }
    return 0;
}

BaseCard* Card_dx_lqq_xueqifanggang::create(int level, int position) {
    return new Card_dx_lqq_xueqifanggang(level, position);
}



const std::string Card_dx_lqq_qianjinzhui::name = "千斤坠";
bool Card_dx_lqq_qianjinzhui::registered = BaseCard::registerCard(Card_dx_lqq_qianjinzhui::name, Card_dx_lqq_qianjinzhui::create);
/*
6/9/12攻，随机减1层负面状态
*/
Card_dx_lqq_qianjinzhui::Card_dx_lqq_qianjinzhui(int level, int position) : BaseCard(level, position) {
    card_name = "千斤坠";
    is_attacking = true;
    switch (level) {
        case 1:
            attack = 6;
            break;
        case 2:
            attack = 9;
            break;
        case 3:
            attack = 12;
            break;
    }
}

Card_dx_lqq_qianjinzhui* Card_dx_lqq_qianjinzhui::Clone() const {
    return new Card_dx_lqq_qianjinzhui(*this);
}

Card_dx_lqq_qianjinzhui::Card_dx_lqq_qianjinzhui(const Card_dx_lqq_qianjinzhui& other) : BaseCard(other) {}

int Card_dx_lqq_qianjinzhui::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
    DebuffRandomReduce(enemy_status, 1);
    return 0;
}

BaseCard* Card_dx_lqq_qianjinzhui::create(int level, int position) {
    return new Card_dx_lqq_qianjinzhui(level, position);
}



const std::string Card_dx_lqq_pokongzhua::name = "破空爪";
bool Card_dx_lqq_pokongzhua::registered = BaseCard::registerCard(Card_dx_lqq_pokongzhua::name, Card_dx_lqq_pokongzhua::create);
/*
耗1灵气，12/15/18攻，自身加1层内伤
*/
Card_dx_lqq_pokongzhua::Card_dx_lqq_pokongzhua(int level, int position) : BaseCard(level, position) {
    card_name = "破空爪";
    is_attacking = true;
    switch (level) {
        case 1:
            attack = 12;
            break;
        case 2:
            attack = 15;
            break;
        case 3:
            attack = 18;
            break;
    }
    ling_qi_cost = 1;
}

Card_dx_lqq_pokongzhua* Card_dx_lqq_pokongzhua::Clone() const {
    return new Card_dx_lqq_pokongzhua(*this);
}

Card_dx_lqq_pokongzhua::Card_dx_lqq_pokongzhua(const Card_dx_lqq_pokongzhua& other) : BaseCard(other) {}

int Card_dx_lqq_pokongzhua::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
    my_status->debuffs[DEBUFF_NEI_SHANG]->add(1);
    return 0;
}

BaseCard* Card_dx_lqq_pokongzhua::create(int level, int position) {
    return new Card_dx_lqq_pokongzhua(level, position);
}



const std::string Card_dx_lqq_zhaoqipengbo::name = "朝气蓬勃";
bool Card_dx_lqq_zhaoqipengbo::registered = BaseCard::registerCard(Card_dx_lqq_zhaoqipengbo::name, Card_dx_lqq_zhaoqipengbo::create);
/*
6/9/12攻（每有1层气势多1攻），耗1灵气：气势+2
*/
Card_dx_lqq_zhaoqipengbo::Card_dx_lqq_zhaoqipengbo(int level, int position) : BaseCard(level, position) {
    card_name = "朝气蓬勃";
    is_attacking = true;
    switch (level) {
        case 1:
            attack = 6;
            break;
        case 2:
            attack = 9;
            break;
        case 3:
            attack = 12;
            break;
    }
}

Card_dx_lqq_zhaoqipengbo* Card_dx_lqq_zhaoqipengbo::Clone() const {
    return new Card_dx_lqq_zhaoqipengbo(*this);
}

Card_dx_lqq_zhaoqipengbo::Card_dx_lqq_zhaoqipengbo(const Card_dx_lqq_zhaoqipengbo& other) : BaseCard(other) {}

int Card_dx_lqq_zhaoqipengbo::Effect(Status* my_status, Status* enemy_status) {
    if (LingQiCostMax(my_status, 1)) {
        my_status->buffs[BUFF_QI_SHI]->add(2);
    }
    int temp_attack = my_status->buffs[BUFF_QI_SHI]->getValue();
    Attack(my_status, enemy_status, attack + temp_attack, card_sp_attr);
    return 0;
}

BaseCard* Card_dx_lqq_zhaoqipengbo::create(int level, int position) {
    return new Card_dx_lqq_zhaoqipengbo(level, position);
}



const std::string Card_dx_lqq_qishi::name = "起势";
bool Card_dx_lqq_qishi::registered = BaseCard::registerCard(Card_dx_lqq_qishi::name, Card_dx_lqq_qishi::create);
/*
2/5/8攻，灵气+1，气势+2
*/
Card_dx_lqq_qishi::Card_dx_lqq_qishi(int level, int position) : BaseCard(level, position) {
    card_name = "起势";
    is_attacking = true;
    switch (level) {
        case 1:
            attack = 2;
            break;
        case 2:
            attack = 5;
            break;
        case 3:
            attack = 8;
            break;
    }
}

Card_dx_lqq_qishi* Card_dx_lqq_qishi::Clone() const {
    return new Card_dx_lqq_qishi(*this);
}

Card_dx_lqq_qishi::Card_dx_lqq_qishi(const Card_dx_lqq_qishi& other) : BaseCard(other) {}

int Card_dx_lqq_qishi::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
    my_status->ling_qi->add(1);
    my_status->buffs[BUFF_QI_SHI]->add(2);
    return 0;
}

BaseCard* Card_dx_lqq_qishi::create(int level, int position) {
    return new Card_dx_lqq_qishi(level, position);
}



const std::string Card_dx_lqq_luochapu::name = "罗刹扑";
bool Card_dx_lqq_luochapu::registered = BaseCard::registerCard(Card_dx_lqq_luochapu::name, Card_dx_lqq_luochapu::create);

/*
8/11/14攻，灵气+1，自身加1层外伤
*/
Card_dx_lqq_luochapu::Card_dx_lqq_luochapu(int level, int position) : BaseCard(level, position) {
    card_name = "罗刹扑";
    is_attacking = true;
    switch (level) {
        case 1:
            attack = 8;
            break;
        case 2:
            attack = 11;
            break;
        case 3:
            attack = 14;
            break;
    }
}

Card_dx_lqq_luochapu::Card_dx_lqq_luochapu(const Card_dx_lqq_luochapu& other) : BaseCard(other) {}

Card_dx_lqq_luochapu* Card_dx_lqq_luochapu::Clone() const {
    return new Card_dx_lqq_luochapu(*this);
}

int Card_dx_lqq_luochapu::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
    my_status->ling_qi->add(1);
    my_status->debuffs[DEBUFF_WAI_SHANG]->add(1);
    return 0;
}

BaseCard* Card_dx_lqq_luochapu::create(int level, int position) {
    return new Card_dx_lqq_luochapu(level, position);
}



const std::string Card_dx_lqq_baoqifa::name = "抱气法";
bool Card_dx_lqq_baoqifa::registered = BaseCard::registerCard(Card_dx_lqq_baoqifa::name, Card_dx_lqq_baoqifa::create);

/*
灵气+1，体魄+2，生命+1/4/7
*/
Card_dx_lqq_baoqifa::Card_dx_lqq_baoqifa(int level, int position) : BaseCard(level, position) {
    card_name = "抱气法";
    is_attacking = false;
    card_tag[TI_PO_CARD] = true;
}

Card_dx_lqq_baoqifa::Card_dx_lqq_baoqifa(const Card_dx_lqq_baoqifa& other) : BaseCard(other) {}

Card_dx_lqq_baoqifa* Card_dx_lqq_baoqifa::Clone() const {
    return new Card_dx_lqq_baoqifa(*this);
}

int Card_dx_lqq_baoqifa::Effect(Status* my_status, Status* enemy_status) {
    my_status->ling_qi->add(1);
    my_status->ti_po->add(2);
    int health_gain = 0;
    switch (level) {
        case 1:
            health_gain = 1;
            break;
        case 2:
            health_gain = 4;
            break;
        case 3:
            health_gain = 7;
            break;
    }
    my_status->health->add(health_gain);
    return 0;
}

BaseCard* Card_dx_lqq_baoqifa::create(int level, int position) {
    return new Card_dx_lqq_baoqifa(level, position);
}



const std::string Card_dx_lqq_pishanzhang::name = "劈山掌";
bool Card_dx_lqq_pishanzhang::registered = BaseCard::registerCard(Card_dx_lqq_pishanzhang::name, Card_dx_lqq_pishanzhang::create);

/*
耗4生命，10/13/16攻，每有2体魄此牌少耗1生命
*/
Card_dx_lqq_pishanzhang::Card_dx_lqq_pishanzhang(int level, int position) : BaseCard(level, position) {
    card_name = "劈山掌";
    is_attacking = true;
    switch (level) {
        case 1:
            attack = 10;
            break;
        case 2:
            attack = 13;
            break;
        case 3:
            attack = 16;
            break;
    }
    is_health_cost = true;
    is_health_cost_modifiable = true;
    health_cost = 4;
}

Card_dx_lqq_pishanzhang::Card_dx_lqq_pishanzhang(const Card_dx_lqq_pishanzhang& other) : BaseCard(other) {}

Card_dx_lqq_pishanzhang* Card_dx_lqq_pishanzhang::Clone() const {
    return new Card_dx_lqq_pishanzhang(*this);
}

int Card_dx_lqq_pishanzhang::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
    return 0;
}

int Card_dx_lqq_pishanzhang::HealthCostModify(Status* my_status, Status* enemy_status) {
    int temp_health_cost = health_cost;
    temp_health_cost -= my_status->ti_po->getValue() / 2;
    if (temp_health_cost < 0) {
        temp_health_cost = 0;
    }
    return temp_health_cost;
}

BaseCard* Card_dx_lqq_pishanzhang::create(int level, int position) {
    return new Card_dx_lqq_pishanzhang(level, position);
}



const std::string Card_dx_lqq_duanquan::name = "锻拳";
bool Card_dx_lqq_duanquan::registered = BaseCard::registerCard(Card_dx_lqq_duanquan::name, Card_dx_lqq_duanquan::create);

/*
6/9/12攻，体魄+1
*/
Card_dx_lqq_duanquan::Card_dx_lqq_duanquan(int level, int position) : BaseCard(level, position) {
    card_name = "锻拳";
    is_attacking = true;
    switch (level) {
        case 1:
            attack = 6;
            break;
        case 2:
            attack = 9;
            break;
        case 3:
            attack = 12;
            break;
    }
    card_tag[TI_PO_CARD] = true;
}

Card_dx_lqq_duanquan::Card_dx_lqq_duanquan(const Card_dx_lqq_duanquan& other) : BaseCard(other) {}

Card_dx_lqq_duanquan* Card_dx_lqq_duanquan::Clone() const {
    return new Card_dx_lqq_duanquan(*this);
}

int Card_dx_lqq_duanquan::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
    my_status->ti_po->add(1);
    return 0;
}

BaseCard* Card_dx_lqq_duanquan::create(int level, int position) {
    return new Card_dx_lqq_duanquan(level, position);
}



const std::string Card_dx_lqq_bengquan_tan::name = "崩拳·弹";
bool Card_dx_lqq_bengquan_tan::registered = BaseCard::registerCard(Card_dx_lqq_bengquan_tan::name, Card_dx_lqq_bengquan_tan::create);

/*
耗2生命，7/11/14攻，下一张崩拳耗生命时加回所耗生命
*/
Card_dx_lqq_bengquan_tan::Card_dx_lqq_bengquan_tan(int level, int position) : BaseCard(level, position) {
    card_name = "崩拳·弹";
    is_attacking = true;
    switch (level) {
        case 1:
            attack = 7;
            break;
        case 2:
            attack = 11;
            break;
        case 3:
            attack = 14;
            break;
    }
    is_health_cost = true;
    health_cost = 2;
    card_tag[BENG_QUAN_CARD] = true;
}

Card_dx_lqq_bengquan_tan::Card_dx_lqq_bengquan_tan(const Card_dx_lqq_bengquan_tan& other) : BaseCard(other) {}

Card_dx_lqq_bengquan_tan* Card_dx_lqq_bengquan_tan::Clone() const {
    return new Card_dx_lqq_bengquan_tan(*this);
}

int Card_dx_lqq_bengquan_tan::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
    my_status->task_quene_before_effect->addTask(
        [my_status](BaseCard* card){
            my_status->health->add(card->health_cost);
        },
        [](BaseCard* card){ return card->card_tag[BENG_QUAN_CARD] ? true : false; },
        [](BaseCard* card){ return true; },
        REMARK_BENG_QUAN
    );
    return 0;
}

BaseCard* Card_dx_lqq_bengquan_tan::create(int level, int position) {
    return new Card_dx_lqq_bengquan_tan(level, position);
}



const std::string Card_dx_lqq_bengquan_feng::name = "崩拳·封";
bool Card_dx_lqq_bengquan_feng::registered = BaseCard::registerCard(Card_dx_lqq_bengquan_feng::name, Card_dx_lqq_bengquan_feng::create);
/*
耗3生命，7/9/11攻，防+2/3/4（下一张崩拳也附加此效果）
*/
Card_dx_lqq_bengquan_feng::Card_dx_lqq_bengquan_feng(int level, int position) : BaseCard(level, position) {
    card_name = "崩拳·封";
    is_attacking = true;
    switch (level) {
        case 1:
            attack = 7;
            break;
        case 2:
            attack = 9;
            break;
        case 3:
            attack = 11;
            break;
    }
    is_health_cost = true;
    health_cost = 3;
    card_tag[BENG_QUAN_CARD] = true;
}

Card_dx_lqq_bengquan_feng* Card_dx_lqq_bengquan_feng::Clone() const {
    return new Card_dx_lqq_bengquan_feng(*this);
}

Card_dx_lqq_bengquan_feng::Card_dx_lqq_bengquan_feng(const Card_dx_lqq_bengquan_feng& other) : BaseCard(other) {}

int Card_dx_lqq_bengquan_feng::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
    int defense = 0;
    switch (level) {
        case 1:
            defense = 2;
            break;
        case 2:
            defense = 3;
            break;
        case 3:
            defense = 4;
            break;
    }
    my_status->defense->add(defense);
    my_status->task_quene_before_effect->addTask(
        [my_status, defense](BaseCard* card){
            my_status->defense->add(defense);
        },
        [](BaseCard* card){ return card->card_tag[BENG_QUAN_CARD] ? true : false; },
        [](BaseCard* card){ return true; },
        REMARK_BENG_QUAN
    );
    return 0;
}

BaseCard* Card_dx_lqq_bengquan_feng::create(int level, int position) {
    return new Card_dx_lqq_bengquan_feng(level, position);
}



const std::string Card_dx_lqq_bengquan_chuo::name = "崩拳·戳";
bool Card_dx_lqq_bengquan_chuo::registered = BaseCard::registerCard(Card_dx_lqq_bengquan_chuo::name, Card_dx_lqq_bengquan_chuo::create);
/*
9/11/13攻 下一张崩拳多2/3/4攻
*/
Card_dx_lqq_bengquan_chuo::Card_dx_lqq_bengquan_chuo(int level, int position) : BaseCard(level, position) {
    card_name = "崩拳·戳";
    is_attacking = true;
    switch (level) {
        case 1:
            attack = 9;
            break;
        case 2:
            attack = 11;
            break;
        case 3:
            attack = 13;
            break;
    }
    is_health_cost = true;
    health_cost = 3;
    card_tag[BENG_QUAN_CARD] = true;
}

Card_dx_lqq_bengquan_chuo* Card_dx_lqq_bengquan_chuo::Clone() const {
    return new Card_dx_lqq_bengquan_chuo(*this);
}

Card_dx_lqq_bengquan_chuo::Card_dx_lqq_bengquan_chuo(const Card_dx_lqq_bengquan_chuo& other) : BaseCard(other) {}

int Card_dx_lqq_bengquan_chuo::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
    int temp_status = 0;
    switch (level) {
        case 1:
            temp_status = 2;
            break;
        case 2:
            temp_status = 3;
            break;
        case 3:
            temp_status = 4;
            break;
    }
    my_status->task_quene_before_effect->addTask(
        [my_status, temp_status](BaseCard* card){
            card->card_sp_attr[CARD_SP_ATTR_DUO_GONG] += temp_status;
            my_status->task_quene_after_effect->addTask(
                [my_status, temp_status](BaseCard* card){
                    card->card_sp_attr[CARD_SP_ATTR_DUO_GONG] -= temp_status;
                },
                [](BaseCard* card){ return true; },
                [](BaseCard* card){ return true; }
            );
        },
        [](BaseCard* card){ return card->card_tag[BENG_QUAN_CARD] && card->is_attacking ? true : false; },
        [](BaseCard* card){ return true; },
        REMARK_BENG_QUAN
    );
    
    return 0;
}

BaseCard* Card_dx_lqq_bengquan_chuo::create(int level, int position) {
    return new Card_dx_lqq_bengquan_chuo(level, position);
}





