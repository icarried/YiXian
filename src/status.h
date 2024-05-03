#ifndef STATUS_H
#define STATUS_H

// #include "buff.h"
#include "flag.h"
#include "head.h"
#include "effect_task_quene.h"
#include "account_task_quene.h"
#include "./status_effects/buffs.h"
#include "./status_effects/debuffs.h"
#include "./status_effects/status_vals.h"
#include "./status_effects/status_effects.h"

class Deck; // 前置声明

// 状态类

class Status {
public:
    // 构造函数
    Status(Deck* deck) : deck(deck) {
        // 初始化状态值
        health_sub_total = new HealthSubTotal(this, 0); // 失去的血量总和
        ti_po_add_total = new TiPoAddTotal(this, 0); // 体魄增加总和
        health = new Health(this, 60); // 血量
        health_max = new HealthMax(this, 60); // 血量上限
        defense = new Defense(this, 0); // 防御
        ling_qi = new LingQi(this, 0); // 灵气
        xiu_wei = new XiuWei(this, 0); // 修为
        ti_po = new TiPo(this, 0); // 体魄
        ti_po_max = new TiPoMax(this, 0); // 体魄上限

        // 初始化星位
        for (int i = 0; i < DECK_END_INDEX; i++) {
            if ( i == 2 || i == 5 )
                is_xing_wei[i] = true;
            else
                is_xing_wei[i] = false;
        }
        // 初始化牌可用
        for (int i = 0; i < DECK_END_INDEX; i++) {
            is_usable[i] = true;
        }
        // 初始化buffs和debuff
        num_buffs = 0;
        num_debuffs = 0;
        for (int i = 0; i < BUFF_END_INDEX; i++) {
            buffs[i] = buff_create(i, this, 0);
        }
        buffs[BUFF_QI_SHI_MAX]->setValue(6); // 气势上限默认为6
        for (int i = 0; i < DEBUFF_END_INDEX; i++) {
            debuffs[i] = debuff_create(i, this, 0);
        }
        
        // 使用卡牌的状态记录
        is_card_attacked = false;
        using_card_position = 0;
        using_yun_jian_continuous = 0;
        attack_damage_percent = 0.0f;


        task_quene_before_effect = new EffectTaskQueue(this);
        task_quene_after_effect = new EffectTaskQueue(this);
        task_quene_after_round = new AccountTaskQueue(this);

        // 校验(目前校验无作用，因为buff和debuff数量是固定的)
        if (num_buffs != BUFF_END_INDEX) {
            std::cout << "error:--buff数量校验失败--" << std::endl;
            exit(1);
        }
        if (num_debuffs != DEBUFF_END_INDEX) {
            std::cout << "error:--debuff数量校验失败--" << std::endl;
            exit(1);
        }
    
    }

    // 析构函数
    ~Status() {

        // 删除状态值
        delete health_sub_total;
        delete ti_po_add_total;
        delete health;
        delete health_max;
        delete defense;
        delete ling_qi;
        delete xiu_wei;
        delete ti_po;
        delete ti_po_max;

        // 删除buff和debuff
        for (int i = 0; i < BUFF_END_INDEX; i++) {
            delete buffs[i];
        }
        for (int i = 0; i < DEBUFF_END_INDEX; i++) {
            delete debuffs[i];
        }

        // 删除任务队列
        delete task_quene_before_effect;
        delete task_quene_after_effect;
        delete task_quene_after_round;
    }

    /*
    切换到下一张卡牌位置
    如果牌已被消耗，则跳过
    */
    void NextCardPosition(){
        do {
            using_card_position++;
            if (using_card_position >= DECK_END_INDEX) {
                using_card_position = 0;
            }
        } while (!is_usable[using_card_position]);
    }

    /*
    打印主要状态
    */
    void ShowStatus() {
        std::cout << "血量：" << health->getValue() << "/" << health_max->getValue() << "，灵气：" << ling_qi->getValue();
        if (defense->getValue() > 0) {
            std::cout << "，防：" << defense->getValue();
        }
        if (ti_po->getValue() > 0) {
            std::cout << "，体魄：" << ti_po->getValue() << "/" << ti_po_max->getValue();
        }
        std::cout << " ";
        ShowBuff();
        std::cout << " ";
        ShowDebuff();
        std::cout << std::endl;
    }

    void ShowBuff() {
        for (int i = 0; i < BUFF_END_INDEX; i++) {
            if (this->buffs[i]->getValue() != 0) {
                std::cout << this->buffs[i]->name << ": " << this->buffs[i]->getValue() << " ";
            }
        }
    }

    void ShowDebuff() {
        for (int i = 0; i < DEBUFF_END_INDEX; i++) {
            if (this->debuffs[i]->getValue() != 0) {
                std::cout << this->debuffs[i]->name << ": " << this->debuffs[i]->getValue() << " ";
            }
        }
    }

    // 结算BUFF变更
    void attack_change();
    void a_card_change();
    void a_damage_change(bool attacking, bool hurting);
    void a_side_round_change();

    /*
    仅声明：获取Deck中position位置的卡牌指针
    */
    BaseCard* GetCard(int position);

    // 每个Status带一个Flag对象
    Flag flag;
    // 每个Status带一个Deck对象指针
    Deck* deck;

    
    // 任务队列
    EffectTaskQueue* task_quene_before_effect; // 卡牌效果执行前的任务队列，参数为使用的牌
    EffectTaskQueue* task_quene_after_effect; // 卡牌效果执行后的任务队列，参数为使用的牌，给下一张牌的执行后任务队列的任务必须通过卡牌效果执行前的任务队列放入
    AccountTaskQueue* task_quene_after_round; // 回合结束时触发的任务队列，参数为回合数

    // 状态值
    StatusVal* health_sub_total; // 该次战斗中失去的血量总和
    StatusVal* ti_po_add_total; // 该次战斗中体魄增加总和
    StatusVal* health; // 血量
    StatusVal* health_max; // 血量上限
    StatusVal* defense; // 防御
    StatusVal* ling_qi; // 灵气
    StatusVal* xiu_wei; // 修为
    StatusVal* ti_po; // 体魄
    StatusVal* ti_po_max; // 体魄上限

    bool is_xing_wei[DECK_END_INDEX]; // 某各格子的位置是否是星位
    bool is_usable[DECK_END_INDEX]; // 某个格子的牌是否可用（未被消耗）(使用的消耗牌和持续牌将被消耗）

    // Buff和Debuff
    int num_buffs; // buff数量，每注册一个buff，num_buffs+1，用于校验
    int num_debuffs; // debuff数量，每注册一个debuff，num_debuffs+1，用于校验
    Buff* buffs[BUFF_END_INDEX]; // buff
    Debuff* debuffs[DEBUFF_END_INDEX]; // debuff
    
    // 使用卡牌的状态记录
    bool is_card_attacked;
    int using_card_position; // 将使用卡牌的位置
    int using_yun_jian_continuous; // 连续使用云剑的次数（！未启用）
    float attack_damage_percent; // 临时记录伤害百分比
};
#endif // !STATUS_H