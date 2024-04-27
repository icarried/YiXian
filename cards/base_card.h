#ifndef BASE_CARD_H
#define BASE_CARD_H

#include <string>
#include "../account.h"
#include "../head.h"

#define PU_TONG_GONG_JI_CARD 0 //普通攻击牌
#define XIAO_HAO_CARD 1 //消耗牌
#define CHI_XU_CARD 2 //持续牌
#define LING_JIAN_CARD 3 //灵剑牌
#define YUN_JIAN_CARD 4 //云剑牌
#define KUANG_JIAN_CARD 5 //狂剑牌
#define BENG_QUAN_CARD 6 //崩拳牌
#define TI_PO_CARD 7 //体魄牌
#define CARD_TAG_END_INDEX 8 //牌标签结束索引



/*
牌基础类
继承该类的子类需要实现Effect函数，用于执行牌的效果
构造函数为 Card_XXX(int level, int position) : BaseCard(level, position) {}

命名方法：
牌以Card_开头，后面跟牌的信息
card_{门派或副职或机缘}_{境界}_{牌名}

*门派或副职或机缘*：
云灵剑宗：yl
七星阁：qx
五行道盟：wx
锻玄宗：dx

炼丹师：lds
符箓师：fls
琴师：qs
画师：hs
阵法师：zfs
灵植师：lzs

法宝：fbjy
灵兽：lsjy
云灵剑宗机缘：yljy
七星阁机缘：qxjy
五行道盟机缘：wxjy
锻玄宗机缘：dxjy

其他：qt

*境界*：
炼气期：lqq
筑基期：zjq
金丹期：jdq
元婴期：yyq
化神期：hsq
返虚期：fxq
其他：qtq
*/
class BaseCard {
public:
    //构造函数
    BaseCard(int level, int position) : level(level), position(position) {
        card_name = "基础牌";
        is_attacking = false;
        attack = 0;
        ling_qi_cost = 0;
        //牌标签数组，初始化为false
        for (int i = 0; i < CARD_TAG_END_INDEX; i++) {
            card_tag[i] = 0;
        }
        //牌特殊属性数组，初始化为false
        for (int i = 0; i < CARD_SP_ATTR_END_INDEX; i++) {
            card_sp_attr[i] = 0;
        }
        //效果启用标志
        is_ling_qi_cost_modifiable = false;
        is_health_cost_modifiable = false;
        is_health_cost = false;
        health_cost = 0;
        is_before_task_queue_effect = false;
    }
    
    ~BaseCard(){
        
    }

    //虚函数，执行牌的效果，并返回执行状态值
    virtual int Effect(Status* my_status, Status* enemy_status){
        return 0;
    }
    //修改后的执行牌的灵气消耗，通过is_ling_qi_cost_modifiable启用
    virtual int LingQiCostModify(Status* my_status, Status* enemy_status){
        return ling_qi_cost;
    }
    //修改后的执行牌的血量消耗，通过is_health_cost_modifiable启用
    virtual int HealthCostModify(Status* my_status, Status* enemy_status){
        return health_cost;
    }
    // 前置于任务队列效果，必须is_before_task_queue_effect为true
    virtual int BeforeTaskQueueEffect(Status* my_status, Status* enemy_status){
        return 0;
    }
    //本牌受效果影响获得指定的牌标签
    void CardTagGain(int tag){
        card_tag[tag] += 1;
    }
    //本牌受效果结束影响失去指定的牌标签
    void CardTagLost(int tag){
        if (card_tag[tag] > 0)
            card_tag[tag] -= 1;
    }
    //本牌受效果影响获得指定的牌特殊属性
    void CardSpAttrGain(int sp_attr){
        card_sp_attr[sp_attr] += 1;
    }
    //本牌受效果结束影响失去指定的牌特殊属性
    void CardSpAttrLost(int sp_attr){
        if (card_sp_attr[sp_attr] > 0)
            card_sp_attr[sp_attr] -= 1;
    }

    std::string card_name; //牌名
    int level; //牌等级
    int position; //牌位置
    bool is_attacking; //是否为攻击牌
    int attack; //攻
    int ling_qi_cost; //灵气耗费
    bool is_health_cost; //是否为血量耗费
    int health_cost; //血量耗费
    int card_tag[CARD_TAG_END_INDEX]; //牌标签（大于0则视为true，方便多重效果重复影响结算）
    int card_sp_attr[CARD_SP_ATTR_END_INDEX]; //牌特殊属性（大于0则视为true，方便多重效果重复影响结算）(需要作为Attack的参数传入)
    bool is_ling_qi_cost_modifiable; //灵气消耗是否可修改，可以则通过LingQiCostModify函数决定灵气消耗
    bool is_health_cost_modifiable; //血量消耗是否可修改，可以则通过HealthCostModify函数决定血量消耗

    bool is_before_task_queue_effect; //是否有前置于任务队列效果（用于对任务队列进行操作）

};
#endif // !BASE_CARD_H



