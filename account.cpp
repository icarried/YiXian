#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "account.h"
#include "status.h"
#include "head.h"

// 注意回合过多时将强制结束战斗


// 结算失去血量
int HealthLoss(Status* losser, int loss_value){
    if (loss_value > 0) {
        losser->health -= loss_value;
        losser->health_loss_total += loss_value;
        std::cout << "失去" << loss_value << "点血，剩余" << losser->health << "/" << losser->health_max << "点血";
        losser->task_quene_after_health_loss->executeTaskQueue(loss_value);
    }
    return loss_value;
}


// 结算失去血量上限
int HealthMaxLoss(Status* losser, int loss_value){
    if (loss_value > 0) {
        losser->health_max -= loss_value;
        std::cout << "，失去" << loss_value << "点血量上限，剩余" << losser->health_max << "点血量上限";
        if (losser->health > losser->health_max) {
            std::cout << "，血量上限减少导致血量减少";
            HealthLoss(losser, losser->health - losser->health_max);
        }
    }
    return 0;
}

/*
效果造成的生命失去，能结算护体，如寒冰咒
*/
int EffectHealthLoss(Status* losser, int loss_value){
    // 结算失去血量
    if (loss_value > 0) {
        // 有护体则免伤，并减少一层护体
        if (losser->buff.buff[BUFF_HU_TI]) {
            loss_value = 0;
            losser->buff.buff[BUFF_HU_TI]--;
            std::cout << "，护体生效";
        }
        if (loss_value > 0) {
            HealthLoss(losser, loss_value);
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
    // 有护体则免伤，并减少一层护体
    if (defender->buff.buff[BUFF_HU_TI]) {
        damage = 0;
        defender->buff.buff[BUFF_HU_TI]--;
        std::cout << "，护体生效";
    }
    if (damage > 0) {
        // 无视防
        HealthLoss(defender, damage);
        std::cout << "，受到{" << damage << "}点伤害";
    }
    return damage;
}


// 结算失去防御
int DefenseLoss(Status* losser, int loss_value){
    losser->defense -= loss_value;
    std::cout << "防减少" << loss_value << "点，剩余" << losser->defense << "点防";
    return 0;
}

// 伤害结算
int Damage(Status* attacker, Status* defender, int damage_value, int card_sp_attr[], bool is_attacking = false){

    // 结算伤害
    int damage = damage_value; // 用于计算伤害
    int defense_loss = 0; // 对方损失的防
    bool is_hurting = false;
    // 如果有无视防御的特殊属性，则结算无视防御
    if (card_sp_attr[CARD_SP_ATTR_WU_SHI_FANG_YU] || attacker->buff.buff[BUFF_GONG_JI_WU_SHI_FANG_YU]) {
        // do nothing
    }
    // 如果有碎防的特殊属性，则每一点伤害能抵消一点防
    else if (card_sp_attr[CARD_SP_ATTR_SUI_FANG]) {
        if (2 * damage > defender->defense) {
            damage -= defender->defense / 2;
            defense_loss = defender->defense;
        }
        else {
            defense_loss = 2 * damage;
            damage = 0;
        }
    }
    else {
        // 无特殊防御变更状态的正常情况
        // 如果对方有防，结算防，damage和defense同时减少，令其中一方为0
        if (defender->defense > 0) {
            if (damage > defender->defense) {
                damage -= defender->defense;
                defense_loss = defender->defense;
            }
            else {
                defense_loss = damage;
                damage = 0;
            }
        }
    }
    
    if (defense_loss > 0) {
        std::cout << "，令对方";
        DefenseLoss(defender, defense_loss);
    }

    if (damage > 0) {
        // 破防，能造成伤害
        // 伤害能使对方扣减生命值时，结算护体，结算护体后若仍然有伤害，则结算锋锐
        
        // 有护体则免伤，并减少一层护体
        if (defender->buff.buff[BUFF_HU_TI]) {
            damage = 0;
            defender->buff.buff[BUFF_HU_TI]--;
            std::cout << "，护体生效";
        }
        // 锋锐结算
        if (damage > 0 && is_attacking && attacker->buff.buff[BUFF_FENG_RUI]) {
            damage += int(float(attacker->buff.buff[BUFF_FENG_RUI]) * attacker->attack_damage_percent);
        }
        if (damage > 0) {
            std::cout << "，对敌方造成{" << damage << "}点伤害";
            HealthLoss(defender, damage);
            is_hurting = true;
        }
    }

    attacker->buff.a_damage_change(is_attacking, is_hurting);
    return damage;
}

// 伤害结算的重载实现，给伤害函数传入均为0的card_sp_attr数组，长度为CARD_SP_ATTR_END_INDEX
// 用于非牌追加的伤害结算
int Damage(Status* attacker, Status* defender, int damage_value){
    int card_sp_attr[CARD_SP_ATTR_END_INDEX] = {0};
    return Damage(attacker, defender, damage_value, card_sp_attr);
}

// 攻击结算，附带牌的特殊效果
int Attack(Status* attacker, Status* defender, int attack_value, int card_sp_attr[]){
    // 特殊属性加成的多攻
    if (card_sp_attr[CARD_SP_ATTR_DUO_GONG]) {
        attack_value += card_sp_attr[CARD_SP_ATTR_DUO_GONG];
    }
    std::cout << "，攻{" << attack_value << "}";
    // *计算攻击力的结算加减*
    int damage_value = attack_value;
    damage_value += attacker->buff.buff[BUFF_JIA_GONG] 
    + attacker->buff.buff[BUFF_JIAN_YI] - attacker->buff.buff[DEBUFF_JIAN_GONG]
    + defender->buff.buff[DEBUFF_WAI_SHANG];
    // 判断星位
    if (attacker->is_xing_wei[attacker->using_card_position]) {
        damage_value += attacker->buff.buff[BUFF_XING_LI];
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
        damage_percent += float(attacker->buff.buff[BUFF_QI_SHI]) * 0.1 * 2;
    }
    else {
        damage_percent += float(attacker->buff.buff[BUFF_QI_SHI]) * 0.1;
    }
    // 破绽和虚弱的结算
    if (defender->buff.buff[DEBUFF_PO_ZHAN]) {
        damage_percent += 0.4;
    }
    if (attacker->buff.buff[DEBUFF_XU_RUO]) {
        damage_percent -= 0.4;
    }
    damage_value = int(float(damage_value) * damage_percent);
    // 最小为1
    if (damage_value < 1) {
        damage_value = 1;
    }
    // *额外结算*
    if (defender->buff.buff[BUFF_QIAN_DUN]) {
        // 潜遁
        damage_value = int(float(damage_value) * 0.6);
        damage_percent = damage_percent * 0.6;
    }
    // 临时记录伤害百分比，用于结算锋锐
    attacker->attack_damage_percent = damage_percent;
    if (defender->buff.buff[BUFF_TIE_GU]) {
        // 铁骨
        damage_value = damage_value - 5;
    }
    // 最小为1
    if (damage_value < 1) {
        damage_value = 1;
    }

    int damage = Damage(attacker, defender, damage_value, card_sp_attr, true);
    attacker->buff.attack_change();
    return damage;
}

// 攻击结算的重载实现，给攻击函数传入均为0的card_sp_attr数组，长度为CARD_SP_ATTR_END_INDEX
// 用于非牌追加的攻击结算
int Attack(Status* attacker, Status* defender, int attack_value){
    int card_sp_attr[CARD_SP_ATTR_END_INDEX] = {0};
    return Attack(attacker, defender, attack_value, card_sp_attr);
}

// 结算获得血量
int HealthGain(Status* gainer, int gain_value){
    gainer->health += gain_value;
    if (gainer->health > gainer->health_max) {
        gainer->health = gainer->health_max;
    }
    std::cout << "，恢复" << gain_value << "点血，剩余" << gainer->health << "/" << gainer->health_max << "点血";

    return 0;
}


// 结算吸血
int HealthSuck(Status* gainer, Status* loser, int suck_value){
    int suck = suck_value;
    if (suck > loser->health) {
        suck = loser->health;
    }
    std::cout << "，吸取" << suck << "点血，敌方";
    HealthLoss(loser, suck);
    HealthGain(gainer, suck);
    return 0;
}

// 结算获得血量上限
int HealthMaxGain(Status* gainer, int gain_value){
    gainer->health_max += gain_value;
    std::cout << "，增加" << gain_value << "点血量上限，剩余" << gainer->health_max << "点血量上限";
    return 0;
}

// 结算获得防御
int DefenseGain(Status* gainer, int gain_value){
    gainer->defense += gain_value;
    std::cout << "，增加" << gain_value << "点防，剩余" << gainer->defense << "点防";
    return 0;
}

// 结算获得灵气
int LingQiGain(Status* gainer, int gain_value){
    // 灵凤获得双倍
    gainer->ling_qi += gain_value;
    std::cout << "，获得" << gain_value << "点灵气，剩余" << gainer->ling_qi << "点灵气";
    return 0;
}

// 结算失去灵气，最小为0
int LingQiLoss(Status* losser, int loss_value){
    losser->ling_qi -= loss_value;
    if (losser->ling_qi < 0) {
        losser->ling_qi = 0;
    }
    std::cout << "消耗" << loss_value << "点灵气";
    return 0;
}

// 消耗所有灵气，并返回消耗的灵气值
int LingQiCostAll(Status* coster){
    int cost_value = coster->ling_qi;
    LingQiLoss(coster, cost_value);
    return cost_value;
}

// 消耗最多n点灵气，并返回消耗的灵气值（耗X灵气）
int LingQiCostMax(Status* coster, int max_cost_value){
    int cost_value = coster->ling_qi;
    if (cost_value > max_cost_value) {
        cost_value = max_cost_value;
    }
    LingQiLoss(coster, cost_value);
    return cost_value;
}

// buff获取
int BuffGain(Status* gainer, int buff_type, int gain_value){
    // 结算获得buff
    switch (buff_type) {
    case BUFF_QI_SHI:
        // 气势超过上限部分转为防
        if (gainer->buff.buff[BUFF_QI_SHI] + gain_value > gainer->buff.buff[BUFF_QI_SHI_MAX]) {
            int exceed_value = gainer->buff.buff[BUFF_QI_SHI] + gain_value - gainer->buff.buff[BUFF_QI_SHI_MAX];
            gainer->buff.buff[BUFF_QI_SHI] = gainer->buff.buff[BUFF_QI_SHI_MAX];
            DefenseGain(gainer, exceed_value);
            if (exceed_value > 0) {
                std::cout << "，获得" << gain_value << "点气势，超出部分转为" << exceed_value << "点防";
            }
            else {
                std::cout << "，获得" << gain_value << "点气势";
            }
            break;
        }
        break;
    default:
        gainer->buff.buff[buff_type] += gain_value;
        std::cout << "，获得" << gain_value << "层" << buff_type;
        break;
    }
    return 0;
}

// buff减少，最小为0
int BuffReduce(Status* reducer, int buff_type, int reduce_value){
    // 结算减少buff
    reducer->buff.buff[buff_type] -= reduce_value;
    if (reducer->buff.buff[buff_type] < 0) {
        reducer->buff.buff[buff_type] = 0;
    }
    std::cout << "，减少" << reduce_value << "层" << buff_type;
    return 0;
}

// debuff获取
int DebuffGain(Status* gainer, int debuff_type, int gain_value){
    // 如果有辟邪，则减少同时减少辟邪和debuff的获取层数
    if (gainer->buff.buff[BUFF_BI_XIE]) {
        int pi_xie_reduce = gainer->buff.buff[BUFF_BI_XIE];
        if (pi_xie_reduce > gain_value) {
            pi_xie_reduce = gain_value;
        }
        std::cout << "，辟邪生效";
        gain_value -= pi_xie_reduce;
        BuffReduce(gainer, BUFF_BI_XIE, pi_xie_reduce);
    }
    // 结算获得debuff
    gainer->buff.buff[debuff_type] += gain_value;
    std::cout << "，获得" << gain_value << "层" << debuff_type;
    return 0;
}

// 再次行动获取
int ReexecuteGain(Status* gainer){
    gainer->flag.flag[FLAG_ZAI_CI_XING_DONG] = true;
    std::cout << "，获得再次行动效果";
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

// 体魄获取，体魄的结算比较特殊，体魄可以超过土坯上限，体魄能提供等额血量上限
// 当体魄超过体魄上限时，超出部分将额外恢复血量
int TiPoGain(Status* gainer, int gain_value){
    // 结算获得体魄
    int ti_po_exceed = 0;
    if (gainer->ti_po < gainer->ti_po_max) {
        if (gain_value + gainer->ti_po > gainer->ti_po_max) {
            ti_po_exceed = gain_value + gainer->ti_po - gainer->ti_po_max;
        }
    }
    else {
        ti_po_exceed = gain_value;
    }
    gainer->ti_po += gain_value;
    gainer->ti_po_battle_gain += gain_value;
    std::cout << "，获得" << gain_value << "点体魄，当前" << gainer->ti_po << "/" << gainer->ti_po_max << "点体魄";
    HealthMaxGain(gainer, gain_value);
    if (ti_po_exceed > 0) {
        HealthGain(gainer, ti_po_exceed);
    }
    return 0;
}

// 生成指定范围内的整型随机数
int RandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int DebuffReduce(Status* reducer, int debuff_type, int reduce_value){
    // 结算减少debuff
    reducer->buff.buff[debuff_type] -= reduce_value;
    std::cout << "，减少" << reduce_value << "层" << debuff_type;
    return 0;
}

// 计算debuff总层数
int DebuffTotal(Status* status){
    int total = 0;
    for (int i = 0; i < DEBUFF_END_INDEX - DEBUFF_START_INDEX; i++) {
        total += status->buff.buff[DEBUFF_START_INDEX + i];
    }
    return total;
}

// 将debuff_type按照层数从大到小排序，返回排序后的debuff_type数组
// debuff_type数组长度为DEBUFF_END_INDEX - DEBUFF_START_INDEX
int* DebuffSort(Status* sorter){
    int* debuff_type = new int[DEBUFF_END_INDEX - DEBUFF_START_INDEX];
    for (int i = 0; i < DEBUFF_END_INDEX - DEBUFF_START_INDEX; i++) {
        debuff_type[i] = DEBUFF_START_INDEX + i;
    }
    // 快速排序
    int left = 0;
    int right = DEBUFF_END_INDEX - DEBUFF_START_INDEX - 1;
    int temp;
    while (left < right) {
        while (left < right && sorter->buff.buff[debuff_type[right]] <= sorter->buff.buff[debuff_type[left]]) {
            right--;
        }
        if (left < right) {
            temp = debuff_type[left];
            debuff_type[left] = debuff_type[right];
            debuff_type[right] = temp;
            left++;
        }
        while (left < right && sorter->buff.buff[debuff_type[right]] >= sorter->buff.buff[debuff_type[left]]) {
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



// 随机减少总计n层debuff，每种debuff至少减少到0，n为正数
// 先获取debuff_type按照层数从大到小排序，并得到大于0的debuff种类数量
// 随机减少大于0的debuff
// 当is_transfer_to_enemy为true时，将减少的debuff转移给敌方，enemy为敌方状态指针
int DebuffRandomReduce(Status* reducer, int reduce_value, bool is_transfer_to_enemy = false, Status* enemy = nullptr){
    int* debuff_type = DebuffSort(reducer);
    int debuff_count = 0;
    for (int i = 0; i < DEBUFF_END_INDEX - DEBUFF_START_INDEX; i++) {
        if (reducer->buff.buff[debuff_type[i]] > 0) {
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
        if (reducer->buff.buff[debuff_type[random_index]] > 0) {
            DebuffReduce(reducer, debuff_type[random_index], 1);
            if (is_transfer_to_enemy) {
                DebuffGain(enemy, debuff_type[random_index], 1);
                std::cout << "，转移" << debuff_type[random_index] << "1层";
            }
            std::cout << "，减少" << debuff_type[random_index] << "1层";
            reduce_count++;
            // 如果减少到0，则减少debuff_count，并将该debuff_type与最后一个debuff_type交换
            if (reducer->buff.buff[debuff_type[random_index]] == 0) {
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

#endif // !ACCOUNT_H