#include "account.h"
#include "status.h"
#include "head.h"

// 注意回合过多时将强制结束战斗

/*
效果造成的生命失去, 能结算护体, 如寒冰咒
*/
int EffectHealthLoss(Status* losser, int loss_value){
    // 结算失去血量
    if (loss_value > 0) {
        // 有护体则免伤, 并减少一层护体
        if (losser->buffs[BUFF_HU_TI]->getValue()) {
            loss_value = 0;
            losser->buffs[BUFF_HU_TI]->sub(1);
            std::cout << ", 护体生效";
        }
        if (loss_value > 0) {
            losser->health->sub(loss_value);
        }
    }
    return loss_value;
}

/*
无来源穿防伤害的结算
如内伤
*/
int NonSourseDamage(Status* defender, int damage_value){
    // 结算伤害
    int damage = damage_value;
    // 有护体则免伤, 并减少一层护体
    if (defender->buffs[BUFF_HU_TI]->getValue()) {
        damage = 0;
        defender->buffs[BUFF_HU_TI]->sub(1);
        std::cout << ", " << defender->style << "护体生效" << DEFAULT_STYLE;
    }
    if (damage > 0) {
        // 无视防
        defender->health->sub(damage);
        std::cout << ", " << defender->style << "受到{" << damage << "}点伤害" << DEFAULT_STYLE;
    }
    return damage;
}

// 伤害结算
int Damage(Status* attacker, Status* defender, int damage_value, int card_sp_attr[], bool is_attacking){

    // 结算伤害
    int damage = damage_value; // 用于计算伤害
    int defense_loss = 0; // 对方损失的防
    bool is_hurting = false;
    // 如果有无视防御的特殊属性, 则结算无视防御
    if (card_sp_attr[CARD_SP_ATTR_WU_SHI_FANG_YU] || attacker->buffs[BUFF_GONG_JI_WU_SHI_FANG_YU]->getValue() > 0) {
        // do nothing
    }
    // 如果有碎防的特殊属性, 则每一点伤害能抵消一点防
    else if (card_sp_attr[CARD_SP_ATTR_SUI_FANG]) {
        if (2 * damage > defender->defense->getValue()) {
            damage -= defender->defense->getValue() / 2;
            defense_loss = defender->defense->getValue();
        }
        else {
            defense_loss = 2 * damage;
            damage = 0;
        }
    }
    else {
        // 无特殊防御变更状态的正常情况
        // 如果对方有防, 结算防, damage和defense同时减少, 令其中一方为0
        if (defender->defense->getValue() > 0) {
            if (damage > defender->defense->getValue()) {
                damage -= defender->defense->getValue();
                defense_loss = defender->defense->getValue();
            }
            else {
                defense_loss = damage;
                damage = 0;
            }
        }
    }
    
    if (defense_loss > 0) {
        std::cout << ", 令对方";
        defender->defense->sub(defense_loss);
    }

    if (damage > 0) {
        // 破防, 能造成伤害
        // 伤害能使对方扣减生命值时, 结算护体, 结算护体后若仍然有伤害, 则结算锋锐
        
        // 有护体则免伤, 并减少一层护体
        if (defender->buffs[BUFF_HU_TI]->getValue() > 0) {
            damage = 0;
            defender->buffs[BUFF_HU_TI]->sub(1);
            std::cout << ", " << defender->style << "护体生效" << DEFAULT_STYLE;
        }
        // 锋锐结算
        if (damage > 0 && is_attacking && attacker->buffs[BUFF_FENG_RUI]->getValue() > 0) {
            damage += int(float(attacker->buffs[BUFF_FENG_RUI]->getValue()) * attacker->attack_damage_percent);
        }
        if (damage > 0) {
            std::cout << ", " << attacker->style << "对" << defender->style << "敌方" << attacker->style << "造成{" << damage << "}点伤害" << DEFAULT_STYLE;
            defender->health->sub(damage);
            is_hurting = true;
        }
    }

    attacker->a_damage_change(is_attacking, is_hurting);
    return damage;
}

// 伤害结算的重载实现, 给伤害函数传入均为0的card_sp_attr数组, 长度为CARD_SP_ATTR_END_INDEX
// 用于非牌追加的伤害结算
int Damage(Status* attacker, Status* defender, int damage_value){
    int card_sp_attr[CARD_SP_ATTR_END_INDEX] = {0};
    return Damage(attacker, defender, damage_value, card_sp_attr);
}

// 攻击结算, 附带牌的特殊效果
int Attack(Status* attacker, Status* defender, int attack_value, int card_sp_attr[]){
    // 特殊属性加成的多攻
    if (card_sp_attr[CARD_SP_ATTR_DUO_GONG]) {
        attack_value += card_sp_attr[CARD_SP_ATTR_DUO_GONG];
    }
    std::cout << ", " << attacker->style << "攻{" << attack_value << "}" << DEFAULT_STYLE;
    // *计算攻击力的结算加减*
    int damage_value = attack_value;
    damage_value += attacker->buffs[BUFF_JIA_GONG]->getValue() 
    + attacker->buffs[BUFF_JIAN_YI]->getValue() - attacker->debuffs[DEBUFF_JIAN_GONG]->getValue()
    + defender->debuffs[DEBUFF_WAI_SHANG]->getValue();
    // 判断星位
    if (attacker->is_xing_wei[attacker->using_card_position]) {
        damage_value += attacker->buffs[BUFF_XING_LI]->getValue();
    }
    // 最小为1
    if (damage_value < 1) {
        damage_value = 1;
    }
    // *计算攻击力加成百分比*
    float damage_percent = 1.0;
    // 气势结算
    // 是否有双倍气势的特殊属性
    if (card_sp_attr[CARD_SP_ATTR_SHUANG_BEI_QI_SHI]) {
        damage_percent += float(attacker->buffs[BUFF_QI_SHI]->getValue()) * 0.1 * 2;
    }
    else {
        damage_percent += float(attacker->buffs[BUFF_QI_SHI]->getValue()) * 0.1;
    }
    // 破绽和虚弱的结算
    if (defender->debuffs[DEBUFF_PO_ZHAN]->getValue()) {
        damage_percent += 0.4;
    }
    if (attacker->debuffs[DEBUFF_XU_RUO]->getValue()) {
        damage_percent -= 0.4;
    }
    damage_value = int(float(damage_value) * damage_percent);
    // 最小为1
    if (damage_value < 1) {
        damage_value = 1;
    }
    // *额外结算*
    if (defender->buffs[BUFF_QIAN_DUN]->getValue()) {
        // 潜遁
        damage_value = int(float(damage_value) * 0.6);
        damage_percent = damage_percent * 0.6;
    }
    // 临时记录伤害百分比, 用于结算锋锐
    attacker->attack_damage_percent = damage_percent;
    if (defender->buffs[BUFF_TIE_GU]->getValue()) {
        // 铁骨
        damage_value = damage_value - 5;
    }
    // 最小为1
    if (damage_value < 1) {
        damage_value = 1;
    }

    int damage = Damage(attacker, defender, damage_value, card_sp_attr, true);
    attacker->attack_change();
    return damage;
}

// 攻击结算的重载实现, 给攻击函数传入均为0的card_sp_attr数组, 长度为CARD_SP_ATTR_END_INDEX
// 用于非牌追加的攻击结算
int Attack(Status* attacker, Status* defender, int attack_value){
    int card_sp_attr[CARD_SP_ATTR_END_INDEX] = {0};
    return Attack(attacker, defender, attack_value, card_sp_attr);
}

// 结算吸血
int HealthSuck(Status* gainer, Status* losser, int suck_value){
    int suck = suck_value;
    // if (suck > loser->health) {
    //     suck = loser->health;
    // }
    if (suck > losser->health->getValue()) {
        suck = losser->health->getValue();
    }
    std::cout << ", " << gainer->style << "吸取" << suck << "点血" << DEFAULT_STYLE << ", " << losser->style << "敌方" << DEFAULT_STYLE;
    losser->health->sub(suck);
    gainer->health->add(suck);
    return 0;
}

// 消耗所有灵气, 并返回消耗的灵气值
int LingQiCostAll(Status* coster){
    int cost_value = coster->ling_qi->getValue();
    coster->ling_qi->sub(cost_value);
    return cost_value;
}

// 消耗最多n点灵气, 并返回消耗的灵气值（耗X灵气）
int LingQiCostMax(Status* coster, int max_cost_value){
    int cost_value = coster->ling_qi->getValue();
    if (cost_value > max_cost_value) {
        cost_value = max_cost_value;
    }
    coster->ling_qi->sub(cost_value);
    return cost_value;
}

// 再次行动获取
int ReexecuteGain(Status* gainer){
    gainer->flag.flag[FLAG_ZAI_CI_XING_DONG] = true;
    std::cout << ", " << gainer->style << "获得再次行动效果" << DEFAULT_STYLE;
    return 0;
}

// 失去再次行动
int ReexecuteLoss(Status* losser){
    losser->flag.flag[FLAG_ZAI_CI_XING_DONG] = false;
    return 0;
}

// 已再次行动获取
int ReexecuteAlreadyGain(Status* gainer){
    gainer->flag.flag[FLAG_YI_ZAI_CI_XING_DONG] += true;
    return 0;
}

// 生成指定范围内的整型随机数
int RandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// 计算debuff总层数
int DebuffTotal(Status* status){
    int total = 0;
    for (int i = 0; i < DEBUFF_END_INDEX; i++) {
        total += status->debuffs[i]->getValue();
    }
    return total;
}

// 将debuff_type按照层数从大到小排序, 返回排序后的debuff_type数组
// debuff_type数组长度为DEBUFF_END_INDEX - DEBUFF_START_INDEX
int* DebuffSort(Status* sorter){
    int* debuff_type = new int[DEBUFF_END_INDEX];
    for (int i = 0; i < DEBUFF_END_INDEX; i++) {
        debuff_type[i] = i;
    }
    // 快速排序
    int left = 0;
    int right = DEBUFF_END_INDEX - 1;
    int temp;
    while (left < right) {
        while (left < right && sorter->debuffs[debuff_type[right]]->getValue() <= sorter->debuffs[debuff_type[left]]->getValue()) {
            right--;
        }
        if (left < right) {
            temp = debuff_type[left];
            debuff_type[left] = debuff_type[right];
            debuff_type[right] = temp;
            left++;
        }
        while (left < right && sorter->debuffs[debuff_type[right]]->getValue() >= sorter->debuffs[debuff_type[left]]->getValue()) {
            left++;
        }
        if (left < right) {
            temp = debuff_type[left];
            debuff_type[left] = debuff_type[right];
            debuff_type[right] = temp;
            right--;
        }
    }
    return debuff_type;
}



// 随机减少总计n层debuff, 每种debuff至少减少到0, n为正数
// 先获取debuff_type按照层数从大到小排序, 并得到大于0的debuff种类数量
// 随机减少大于0的debuff
// 当is_transfer_to_enemy为true时, 将减少的debuff转移给敌方, enemy为敌方状态指针
int DebuffRandomReduce(Status* reducer, int reduce_value, bool is_transfer_to_enemy, Status* enemy){
    int* debuff_type = DebuffSort(reducer);
    int debuff_count = 0;
    for (int i = 0; i < DEBUFF_END_INDEX; i++) {
        if (reducer->debuffs[debuff_type[i]]->getValue() > 0) {
            debuff_count++;
        }
        else {
            break;
        }
    }
    if (debuff_count == 0) {
        delete[] debuff_type;
        return 0;
    }
    int reduce_count = 0;
    int random_index;
    while (reduce_count < reduce_value) {
        random_index = RandomNumber(0, debuff_count - 1);
        if (reducer->debuffs[debuff_type[random_index]]->getValue() > 0) {
            reducer->debuffs[debuff_type[random_index]]->sub(1);
            if (is_transfer_to_enemy) {
                enemy->debuffs[debuff_type[random_index]]->add(1);
                std::cout << ", " << reducer->style << "转移" << debuff_type[random_index] << "1层" << DEFAULT_STYLE;
            }
            std::cout << ",  " << reducer->style << "减少" << debuff_type[random_index] << "1层" << DEFAULT_STYLE;
            reduce_count++;
            // 如果减少到0, 则减少debuff_count, 并将该debuff_type与最后一个debuff_type交换
            if (reducer->debuffs[debuff_type[random_index]]->getValue() == 0) {
                debuff_count--;
                int temp = debuff_type[random_index];
                debuff_type[random_index] = debuff_type[debuff_count];
                debuff_type[debuff_count] = temp;
            }
        }
    }
    delete[] debuff_type;
    return 0;
}

// 随机增加n层debuff
int DebuffRandomAdd(Status* adder, int add_value){
    int add_count = 0;
    int random_index;
    while (add_count < add_value) {
        random_index = RandomNumber(0, DEBUFF_END_INDEX - 1);
        adder->debuffs[random_index]->add(1);
        std::cout << ", " << adder->style << "增加" << random_index << "1层" << DEFAULT_STYLE;
        add_count++;
    }
    return 0;
}