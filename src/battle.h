#ifndef BATTLE_H
#define BATTLE_H

#include <iostream>
#include <string>
#include "status.h"
#include "deck.h"
#include "./cards/cards.h"
#include "head.h"


#define BATTLE_END_ROUND 30 // 战斗最大回合数, 目前暂不确定

// 注意回合过多时将强制结束战斗

class Battle {
public:
    // 构造函数
    Battle(int battle_round) : battle_round(battle_round) {
        my_deck = new Deck();
        enemy_deck = new Deck();
        decks[0] = my_deck;
        decks[1] = enemy_deck;

        // 初始化状态，传入对应deck指针（方便检索卡组的效果）
        my_status = new Status(my_deck);
        enemy_status = new Status(enemy_deck);
        statuss[0] = my_status;
        statuss[1] = enemy_status;
        // 初始化随机数种子
        srand((unsigned)time(NULL));

    }
    
    // 析构函数
    ~Battle() {
        delete my_status;
        delete enemy_status;
        delete my_deck;
        delete enemy_deck;
    }

    /*
    命元伤害计算
    参数：胜利方status，失败方status
    最终生命差：胜利方生命-失败方生命
    轮次数：this->battle_round
    最终生命差<=20时，命元伤害=轮次数+最终生命差/5（向上取整）
    最终生命差>20时，命元伤害=轮次数+4+（最终生命差-20）/10（向上取整，且最大不超过2+轮次数的一半）
    */
    int MingYuanDamage(Status *win_status, Status *lose_status) {
        int health_diff = win_status->health->getValue() - lose_status->health->getValue();
        int ming_yuan_damage = 0;
        if (health_diff <= 20) {
            ming_yuan_damage = this->battle_round + (health_diff + 4) / 5;
        }
        else {
            ming_yuan_damage = this->battle_round + 4 + (health_diff - 20 + 9) / 10;
            ming_yuan_damage = ming_yuan_damage > (this->battle_round + 4 + this->battle_round / 2 + 2) ? (this->battle_round + 4 + this->battle_round / 2 + 2) : ming_yuan_damage;
        }
        return ming_yuan_damage;
    }

    // 战斗结束数值结算
    // statuss[0]为我方，statuss[1]为敌方
    // 返回值为正数，胜利方为我方，负数为敌方，0为平局，绝对值为血量差
    int BattleEnd() {
        Status *win_status;
        Status *lose_status;
        bool is_draw = false; // 是否平局
        if (statuss[0]->health->getValue() > statuss[1]->health->getValue()) {
            std::cout << "我方胜利" << std::endl;
            win_status = statuss[0];
            lose_status = statuss[1];
        }
        else if (statuss[0]->health->getValue() < statuss[1]->health->getValue()) {
            std::cout << "敌方胜利" << std::endl;
            win_status = statuss[1];
            lose_status = statuss[0];
        }
        else {
            std::cout << "平局" << std::endl;
            is_draw = true;
        }
        std::cout << "我方剩余血量：" << statuss[0]->health->getValue() << std::endl;
        std::cout << "敌方剩余血量：" << statuss[1]->health->getValue() << std::endl;
        // 结算命元伤害
        int ming_yuan_damage = 0;
        if (!is_draw) {
            ming_yuan_damage = MingYuanDamage(win_status, lose_status);
            std::cout << "命元伤害：" << ming_yuan_damage << std::endl;
        }
        return statuss[0]->health->getValue() - statuss[1]->health->getValue();
    }

    // 战斗开始
    // statuss[0]为我方，statuss[1]为敌方
    // decks[0]为我方，decks[1]为敌方
    // 返回值为正数，胜利方为我方，负数为敌方，0为平局，绝对值为血量差
    int BattleStart() {
        int side;
        int other_side;
        for (this->round = 1; this->round < BATTLE_END_ROUND; this->round++) {
            std::cout << "--------第" << this->round << "回合--------" << std::endl;
            for (side = 0; side < 2; side++) {
                other_side = (side + 1) % 2;
                std::cout << side_string[side] << "回合" << std::endl;
                statuss[side]->ShowStatus();
                // 双方轮流行动
                // 1. 检查回合buff
                if (statuss[side]->debuffs[DEBUFF_NEI_SHANG]->getValue() > 0) {
                    // 内伤
                    NonSourseDamage(statuss[side], statuss[side]->debuffs[DEBUFF_NEI_SHANG]->getValue());
                    std::cout << side_string[side]  << "受到内伤造成" << statuss[side]->debuffs[DEBUFF_NEI_SHANG]->getValue() << "点伤害" << std::endl;
                }
                if (statuss[0]->health->getValue() <= 0 || statuss[1]->health->getValue() <= 0) {
                    // 有一方血量为0则结束战斗
                    return BattleEnd();
                }
                if (statuss[side]->defense->getValue() > 0) {
                    // 有防御则减少一半防御
                    int target_defense = statuss[side]->defense->getValue() / 2;
                    statuss[side]->defense->sub(statuss[side]->defense->getValue() - target_defense);
                    std::cout << side_string[side] << "防减半，剩余" << statuss[side]->defense->getValue() << "点防" << std::endl;
                }

                // 2. 行动相关，一回合可能包含多次行动
                if (statuss[side]->buffs[WU_FA_XING_DONG]->getValue() > 0) {
                    // 无法行动，优先于使用牌
                    std::cout << side_string[side] << "无法行动" << std::endl;
                    statuss[side]->buffs[WU_FA_XING_DONG]->sub(1);
                    continue;
                }
                bool reexecute = false;
                // 首次执行或再次行动时执行
                // 当有再次行动buff且未当前回合为发动再次行动时，再次行动
                while (statuss[side]->flag.flag[FLAG_ZAI_CI_XING_DONG] 
                && !statuss[side]->flag.flag[FLAG_YI_ZAI_CI_XING_DONG] 
                || !reexecute) {
                    if (reexecute) {
                        std::cout << side_string[side] << "再次行动" << std::endl;
                    }
                    if (statuss[side]->buffs[SKIP_CARD]->getValue() > 0){
                        // 跳过下N张牌
                        while (statuss[side]->buffs[SKIP_CARD]->getValue() > 0){
                            statuss[side]->buffs[SKIP_CARD]->sub(1);
                            statuss[side]->NextCardPosition();
                            std::cout << side_string[side] << "跳过一张牌" << std::endl;
                        }
                    }
                    // 开始根据当前使用的牌进行判断
                    // 牌消耗，判断灵气消耗
                    int card_ling_qi_cost = 0;
                    if (decks[side]->cards[statuss[side]->using_card_position]->is_ling_qi_cost_modifiable) {
                        card_ling_qi_cost = decks[side]->cards[statuss[side]->using_card_position]->LingQiCostModify(statuss[side], statuss[other_side]);
                    }
                    else {
                        card_ling_qi_cost = decks[side]->cards[statuss[side]->using_card_position]->ling_qi_cost;
                    }
                    if (statuss[side]->ling_qi->getValue() < card_ling_qi_cost) {
                        // 灵气不足，则恢复一点灵气，不使用牌
                        statuss[side]->ling_qi->add(1);
                        std::cout << side_string[side] << "灵气不足，恢复一点灵气" << std::endl;
                    }
                    else {
                        // 正常消耗灵气使用牌
                        if (card_ling_qi_cost) {
                            statuss[side]->ling_qi->sub(card_ling_qi_cost);
                            std::cout<< "，";
                        }
                        // 如果耗费血量
                        if (decks[side]->cards[statuss[side]->using_card_position]->is_health_cost) {
                            int card_health_cost = 0;
                            if (decks[side]->cards[statuss[side]->using_card_position]->is_health_cost_modifiable) {
                                card_health_cost = decks[side]->cards[statuss[side]->using_card_position]->HealthCostModify(statuss[side], statuss[other_side]);
                            }
                            else {
                                card_health_cost = decks[side]->cards[statuss[side]->using_card_position]->health_cost;
                            }

                            statuss[side]->health->sub(card_health_cost);
                            std::cout << "消耗" << card_health_cost << "点血量，";
                        }
                        // 执行牌效果Effect开始
                        std::cout << "使用了第" << statuss[side]->using_card_position + 1 << "张牌" << decks[side]->cards[statuss[side]->using_card_position]->level << "级《" << decks[side]->cards[statuss[side]->using_card_position]->card_name << "》";
                        if (decks[side]->cards[statuss[side]->using_card_position]->is_before_task_queue_effect) {
                            decks[side]->cards[statuss[side]->using_card_position]->BeforeTaskQueueEffect(statuss[side], statuss[other_side]);
                        }
                        statuss[side]->task_quene_before_effect->executeTaskQueue(decks[side]->cards[statuss[side]->using_card_position]);
                        decks[side]->cards[statuss[side]->using_card_position]->Effect(statuss[side], statuss[other_side]);
                        statuss[side]->task_quene_after_effect->executeTaskQueue(decks[side]->cards[statuss[side]->using_card_position]);
                        // 若为消耗牌或持续牌，使用后将被消耗
                        if (decks[side]->cards[statuss[side]->using_card_position]->card_tag[XIAO_HAO_CARD] || decks[side]->cards[statuss[side]->using_card_position]->card_tag[CHI_XU_CARD]) {
                            statuss[side]->is_usable[statuss[side]->using_card_position] = false;
                        }
                        statuss[side]->a_card_change();
                        // 执行牌效果Effect结束
                        //切换到下一张牌
                        statuss[side]->NextCardPosition();
                    }
                    std::cout << std::endl;
                    if (statuss[0]->health->getValue() <= 0 || statuss[1]->health->getValue() <= 0) {
                        // 有一方血量为0则结束战斗
                        return BattleEnd();
                    }

                    // 回合结束，回合结束buff结算
                    statuss[side]->a_side_round_change();
                    statuss[side]->flag.a_side_round_change();
                    statuss[side]->task_quene_after_round->executeTaskQueue(this->round);
                    
                    // 如果有无法再次行动buff，则跳出
                    if (statuss[side]->flag.flag[FLAG_WU_FA_ZAI_CI_XING_DONG]) {
                        ReexecuteLoss(statuss[side]);
                        std::cout << side_string[side] << "无法再次行动" << std::endl;
                        break;
                    }
                    // 如果有debuff困缚，困缚减一层，并跳出
                    else if (statuss[side]->debuffs[DEBUFF_KUN_FU]->getValue() > 0) {
                        ReexecuteLoss(statuss[side]);
                        std::cout << side_string[side] << "因困缚无法再次行动" << std::endl;
                        break;
                    }
                    
                    // 若未再次行动，且没有再次行动flag，身法>=10则将10点身法转化为一次再次行动flag
                    if (!reexecute && !statuss[side]->flag.flag[FLAG_ZAI_CI_XING_DONG] && statuss[side]->buffs[BUFF_SHEN_FA]->getValue() >= 10) {
                        statuss[side]->buffs[BUFF_SHEN_FA]->sub(10);
                        ReexecuteGain(statuss[side]);
                        std::cout << side_string[side] << "身法转化为再次行动" << std::endl;
                    }

                    // 如果为第二次行动，将标记为已再次行动
                    if (reexecute) {
                        ReexecuteAlreadyGain(statuss[side]);
                    }else {
                        reexecute = true;
                    }
                }
            }
        }
        // 战斗回合数超过最大回合数，强制结束战斗
        std::cout << "战斗回合数超过最大回合数，强制结束战斗" << std::endl;
        return BattleEnd();
    }

    Status *my_status;
    Status *enemy_status;
    Status *statuss[2];

    Deck *my_deck;
    Deck *enemy_deck;
    Deck *decks[2];

    const std::string side_string[2] = {"我方", "敌方"};
    int round = 0; // 回合数, 从1开始
    // 本次战斗的轮次数（不是回合数）
    int battle_round;
};


#endif // !BATTLE_H