#include "dx_yyq.h"

// 定义文件内所有牌的变量
#define FILE_CARDS_SOVJ "锻玄宗"
#define FILE_CARDS_REALM REALM_YYQ

const std::string Card_dx_yyq_xuanshouduohun::name = "玄手夺魂";
bool Card_dx_yyq_xuanshouduohun::registered = BaseCard::registerCard(FILE_CARDS_SOVJ, FILE_CARDS_REALM, Card_dx_yyq_xuanshouduohun::name, Card_dx_yyq_xuanshouduohun::create);
/*
耗1灵气，吸取对方7/10/13生命；自身每有1层负面状态就多吸取1点（最多加7/10/13）
*/
Card_dx_yyq_xuanshouduohun::Card_dx_yyq_xuanshouduohun(int level, int position) : BaseCard(level, position) {
    sovj = FILE_CARDS_SOVJ;
    realm = FILE_CARDS_REALM;
    card_name = "玄手夺魂";
    ling_qi_cost = 1;
}

Card_dx_yyq_xuanshouduohun* Card_dx_yyq_xuanshouduohun::Clone() const {
    return new Card_dx_yyq_xuanshouduohun(*this);
}

Card_dx_yyq_xuanshouduohun::Card_dx_yyq_xuanshouduohun(const Card_dx_yyq_xuanshouduohun& other) : BaseCard(other) {}

int Card_dx_yyq_xuanshouduohun::Effect(Status* my_status, Status* enemy_status) {
    int temp_suck = 0;
    int temp_ex_suck_max = 0;
    switch (level) {
        case 1:
            temp_suck = 7;
            temp_ex_suck_max = 7;
            break;
        case 2:
            temp_suck = 10;
            temp_ex_suck_max = 10;
            break;
        case 3:
            temp_suck = 13;
            temp_ex_suck_max = 13;
            break;
    }
    int temp_ex_suck = DebuffTotal(my_status);
    temp_ex_suck = temp_ex_suck > temp_ex_suck_max ? temp_ex_suck_max : temp_ex_suck;
    temp_suck += temp_ex_suck;
    HealthSuck(my_status, enemy_status, temp_suck);
    return 0;
}

BaseCard* Card_dx_yyq_xuanshouduohun::create(int level, int position) {
    return new Card_dx_yyq_xuanshouduohun(level, position);
}



const std::string Card_dx_yyq_pangbozhishi::name = "磅礴之势";
bool Card_dx_yyq_pangbozhishi::registered = BaseCard::registerCard(FILE_CARDS_SOVJ, FILE_CARDS_REALM, Card_dx_yyq_pangbozhishi::name, Card_dx_yyq_pangbozhishi::create);
/*
耗尽气势，每点加4防并造成3/4/5伤害，身法+5/6/7
*/
Card_dx_yyq_pangbozhishi::Card_dx_yyq_pangbozhishi(int level, int position) : BaseCard(level, position) {
    sovj = FILE_CARDS_SOVJ;
    realm = FILE_CARDS_REALM;
    card_name = "磅礴之势";
    is_attacking = false;
}

Card_dx_yyq_pangbozhishi* Card_dx_yyq_pangbozhishi::Clone() const {
    return new Card_dx_yyq_pangbozhishi(*this);
}

Card_dx_yyq_pangbozhishi::Card_dx_yyq_pangbozhishi(const Card_dx_yyq_pangbozhishi& other) : BaseCard(other) {}

int Card_dx_yyq_pangbozhishi::Effect(Status* my_status, Status* enemy_status) {
    int shen_fa_gain = 0;
    switch (level) {
        case 1:
            shen_fa_gain = 5;
            break;
        case 2:
            shen_fa_gain = 6;
            break;
        case 3:
            shen_fa_gain = 7;
            break;
    }
    my_status->buffs[BUFF_SHEN_FA]->add(shen_fa_gain);
    int temp_qi_shi = my_status->buffs[BUFF_QI_SHI]->getValue();
    my_status->buffs[BUFF_QI_SHI]->sub(temp_qi_shi);
    int defence = temp_qi_shi * 4;
    int damage = 0;
    switch (level) {
        case 1:
            damage = temp_qi_shi * 3;
            break;
        case 2:
            damage = temp_qi_shi * 4;
            break;
        case 3:
            damage = temp_qi_shi * 5;
            break;
    }
    my_status->defense->add(defence);
    Damage(my_status, enemy_status, damage, card_sp_attr);
    return 0;
}

BaseCard* Card_dx_yyq_pangbozhishi::create(int level, int position) {
    return new Card_dx_yyq_pangbozhishi(level, position);
}



const std::string Card_dx_yyq_chongxiaopolang::name = "冲霄破浪";
bool Card_dx_yyq_chongxiaopolang::registered = BaseCard::registerCard(FILE_CARDS_SOVJ, FILE_CARDS_REALM, Card_dx_yyq_chongxiaopolang::name, Card_dx_yyq_chongxiaopolang::create);
/*
灵气+1/2/3，每有1灵气加1气势，身法+5
*/
Card_dx_yyq_chongxiaopolang::Card_dx_yyq_chongxiaopolang(int level, int position) : BaseCard(level, position) {
    sovj = FILE_CARDS_SOVJ;
    realm = FILE_CARDS_REALM;
    card_name = "冲霄破浪";
    is_attacking = false;
}

Card_dx_yyq_chongxiaopolang* Card_dx_yyq_chongxiaopolang::Clone() const {
    return new Card_dx_yyq_chongxiaopolang(*this);
}

Card_dx_yyq_chongxiaopolang::Card_dx_yyq_chongxiaopolang(const Card_dx_yyq_chongxiaopolang& other) : BaseCard(other) {}

int Card_dx_yyq_chongxiaopolang::Effect(Status* my_status, Status* enemy_status) {
    int ling_qi_gain = 0;
    switch (level) {
        case 1:
            ling_qi_gain = 1;
            break;
        case 2:
            ling_qi_gain = 2;
            break;
        case 3:
            ling_qi_gain = 3;
            break;
    }
    my_status->ling_qi->add(ling_qi_gain);
    my_status->buffs[BUFF_QI_SHI]->add(my_status->ling_qi->getValue());
    my_status->buffs[BUFF_SHEN_FA]->add(5);
    return 0;
}

BaseCard* Card_dx_yyq_chongxiaopolang::create(int level, int position) {
    return new Card_dx_yyq_chongxiaopolang(level, position);
}




const std::string Card_dx_yyq_mingyingshenfa::name = "冥影身法";
bool Card_dx_yyq_mingyingshenfa::registered = BaseCard::registerCard(FILE_CARDS_SOVJ, FILE_CARDS_REALM, Card_dx_yyq_mingyingshenfa::name, Card_dx_yyq_mingyingshenfa::create);
/*
耗1/3/5生命，自身加1/1/2层减攻，身法+10/14/18
*/
Card_dx_yyq_mingyingshenfa::Card_dx_yyq_mingyingshenfa(int level, int position) : BaseCard(level, position) {
    sovj = FILE_CARDS_SOVJ;
    realm = FILE_CARDS_REALM;
    card_name = "冥影身法";
    is_attacking = false;
    is_health_cost = true;
    switch (level) {
        case 1:
            health_cost = 1;
            break;
        case 2:
            health_cost = 3;
            break;
        case 3:
            health_cost = 5;
            break;
    }
}

Card_dx_yyq_mingyingshenfa* Card_dx_yyq_mingyingshenfa::Clone() const {
    return new Card_dx_yyq_mingyingshenfa(*this);
}

Card_dx_yyq_mingyingshenfa::Card_dx_yyq_mingyingshenfa(const Card_dx_yyq_mingyingshenfa& other) : BaseCard(other) {}

int Card_dx_yyq_mingyingshenfa::Effect(Status* my_status, Status* enemy_status) {
    int jian_gong_gain = 0;
    int shen_fa_gain = 0;
    switch (level) {
        case 1:
            jian_gong_gain = 1;
            shen_fa_gain = 10;
            break;
        case 2:
            jian_gong_gain = 1;
            shen_fa_gain = 14;
            break;
        case 3:
            jian_gong_gain = 2;
            shen_fa_gain = 18;
            break;
    }
    my_status->debuffs[DEBUFF_JIAN_GONG]->add(jian_gong_gain);
    my_status->debuffs[DEBUFF_JIAN_GONG]->add(jian_gong_gain);
    my_status->buffs[BUFF_SHEN_FA]->add(shen_fa_gain);
    return 0;
}

BaseCard* Card_dx_yyq_mingyingshenfa::create(int level, int position) {
    return new Card_dx_yyq_mingyingshenfa(level, position);
}



const std::string Card_dx_yyq_lingxuanmizongbu::name = "灵玄迷踪步";
bool Card_dx_yyq_lingxuanmizongbu::registered = BaseCard::registerCard(FILE_CARDS_SOVJ, FILE_CARDS_REALM, Card_dx_yyq_lingxuanmizongbu::name, Card_dx_yyq_lingxuanmizongbu::create);
/*
灵气+1/2/3，身法+2/3/4，持续：自身每回合首次失去生命时，加1灵气和1身法
*/
Card_dx_yyq_lingxuanmizongbu::Card_dx_yyq_lingxuanmizongbu(int level, int position) : BaseCard(level, position) {
    sovj = FILE_CARDS_SOVJ;
    realm = FILE_CARDS_REALM;
    card_name = "灵玄迷踪步";
    is_attacking = false;
    card_tag[CHI_XU_CARD] = true;
}

Card_dx_yyq_lingxuanmizongbu* Card_dx_yyq_lingxuanmizongbu::Clone() const {
    return new Card_dx_yyq_lingxuanmizongbu(*this);
}

Card_dx_yyq_lingxuanmizongbu::Card_dx_yyq_lingxuanmizongbu(const Card_dx_yyq_lingxuanmizongbu& other) : BaseCard(other) {}

int Card_dx_yyq_lingxuanmizongbu::Effect(Status* my_status, Status* enemy_status) {
    int ling_qi_gain = 0;
    int shen_fa_gain = 0;
    switch (level) {
        case 1:
            ling_qi_gain = 1;
            shen_fa_gain = 2;
            break;
        case 2:
            ling_qi_gain = 2;
            shen_fa_gain = 3;
            break;
        case 3:
            ling_qi_gain = 3;
            shen_fa_gain = 4;
            break;
    }
    my_status->ling_qi->add(ling_qi_gain);
    my_status->buffs[BUFF_SHEN_FA]->add(shen_fa_gain);
    my_status->health->sub_task_quene->addTask(
        [my_status](int& health_loss){
            my_status->ling_qi->add(1);
            my_status->buffs[BUFF_SHEN_FA]->add(1);
            my_status->SetFlag("灵玄迷踪步本回合失去过生命", true);
        },
        [my_status](int& health_loss){ return !my_status->GetFlag("灵玄迷踪步本回合失去过生命"); },
        [](int& health_loss){ return false; }
    );
    my_status->task_quene_after_round->addTask(
        [my_status](int& round){
            my_status->SetFlag("灵玄迷踪步本回合失去过生命", false);
        },
        [](int& round){ return true; },
        [](int& round){ return false; }
    );
    return 0;
}

BaseCard* Card_dx_yyq_lingxuanmizongbu::create(int level, int position) {
    return new Card_dx_yyq_lingxuanmizongbu(level, position);
}



const std::string Card_dx_yyq_hebu::name = "鹤步";
bool Card_dx_yyq_hebu::registered = BaseCard::registerCard(FILE_CARDS_SOVJ, FILE_CARDS_REALM, Card_dx_yyq_hebu::name, Card_dx_yyq_hebu::create);
/*
生命+4/5/6，每有4体魄加1身法（上限为10/13/16）
*/
Card_dx_yyq_hebu::Card_dx_yyq_hebu(int level, int position) : BaseCard(level, position) {
    sovj = FILE_CARDS_SOVJ;
    realm = FILE_CARDS_REALM;
    card_name = "鹤步";
    is_attacking = false;
}

Card_dx_yyq_hebu* Card_dx_yyq_hebu::Clone() const {
    return new Card_dx_yyq_hebu(*this);
}

Card_dx_yyq_hebu::Card_dx_yyq_hebu(const Card_dx_yyq_hebu& other) : BaseCard(other) {}

int Card_dx_yyq_hebu::Effect(Status* my_status, Status* enemy_status) {
    int health_gain = 0;
    int shen_fa_gain_max = 0;
    switch (level) {
        case 1:
            health_gain = 4;
            shen_fa_gain_max = 10;
            break;
        case 2:
            health_gain = 5;
            shen_fa_gain_max = 13;
            break;
        case 3:
            health_gain = 6;
            shen_fa_gain_max = 16;
            break;
    }
    my_status->health->add(health_gain);
    int shen_fa_gain = my_status->ti_po->getValue() / 4;
    if (shen_fa_gain > shen_fa_gain_max) {
        shen_fa_gain = shen_fa_gain_max;
    }
    my_status->buffs[BUFF_SHEN_FA]->add(shen_fa_gain);
    return 0;
}

BaseCard* Card_dx_yyq_hebu::create(int level, int position) {
    return new Card_dx_yyq_hebu(level, position);
}



const std::string Card_dx_yyq_duansui::name = "锻髓";
bool Card_dx_yyq_duansui::registered = BaseCard::registerCard(FILE_CARDS_SOVJ, FILE_CARDS_REALM, Card_dx_yyq_duansui::name, Card_dx_yyq_duansui::create);
/*
体魄+3，回复生命上限8/12/16%的生命
*/
Card_dx_yyq_duansui::Card_dx_yyq_duansui(int level, int position) : BaseCard(level, position) {
    sovj = FILE_CARDS_SOVJ;
    realm = FILE_CARDS_REALM;
    card_name = "锻髓";
    is_attacking = false;
    card_tag[TI_PO_CARD] = true;
}

Card_dx_yyq_duansui* Card_dx_yyq_duansui::Clone() const {
    return new Card_dx_yyq_duansui(*this);
}

Card_dx_yyq_duansui::Card_dx_yyq_duansui(const Card_dx_yyq_duansui& other) : BaseCard(other) {}

int Card_dx_yyq_duansui::Effect(Status* my_status, Status* enemy_status) {
    my_status->ti_po->add(3);
    float temp_percent = 0;
    switch (level) {
        case 1:
            temp_percent = 8;
            break;
        case 2:
            temp_percent = 12;
            break;
        case 3:
            temp_percent = 16;
            break;
    }
    int health_gain = int(float(my_status->health_max->getValue()) * temp_percent / 100);
    my_status->health->add(health_gain);
    return 0;
}

BaseCard* Card_dx_yyq_duansui::create(int level, int position) {
    return new Card_dx_yyq_duansui(level, position);
}



const std::string Card_dx_yyq_bengquan_cunjing::name = "崩拳·寸劲";
bool Card_dx_yyq_bengquan_cunjing::registered = BaseCard::registerCard(FILE_CARDS_SOVJ, FILE_CARDS_REALM, Card_dx_yyq_bengquan_cunjing::name, Card_dx_yyq_bengquan_cunjing::create);
/*
耗5生命，10/14/18攻，受双倍气势加成（下一张崩拳也附加此效果，不可叠加）
*/
Card_dx_yyq_bengquan_cunjing::Card_dx_yyq_bengquan_cunjing(int level, int position) : BaseCard(level, position) {
    sovj = FILE_CARDS_SOVJ;
    realm = FILE_CARDS_REALM;
    card_name = "崩拳·寸劲";
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
    health_cost = 5;
    card_tag[BENG_QUAN_CARD] = true;
    card_sp_attr[CARD_SP_ATTR_SHUANG_BEI_QI_SHI] = true;
}

Card_dx_yyq_bengquan_cunjing* Card_dx_yyq_bengquan_cunjing::Clone() const {
    return new Card_dx_yyq_bengquan_cunjing(*this);
}

Card_dx_yyq_bengquan_cunjing::Card_dx_yyq_bengquan_cunjing(const Card_dx_yyq_bengquan_cunjing& other) : BaseCard(other) {}

int Card_dx_yyq_bengquan_cunjing::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
    my_status->task_quene_before_effect->addTask(
        [my_status](BaseCard* card){
            card->card_sp_attr[CARD_SP_ATTR_SHUANG_BEI_QI_SHI] += 1;
            my_status->task_quene_after_effect->addTask(
                [my_status](BaseCard* card){
                    card->card_sp_attr[CARD_SP_ATTR_SHUANG_BEI_QI_SHI] -= 1;
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

BaseCard* Card_dx_yyq_bengquan_cunjing::create(int level, int position) {
    return new Card_dx_yyq_bengquan_cunjing(level, position);
}



const std::string Card_dx_yyq_bengquan_lianbeng::name = "崩拳·连崩";
bool Card_dx_yyq_bengquan_lianbeng::registered = BaseCard::registerCard(FILE_CARDS_SOVJ, FILE_CARDS_REALM, Card_dx_yyq_bengquan_lianbeng::name, Card_dx_yyq_bengquan_lianbeng::create);
/*
耗6生命，11/16/21攻，此牌触发的崩拳效果保留至下一张崩拳
*/
Card_dx_yyq_bengquan_lianbeng::Card_dx_yyq_bengquan_lianbeng(int level, int position) : BaseCard(level, position) {
    sovj = FILE_CARDS_SOVJ;
    realm = FILE_CARDS_REALM;
    card_name = "崩拳·连崩";
    is_attacking = true;
    switch (level) {
        case 1:
            attack = 11;
            break;
        case 2:
            attack = 16;
            break;
        case 3:
            attack = 21;
            break;
    }
    is_health_cost = true;
    health_cost = 6;
    card_tag[BENG_QUAN_CARD] = true;
    is_before_task_queue_effect = true;
}

Card_dx_yyq_bengquan_lianbeng* Card_dx_yyq_bengquan_lianbeng::Clone() const {
    return new Card_dx_yyq_bengquan_lianbeng(*this);
}

Card_dx_yyq_bengquan_lianbeng::Card_dx_yyq_bengquan_lianbeng(const Card_dx_yyq_bengquan_lianbeng& other) : BaseCard(other), recordedTasks(other.recordedTasks) {}

int Card_dx_yyq_bengquan_lianbeng::BeforeTaskQueueEffect(Status* my_status, Status* enemy_status) {
    // 记录将触发的崩拳效果
    for (auto& task : my_status->task_quene_before_effect->taskQueue) {
        if (task.remark == REMARK_BENG_QUAN) {
            this->recordedTasks.push_back(task);
        }
    }
    return 0;
}

int Card_dx_yyq_bengquan_lianbeng::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
    // 重新把任务放回队列
    for (const auto& task : this->recordedTasks) {
        my_status->task_quene_before_effect->addTask(task.function, task.executeCondition, task.removeCondition, task.remark);
    }
    this->recordedTasks.clear();
    return 0;
}

BaseCard* Card_dx_yyq_bengquan_lianbeng::create(int level, int position) {
    return new Card_dx_yyq_bengquan_lianbeng(level, position);
}



const std::string Card_dx_yyq_bengmiexinfa::name = "崩灭心法";
bool Card_dx_yyq_bengmiexinfa::registered = BaseCard::registerCard(FILE_CARDS_SOVJ, FILE_CARDS_REALM, Card_dx_yyq_bengmiexinfa::name, Card_dx_yyq_bengmiexinfa::create);
/*
气势+2/3/4，持续：每次使用耗生命的牌时加1气势
*/
Card_dx_yyq_bengmiexinfa::Card_dx_yyq_bengmiexinfa(int level, int position) : BaseCard(level, position) {
    sovj = FILE_CARDS_SOVJ;
    realm = FILE_CARDS_REALM;
    card_name = "崩灭心法";
    is_attacking = false;
    card_tag[CHI_XU_CARD] = true;
}

Card_dx_yyq_bengmiexinfa* Card_dx_yyq_bengmiexinfa::Clone() const {
    return new Card_dx_yyq_bengmiexinfa(*this);
}

Card_dx_yyq_bengmiexinfa::Card_dx_yyq_bengmiexinfa(const Card_dx_yyq_bengmiexinfa& other) : BaseCard(other) {}

int Card_dx_yyq_bengmiexinfa::Effect(Status* my_status, Status* enemy_status) {
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
    my_status->task_quene_before_effect->addTask(
        [my_status](BaseCard* card){
            my_status->buffs[BUFF_QI_SHI]->add(1);
        },
        [](BaseCard* card){
            if (card->is_health_cost) {
                return true;
            }
            else {
                return false;
            }
        },
        [](BaseCard* card){ return false; }
    );
    return 0;
}

BaseCard* Card_dx_yyq_bengmiexinfa::create(int level, int position) {
    return new Card_dx_yyq_bengmiexinfa(level, position);
}