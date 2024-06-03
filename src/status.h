#ifndef STATUS_H
#define STATUS_H

#include "flag.h"
#include "head.h"
#include "effect_task_quene.h"
#include "account_task_quene.h"
#include "./status_effects/status_effects.h"

class Deck; // 前置声明

/*
状态类
新增任何指针成员变量时，需要在拷贝构造函数中拷贝，在构造函数中初始化，在析构函数中删除
新增任何非指针成员变量时，需要在拷贝构造函数中拷贝，在构造函数中初始化
*/
class Status {
public:
    // 构造函数
    Status(Deck* deck) : deck(deck) {
        // 初始化状态值
        health = new Health(this, 60); // 血量
        health_max = new HealthMax(this, 60); // 血量上限
        defense = new Defense(this, 0); // 防御
        ling_qi = new LingQi(this, 0); // 灵气
        xiu_wei = new XiuWei(this, 0); // 修为
        speed = new Speed(this, 0); // 速度
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
        task_quene_before_ling_qi_cost = new EffectTaskQueue(this);
        task_quene_before_round = new AccountTaskQueue(this);
        task_quene_after_round = new AccountTaskQueue(this);
        task_quene_before_attack = new AccountTaskQueue(this);
        task_quene_after_attack = new AccountTaskQueue(this);
        task_quene_at_battle_start = new AccountTaskQueue(this);
    
    }

    // 虚拷贝函数
    virtual Status* Clone(Deck* new_deck) const {
        return new Status(*this, new_deck);
    }

    // 拷贝构造函数
    Status(const Status& other, Deck* new_deck) : deck(new_deck) {
        // 初始化状态值
        health = other.health->Clone(this); // 血量
        health_max = other.health_max->Clone(this); // 血量上限
        defense = other.defense->Clone(this); // 防御
        ling_qi = other.ling_qi->Clone(this); // 灵气
        xiu_wei = other.xiu_wei->Clone(this); // 修为
        speed = other.speed->Clone(this); // 速度
        ti_po = other.ti_po->Clone(this); // 体魄
        ti_po_max = other.ti_po_max->Clone(this); // 体魄上限

        // 初始化星位
        for (int i = 0; i < DECK_END_INDEX; i++) {
            is_xing_wei[i] = other.is_xing_wei[i];
        }
        // 初始化牌可用
        for (int i = 0; i < DECK_END_INDEX; i++) {
            is_usable[i] = other.is_usable[i];
        }
        // 初始化buffs和debuff
        for (int i = 0; i < BUFF_END_INDEX; i++) {
            buffs[i] = other.buffs[i]->Clone(this);
        }
        for (int i = 0; i < DEBUFF_END_INDEX; i++) {
            debuffs[i] = other.debuffs[i]->Clone(this);
        }

        // 使用卡牌的状态记录
        is_card_attacked = other.is_card_attacked;
        using_card_position = other.using_card_position;
        using_yun_jian_continuous = other.using_yun_jian_continuous;
        attack_damage_percent = other.attack_damage_percent;

        task_quene_before_effect = other.task_quene_before_effect->Clone(this);
        task_quene_after_effect = other.task_quene_after_effect->Clone(this);
        task_quene_before_ling_qi_cost = other.task_quene_before_ling_qi_cost->Clone(this);
        task_quene_before_round = other.task_quene_before_round->Clone(this);
        task_quene_after_round = other.task_quene_after_round->Clone(this);
        task_quene_before_attack = other.task_quene_before_attack->Clone(this);
        task_quene_after_attack = other.task_quene_after_attack->Clone(this);
        task_quene_at_battle_start = other.task_quene_at_battle_start->Clone(this);
        
        // Flag对象
        flag = other.flag;
        // 卡牌效果数值映射
        card_effect_val_map = other.card_effect_val_map;
        // 使用文字样式
        style = other.style;
    }

    // 析构函数
    ~Status() {

        // 删除状态值
        delete health;
        delete health_max;
        delete defense;
        delete ling_qi;
        delete xiu_wei;
        delete speed;
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
        delete task_quene_before_ling_qi_cost;
        delete task_quene_before_round;
        delete task_quene_after_round;
        delete task_quene_before_attack;
        delete task_quene_after_attack;
        delete task_quene_at_battle_start;
    }

    /*
    切换到下一张卡牌位置
    如果牌已被消耗，则跳过
    */
    void NextCardPosition();

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

    // card_effect_val_map中某个键是否存在
    bool IsCardEffectValExist(std::string key) {
        return card_effect_val_map.find(key) != card_effect_val_map.end();
    }

    // 给出一个键和一个增加的数值(可为负数)以及不存在时是否创建的判断，如果键存在则增加，不存在则创建, 目标为card_effect_val_map, 返回值为是否存在
    bool AddOrSubCardEffectVal(std::string key, int val, bool create) {
        if (IsCardEffectValExist(key)) {
            card_effect_val_map[key] += val;
            return true;
        } else {
            if (create) {
                card_effect_val_map[key] = val;
                return true;
            } else {
                return false;
            }
        }
    }

    // 获取card_effect_val_map中某个键的值
    int GetCardEffectVal(std::string key) {
        if (IsCardEffectValExist(key)) {
            return card_effect_val_map[key];
        } else {
            return 0;
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
    std::unordered_map<std::string, int> card_effect_val_map; // 卡牌效果数值映射, 通过AddCardEffectVal方法添加
    // 每个Status带一个Deck对象指针
    Deck* deck;

    
    // 任务队列
    EffectTaskQueue* task_quene_before_effect; // 卡牌效果执行前的任务队列，参数为使用的牌
    EffectTaskQueue* task_quene_after_effect; // 卡牌效果执行后的任务队列，参数为使用的牌，给下一张牌的执行后任务队列的任务必须通过卡牌效果执行前的任务队列放入
    EffectTaskQueue* task_quene_before_ling_qi_cost; // 灵气消耗前的任务队列，参数为使用的牌，执行队列参数为牌的灵气消耗
    AccountTaskQueue* task_quene_before_round; // 回合开始时触发的任务队列，参数为回合数
    AccountTaskQueue* task_quene_after_round; // 回合结束时触发的任务队列，参数为回合数
    AccountTaskQueue* task_quene_before_attack; // 攻击前触发的任务队列（计算变更攻击数值的buff之前），参数为攻击数值
    AccountTaskQueue* task_quene_after_attack; // 攻击后触发的任务队列，参数为造成的伤害
    AccountTaskQueue* task_quene_at_battle_start; // 战斗开始时触发的任务队列，参数为战斗轮数

    // 状态值
    StatusVal* health; // 血量
    StatusVal* health_max; // 血量上限
    StatusVal* defense; // 防御
    StatusVal* ling_qi; // 灵气
    StatusVal* xiu_wei; // 修为
    StatusVal* speed; // 速度
    StatusVal* ti_po; // 体魄
    StatusVal* ti_po_max; // 体魄上限

    bool is_xing_wei[DECK_END_INDEX]; // 某各格子的位置是否是星位
    bool is_usable[DECK_END_INDEX]; // 某个格子的牌是否可用（未被消耗）(使用的消耗牌和持续牌将被消耗）

    // Buff和Debuff
    Buff* buffs[BUFF_END_INDEX]; // buff
    Debuff* debuffs[DEBUFF_END_INDEX]; // debuff
    
    // 使用卡牌的状态记录
    bool is_card_attacked;
    int using_card_position; // 将使用卡牌的位置
    int using_yun_jian_continuous; // 连续使用云剑的次数（！未启用）
    float attack_damage_percent; // 临时记录伤害百分比

    // 使用文字样式
    std::string style = "";
};
#endif // !STATUS_H