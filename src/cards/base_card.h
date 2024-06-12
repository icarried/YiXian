#ifndef BASE_CARD_H
#define BASE_CARD_H

#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <memory>
#include "../status.h"
#include "../account.h"
#include "../head.h"

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

专属仙命牌：zsxm
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
        sovj = SECT_NONE;
        realm = REALM_NONE;
        card_name = "基础牌";
        is_level_modifiable = true;
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

    virtual BaseCard* Clone() const {
        return new BaseCard(*this);
    }

    //拷贝构造函数
    BaseCard(const BaseCard& other) {
        sovj = other.sovj;
        realm = other.realm;
        card_name = other.card_name;
        level = other.level;
        is_level_modifiable = other.is_level_modifiable;
        position = other.position;
        is_attacking = other.is_attacking;
        attack = other.attack;
        ling_qi_cost = other.ling_qi_cost;
        for (int i = 0; i < CARD_TAG_END_INDEX; i++) {
            card_tag[i] = other.card_tag[i];
        }
        for (int i = 0; i < CARD_SP_ATTR_END_INDEX; i++) {
            card_sp_attr[i] = other.card_sp_attr[i];
        }
        is_ling_qi_cost_modifiable = other.is_ling_qi_cost_modifiable;
        is_health_cost_modifiable = other.is_health_cost_modifiable;
        is_health_cost = other.is_health_cost;
        health_cost = other.health_cost;
        is_before_task_queue_effect = other.is_before_task_queue_effect;
    }
    
    virtual ~BaseCard() = default;

    // 参数：牌名，构造函数
    static std::map<std::string, std::function<BaseCard*(int, int)>>& getRegisteredObjectByName() {
        static std::map<std::string, std::function<BaseCard*(int, int)>> registered_object_by_name;
        return registered_object_by_name;
    }

    // 参数：门派或副职或机缘(SoVJ)、境界(Realm)、id(由GetCountForSoVJRealm计算)，构造函数
    static std::map<std::tuple<std::string, int, int>, std::function<BaseCard*(int, int)>>& getRegisteredObjectBySoVJRealmId() {
        static std::map<std::tuple<std::string, int, int>, std::function<BaseCard*(int, int)>> registered_object_by_sovj_realm_id;
        return registered_object_by_sovj_realm_id;
    }

    // 可以通过门派或副职或机缘(SoVJ)、境界(Realm)获取已注册数量
    static int GetCountForSoVJRealm(const std::string& sovj, int realm) {
        auto& registered_objects = getRegisteredObjectBySoVJRealmId();
        int count = 0;
        for (const auto& obj : registered_objects) {
            if (std::get<0>(obj.first) == sovj && std::get<1>(obj.first) == realm) {
                count++;
            }
        }
        return count;
    }

    // 注册牌名, 使得可以通过名字创建牌实例
    static bool registerCard(const std::string& name, std::function<BaseCard*(int, int)> constructor) {
        getRegisteredObjectByName()[name] = constructor;
        return true;
    }

    // registerCard的重载
    // 注册门派或副职或机缘(SoVJ)、境界(Realm)的牌, 并调用registerCard
    static bool registerCard(const std::string& sovj, int realm, const std::string& name, std::function<BaseCard*(int, int)> constructor) {
        int count = GetCountForSoVJRealm(sovj, realm);
        getRegisteredObjectBySoVJRealmId()[std::make_tuple(sovj, realm, count)] = constructor;
        getRegisteredObjectByName()[name] = constructor;
        return true;
    }

    // 创建牌实例, 参数：牌名、等级、位置
    static BaseCard* createInstance(const std::string& name, int level, int position) {
        auto it = getRegisteredObjectByName().find(name);
        if (it != getRegisteredObjectByName().end()) {
            return it->second(level, position);
        }
        throw std::runtime_error("Card not found: " + name);
        return nullptr;
    }

    // 创建牌实例, 参数：门派或副职或机缘(SoVJ)、境界(Realm)、id(由GetCountForSoVJRealm计算)、等级、位置
    static BaseCard* createInstanceBySoVJRealmId(const std::string& sovj, int realm, int id, int level, int position) {
        auto it = getRegisteredObjectBySoVJRealmId().find(std::make_tuple(sovj, realm, id));
        if (it != getRegisteredObjectBySoVJRealmId().end()) {
            return it->second(level, position);
        }
        throw std::runtime_error("Card not found: " + sovj + " " + std::to_string(realm) + " " + std::to_string(id));
        return nullptr;
    }

    // 显示计数矩阵表格
    static void DisplayCountMatrixGrid();

    //虚函数，执行牌的效果，并返回执行状态值
    virtual int Effect(Status* my_status, Status* enemy_status){
        (void)my_status;
        (void)enemy_status;
        return 0;
    }
    //修改后的执行牌的灵气消耗，通过is_ling_qi_cost_modifiable启用
    virtual int LingQiCostModify(Status* my_status, Status* enemy_status){
        (void)my_status;
        (void)enemy_status;
        return ling_qi_cost;
    }
    //修改后的执行牌的血量消耗，通过is_health_cost_modifiable启用
    virtual int HealthCostModify(Status* my_status, Status* enemy_status){
        (void)my_status;
        (void)enemy_status;
        return health_cost;
    }
    // 前置于任务队列效果，必须is_before_task_queue_effect为true
    virtual int BeforeTaskQueueEffect(Status* my_status, Status* enemy_status){
        (void)my_status;
        (void)enemy_status;
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

    static const std::string name;
    
    std::string sovj; //门派或副职SoVJ
    int realm; //境界
    std::string card_name; //牌名
    int level; //牌等级
    bool is_level_modifiable; // 等级是否可修改
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



