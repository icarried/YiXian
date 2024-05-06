#include "dx_zjq.h"


const std::string Card_dx_zjq_haoranzhengqi::name = "浩然正气";
bool Card_dx_zjq_haoranzhengqi::registered = BaseCard::registerCard(Card_dx_zjq_haoranzhengqi::name, Card_dx_zjq_haoranzhengqi::create);
/*
灵气+1，防+4/8/12，获得2/3/4层辟邪
*/
Card_dx_zjq_haoranzhengqi::Card_dx_zjq_haoranzhengqi(int level, int position) : BaseCard(level, position) {
    card_name = "浩然正气";
    is_attacking = false;
}

Card_dx_zjq_haoranzhengqi* Card_dx_zjq_haoranzhengqi::Clone() const {
    return new Card_dx_zjq_haoranzhengqi(*this);
}

Card_dx_zjq_haoranzhengqi::Card_dx_zjq_haoranzhengqi(const Card_dx_zjq_haoranzhengqi& other) : BaseCard(other) {}

int Card_dx_zjq_haoranzhengqi::Effect(Status* my_status, Status* enemy_status) {
    my_status->ling_qi->add(1);
    int defence_gain = 0;
    int pi_xie_gain = 0;
    switch (level) {
        case 1:
            defence_gain = 4;
            pi_xie_gain = 2;
            break;
        case 2:
            defence_gain = 8;
            pi_xie_gain = 3;
            break;
        case 3:
            defence_gain = 12;
            pi_xie_gain = 4;
            break;
    }
    my_status->defense->add(defence_gain);
    my_status->buffs[BUFF_BI_XIE]->add(pi_xie_gain);
    return 0;
}

BaseCard* Card_dx_zjq_haoranzhengqi::create(int level, int position) {
    return new Card_dx_zjq_haoranzhengqi(level, position);
}



const std::string Card_dx_zjq_qichendantian::name = "气沉丹田";
bool Card_dx_zjq_qichendantian::registered = BaseCard::registerCard(Card_dx_zjq_qichendantian::name, Card_dx_zjq_qichendantian::create);
/*
灵气+2，生命+2/6/10
*/
Card_dx_zjq_qichendantian::Card_dx_zjq_qichendantian(int level, int position) : BaseCard(level, position) {
    card_name = "气沉丹田";
    is_attacking = false;
}

Card_dx_zjq_qichendantian* Card_dx_zjq_qichendantian::Clone() const {
    return new Card_dx_zjq_qichendantian(*this);
}

Card_dx_zjq_qichendantian::Card_dx_zjq_qichendantian(const Card_dx_zjq_qichendantian& other) : BaseCard(other) {}

int Card_dx_zjq_qichendantian::Effect(Status* my_status, Status* enemy_status) {
    my_status->ling_qi->add(2);
    int health_gain = 0;
    switch (level) {
        case 1:
            health_gain = 2;
            break;
        case 2:
            health_gain = 6;
            break;
        case 3:
            health_gain = 10;
            break;
    }
    my_status->health->add(health_gain);
    return 0;
}

BaseCard* Card_dx_zjq_qichendantian::create(int level, int position) {
    return new Card_dx_zjq_qichendantian(level, position);
}



const std::string Card_dx_zjq_shidalichen::name = "势大力沉";
bool Card_dx_zjq_shidalichen::registered = BaseCard::registerCard(Card_dx_zjq_shidalichen::name, Card_dx_zjq_shidalichen::create);
/*
耗2生命，9/12/15攻，耗1灵气：此牌获得碎防并多4/5/6攻
*/
Card_dx_zjq_shidalichen::Card_dx_zjq_shidalichen(int level, int position) : BaseCard(level, position) {
    card_name = "势大力沉";
    is_attacking = true;
    switch (level) {
        case 1:
            attack = 9;
            break;
        case 2:
            attack = 12;
            break;
        case 3:
            attack = 15;
            break;
    }
    is_health_cost = true;
    health_cost = 2;
}

Card_dx_zjq_shidalichen* Card_dx_zjq_shidalichen::Clone() const {
    return new Card_dx_zjq_shidalichen(*this);
}

Card_dx_zjq_shidalichen::Card_dx_zjq_shidalichen(const Card_dx_zjq_shidalichen& other) : BaseCard(other) {}

int Card_dx_zjq_shidalichen::Effect(Status* my_status, Status* enemy_status) {
    int temp_attack = 0;
    switch (level) {
        case 1:
            temp_attack = 4;
            break;
        case 2:
            temp_attack = 5;
            break;
        case 3:
            temp_attack = 6;
            break;
    }
    bool exeflag = false;
    if (LingQiCostMax(my_status, 1)) {
        exeflag = true;
        this->card_sp_attr[CARD_SP_ATTR_SUI_FANG] += 1;
        this->attack += temp_attack;
    }
    Attack(my_status, enemy_status, attack, card_sp_attr);
    if (exeflag) {
        this->card_sp_attr[CARD_SP_ATTR_SUI_FANG] -= 1;
        this->attack -= temp_attack;
    }
    return 0;
}

BaseCard* Card_dx_zjq_shidalichen::create(int level, int position) {
    return new Card_dx_zjq_shidalichen(level, position);
}



const std::string Card_dx_zjq_kuiranbudong::name = "岿然不动";
bool Card_dx_zjq_kuiranbudong::registered = BaseCard::registerCard(Card_dx_zjq_kuiranbudong::name, Card_dx_zjq_kuiranbudong::create);
/*
防+4/5/6，气势+2/3/4，耗1灵气：生命+5
*/
Card_dx_zjq_kuiranbudong::Card_dx_zjq_kuiranbudong(int level, int position) : BaseCard(level, position) {
    card_name = "岿然不动";
    is_attacking = false;
}

Card_dx_zjq_kuiranbudong* Card_dx_zjq_kuiranbudong::Clone() const {
    return new Card_dx_zjq_kuiranbudong(*this);
}

Card_dx_zjq_kuiranbudong::Card_dx_zjq_kuiranbudong(const Card_dx_zjq_kuiranbudong& other) : BaseCard(other) {}

int Card_dx_zjq_kuiranbudong::Effect(Status* my_status, Status* enemy_status) {
    int defence = 0;
    int qi_shi_gain = 0;
    switch (level) {
        case 1:
            defence = 4;
            qi_shi_gain = 2;
            break;
        case 2:
            defence = 5;
            qi_shi_gain = 3;
            break;
        case 3:
            defence = 6;
            qi_shi_gain = 4;
            break;
    }
    my_status->defense->add(defence);
    my_status->buffs[BUFF_QI_SHI]->add(qi_shi_gain);
    if (LingQiCostMax(my_status, 1)) {
        my_status->health->add(5);
    }
    return 0;
}

BaseCard* Card_dx_zjq_kuiranbudong::create(int level, int position) {
    return new Card_dx_zjq_kuiranbudong(level, position);
}



const std::string Card_dx_zjq_yeguixiao::name = "夜鬼啸";
bool Card_dx_zjq_yeguixiao::registered = BaseCard::registerCard(Card_dx_zjq_yeguixiao::name, Card_dx_zjq_yeguixiao::create);
/*
耗1灵气，14/18/22攻，无视防御，自身加3层虚弱
*/
Card_dx_zjq_yeguixiao::Card_dx_zjq_yeguixiao(int level, int position) : BaseCard(level, position) {
    card_name = "夜鬼啸";
    ling_qi_cost = 1;
    is_attacking = true;
    switch (level) {
        case 1:
            attack = 14;
            break;
        case 2:
            attack = 18;
            break;
        case 3:
            attack = 22;
            break;
    }
    card_sp_attr[CARD_SP_ATTR_WU_SHI_FANG_YU] = true;
}

Card_dx_zjq_yeguixiao* Card_dx_zjq_yeguixiao::Clone() const {
    return new Card_dx_zjq_yeguixiao(*this);
}

Card_dx_zjq_yeguixiao::Card_dx_zjq_yeguixiao(const Card_dx_zjq_yeguixiao& other) : BaseCard(other) {}

int Card_dx_zjq_yeguixiao::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
    my_status->debuffs[DEBUFF_XU_RUO]->add(3);
    return 0;
}

BaseCard* Card_dx_zjq_yeguixiao::create(int level, int position) {
    return new Card_dx_zjq_yeguixiao(level, position);
}



const std::string Card_dx_zjq_fengmingzhua::name = "风冥爪";
bool Card_dx_zjq_fengmingzhua::registered = BaseCard::registerCard(Card_dx_zjq_fengmingzhua::name, Card_dx_zjq_fengmingzhua::create);
/*
4/6/8攻×2，灵气+2，自身加3层破绽
*/
Card_dx_zjq_fengmingzhua::Card_dx_zjq_fengmingzhua(int level, int position) : BaseCard(level, position) {
    card_name = "风冥爪";
    is_attacking = true;
    switch (level) {
        case 1:
            attack = 4;
            break;
        case 2:
            attack = 6;
            break;
        case 3:
            attack = 8;
            break;
    }
}

Card_dx_zjq_fengmingzhua* Card_dx_zjq_fengmingzhua::Clone() const {
    return new Card_dx_zjq_fengmingzhua(*this);
}

Card_dx_zjq_fengmingzhua::Card_dx_zjq_fengmingzhua(const Card_dx_zjq_fengmingzhua& other) : BaseCard(other) {}

int Card_dx_zjq_fengmingzhua::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
    Attack(my_status, enemy_status, attack, card_sp_attr);
    my_status->ling_qi->add(2);
    my_status->debuffs[DEBUFF_PO_ZHAN]->add(3);
    return 0;
}

BaseCard* Card_dx_zjq_fengmingzhua::create(int level, int position) {
    return new Card_dx_zjq_fengmingzhua(level, position);
}



const std::string Card_dx_zjq_tanmazhang::name = "探马掌";
bool Card_dx_zjq_tanmazhang::registered = BaseCard::registerCard(Card_dx_zjq_tanmazhang::name, Card_dx_zjq_tanmazhang::create);
/*
7/9/11攻，每有2体魄加1防（上限8/11/14）
*/
Card_dx_zjq_tanmazhang::Card_dx_zjq_tanmazhang(int level, int position) : BaseCard(level, position) {
    card_name = "探马掌";
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
}

Card_dx_zjq_tanmazhang* Card_dx_zjq_tanmazhang::Clone() const {
    return new Card_dx_zjq_tanmazhang(*this);
}

Card_dx_zjq_tanmazhang::Card_dx_zjq_tanmazhang(const Card_dx_zjq_tanmazhang& other) : BaseCard(other) {}

int Card_dx_zjq_tanmazhang::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
    int temp_max = 0;
    switch (level) {
        case 1:
            temp_max = 8;
            break;
        case 2:
            temp_max = 11;
            break;
        case 3:
            temp_max = 14;
            break;
    }
    int defense = my_status->ti_po->getValue() / 2;
    defense = defense > temp_max ? temp_max : defense;
    my_status->defense->add(defense);
    return 0;
}

BaseCard* Card_dx_zjq_tanmazhang::create(int level, int position) {
    return new Card_dx_zjq_tanmazhang(level, position);
}



const std::string Card_dx_zjq_duanjin::name = "锻筋";
bool Card_dx_zjq_duanjin::registered = BaseCard::registerCard(Card_dx_zjq_duanjin::name, Card_dx_zjq_duanjin::create);
/*
5/7/9攻，体魄+2，体魄≥15：防+4/6/8
*/
Card_dx_zjq_duanjin::Card_dx_zjq_duanjin(int level, int position) : BaseCard(level, position) {
    card_name = "锻筋";
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
    card_tag[TI_PO_CARD] = true;
}

Card_dx_zjq_duanjin* Card_dx_zjq_duanjin::Clone() const {
    return new Card_dx_zjq_duanjin(*this);
}

Card_dx_zjq_duanjin::Card_dx_zjq_duanjin(const Card_dx_zjq_duanjin& other) : BaseCard(other) {}

int Card_dx_zjq_duanjin::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
    my_status->ti_po->add(2);
    if (my_status->ti_po->getValue() >= 15) {
        int defense = 0;
        switch (level) {
            case 1:
                defense = 4;
                break;
            case 2:
                defense = 6;
                break;
            case 3:
                defense = 8;
                break;
        }
        my_status->defense->add(defense);
    }
    return 0;
}

BaseCard* Card_dx_zjq_duanjin::create(int level, int position) {
    return new Card_dx_zjq_duanjin(level, position);
}



const std::string Card_dx_zjq_bengquan_han::name = "崩拳·撼";
bool Card_dx_zjq_bengquan_han::registered = BaseCard::registerCard(Card_dx_zjq_bengquan_han::name, Card_dx_zjq_bengquan_han::create);
/*
耗4生命，10/11/12攻，使用下一张崩拳时加2/3/4气势
*/
Card_dx_zjq_bengquan_han::Card_dx_zjq_bengquan_han(int level, int position) : BaseCard(level, position) {
    card_name = "崩拳·撼";
    is_attacking = true;
    switch (level) {
        case 1:
            attack = 10;
            break;
        case 2:
            attack = 11;
            break;
        case 3:
            attack = 12;
            break;
    }
    is_health_cost = true;
    health_cost = 4;
    card_tag[BENG_QUAN_CARD] = true;
}

Card_dx_zjq_bengquan_han* Card_dx_zjq_bengquan_han::Clone() const {
    return new Card_dx_zjq_bengquan_han(*this);
}

Card_dx_zjq_bengquan_han::Card_dx_zjq_bengquan_han(const Card_dx_zjq_bengquan_han& other) : BaseCard(other) {}

int Card_dx_zjq_bengquan_han::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
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
    my_status->task_quene_before_effect->addTask(
        [my_status, qi_shi_gain](BaseCard* card){
            my_status->buffs[BUFF_QI_SHI]->add(qi_shi_gain);
        },
        [](BaseCard* card){ return card->card_tag[BENG_QUAN_CARD] ? true : false; },
        [](BaseCard* card){ return true; },
        REMARK_BENG_QUAN
    );
    return 0;
}

BaseCard* Card_dx_zjq_bengquan_han::create(int level, int position) {
    return new Card_dx_zjq_bengquan_han(level, position);
}



const std::string Card_dx_zjq_bengquan_can::name = "崩拳·缠";
bool Card_dx_zjq_bengquan_can::registered = BaseCard::registerCard(Card_dx_zjq_bengquan_can::name, Card_dx_zjq_bengquan_can::create);

/*
耗4生命，10/11/12攻，使用下一张崩拳时施加1/2/3层外伤
*/
Card_dx_zjq_bengquan_can::Card_dx_zjq_bengquan_can(int level, int position) : BaseCard(level, position) {
    card_name = "崩拳·缠";
    is_attacking = true;
    switch (level) {
        case 1:
            attack = 10;
            break;
        case 2:
            attack = 11;
            break;
        case 3:
            attack = 12;
            break;
    }
    is_health_cost = true;
    health_cost = 4;
    card_tag[BENG_QUAN_CARD] = true;
}

Card_dx_zjq_bengquan_can::Card_dx_zjq_bengquan_can(const Card_dx_zjq_bengquan_can& other) : BaseCard(other) {}

Card_dx_zjq_bengquan_can* Card_dx_zjq_bengquan_can::Clone() const {
    return new Card_dx_zjq_bengquan_can(*this);
}

int Card_dx_zjq_bengquan_can::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
    int temp_status = 0;
    switch (level) {
        case 1:
            temp_status = 1;
            break;
        case 2:
            temp_status = 2;
            break;
        case 3:
            temp_status = 3;
            break;
    }
    enemy_status->task_quene_before_effect->addTask(
        [enemy_status, temp_status](BaseCard* card){
            enemy_status->debuffs[DEBUFF_WAI_SHANG]->add(temp_status);
        },
        [](BaseCard* card){ return card->card_tag[BENG_QUAN_CARD] ? true : false; },
        [](BaseCard* card){ return true; },
        REMARK_BENG_QUAN
    );
    return 0;
}

BaseCard* Card_dx_zjq_bengquan_can::create(int level, int position) {
    return new Card_dx_zjq_bengquan_can(level, position);
}



const std::string Card_dx_zjq_bengquan_tu::name = "崩拳·突";
bool Card_dx_zjq_bengquan_tu::registered = BaseCard::registerCard(Card_dx_zjq_bengquan_tu::name, Card_dx_zjq_bengquan_tu::create);

/*
耗4生命，10/14/18攻，碎防（下一张崩拳也附加此效果）
*/
Card_dx_zjq_bengquan_tu::Card_dx_zjq_bengquan_tu(int level, int position) : BaseCard(level, position) {
    card_name = "崩拳·突";
    is_attacking = true;
    switch (level) {
        case 1:
            attack = 10;
            break;
        case 2:
            attack = 14;
            break;
        case 3:
            attack = 18;
            break;
    }
    is_health_cost = true;
    health_cost = 4;
    card_tag[BENG_QUAN_CARD] = true;
    card_sp_attr[CARD_SP_ATTR_SUI_FANG] = true;
}

Card_dx_zjq_bengquan_tu::Card_dx_zjq_bengquan_tu(const Card_dx_zjq_bengquan_tu& other) : BaseCard(other) {}

Card_dx_zjq_bengquan_tu* Card_dx_zjq_bengquan_tu::Clone() const {
    return new Card_dx_zjq_bengquan_tu(*this);
}

int Card_dx_zjq_bengquan_tu::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
    my_status->task_quene_before_effect->addTask(
        [my_status](BaseCard* card){
            card->card_sp_attr[CARD_SP_ATTR_SUI_FANG] += 1;
            my_status->task_quene_after_effect->addTask(
                [my_status](BaseCard* card){
                    card->card_sp_attr[CARD_SP_ATTR_SUI_FANG] -= 1;
                },
                [](BaseCard* card){ return true; },
                [](BaseCard* card){ return true; }
            );
        },
        [](BaseCard* card){ return card->card_tag[BENG_QUAN_CARD] && card-> is_attacking ? true : false; },
        [](BaseCard* card){ return true; },
        REMARK_BENG_QUAN
    );
    return 0;
}

BaseCard* Card_dx_zjq_bengquan_tu::create(int level, int position) {
    return new Card_dx_zjq_bengquan_tu(level, position);
}
