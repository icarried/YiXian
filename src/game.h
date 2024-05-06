#ifndef GAME_H
#define GAME_H

#include "battle.h"
#include "./roles/roles.h"

/*
在InitMyInfo()和InitEnemyInfo()中初始化己方和敌方的信息，包括角色、仙命、状态和卡组
*/
class Game {
public:
    Game() {
        is_sync = false;
        battle_round = 10;

        battle = nullptr;
        sor_my_deck = new Deck();
        sor_enemy_deck = new Deck();

        // 初始化状态，传入对应deck指针（方便检索卡组的效果）
        sor_my_status = new Status(sor_my_deck);
        sor_enemy_status = new Status(sor_enemy_deck);

        // 初始化角色
        my_role = new RoleDxXiaobu(sor_my_status, sor_enemy_status);
        enemy_role = new RoleDxXiaobu(sor_enemy_status, sor_my_status);

        // 初始化角色、状态、卡组
        InitMyInfo();
        InitEnemyInfo();
    }
    ~Game() {
        if (battle != nullptr) {
            delete battle;
        }
        delete sor_my_status;
        delete sor_enemy_status;
        delete sor_my_deck;
        delete sor_enemy_deck;
    }
    
    // 初始化己方信息
    void InitMyInfo() {
        // 更改初始化角色为小布，化神期
        delete my_role;
        my_role = new RoleDxXiaobu(sor_my_status, sor_enemy_status);
        my_role->realm = REALM_HSQ;

        // 选取仙命
        my_role->PickDestiny(new RoleDxXiaobu::ExclusiveDestinyHSQ(my_role));

        // 更改初始化状态
        sor_my_status->health_max->setValue(60);

        // 初始化卡组
        delete sor_my_deck->cards[0];
        sor_my_deck->cards[0] = BaseCard::createInstance("修罗吼", 1, 0);

        delete sor_my_deck->cards[1];
        sor_my_deck->cards[1] = BaseCard::createInstance("罗刹扑", 1, 1);

        delete sor_my_deck->cards[2];
        sor_my_deck->cards[2] = BaseCard::createInstance("罗刹扑", 1, 2);

        delete sor_my_deck->cards[3];
        sor_my_deck->cards[3] = BaseCard::createInstance("玄心斩魄", 1, 3);
    }

    // 初始化敌方信息
    void InitEnemyInfo() {
        // 更改初始化角色为小布
        delete enemy_role;
        enemy_role = new RoleDxXiaobu(sor_enemy_status, sor_my_status);
        enemy_role->realm = REALM_HSQ;

        // 选取仙命
        enemy_role->PickDestiny(new RoleDxXiaobu::ExclusiveDestinyHSQ(enemy_role));

        // 更改初始化状态
        sor_enemy_status->health_max->setValue(60);

        // 初始化卡组
        delete sor_enemy_deck->cards[0];
        sor_enemy_deck->cards[0] = new Card_dx_hsq_xiuluohou(1, 0);

        delete sor_enemy_deck->cards[1];
        sor_enemy_deck->cards[1] = new Card_dx_lqq_luochapu(1, 1);

        delete sor_enemy_deck->cards[2];
        sor_enemy_deck->cards[2] = new Card_dx_lqq_luochapu(1, 2);

        delete sor_enemy_deck->cards[3];
        sor_enemy_deck->cards[3] = new Card_dx_hsq_xuanxinzhanpo(1, 3);
    }


    void BattleStart() {
        // 从源状态复制当前状态和卡组
        Deck *my_deck = sor_my_deck->Clone();
        Deck *enemy_deck = sor_enemy_deck->Clone();
        Status *my_status = sor_my_status->Clone(my_deck);
        Status *enemy_status = sor_enemy_status->Clone(enemy_deck);

        // 体力同步到体力上限
        my_status->health->setValue(my_status->health_max->getValue());
        enemy_status->health->setValue(enemy_status->health_max->getValue());
        // 从体魄获得体力上限
        my_status->health_max->setValue(my_status->health_max->getValue() + my_status->ti_po_max->getValue());
        enemy_status->health_max->setValue(enemy_status->health_max->getValue() + enemy_status->ti_po_max->getValue());

        // 创建战斗
        if (battle != nullptr) {
            delete battle;
        }
        battle = new Battle(my_deck, enemy_deck, my_status, enemy_status, battle_round);

        std::cout << "我方角色：" << my_role->name << std::endl;
        std::cout << "我方仙命：" ;
        for (int i = REALM_START_INDEX; i < ROLE_REALM_MAX + 1; i++) {
            if (my_role->picked_destinies[i] != nullptr) {
                std::cout << "[" << my_role->picked_destinies[i]->name << "] ";
            }
        }
        std::cout << std::endl;
        std::cout << "我方卡组" << std::endl;
        battle->decks[0]->ShowDeck();
        std::cout << "敌方角色：" << enemy_role->name << std::endl;
        std::cout << "敌方仙命：" ;
        for (int i = REALM_START_INDEX; i < ROLE_REALM_MAX + 1; i++) {
            if (enemy_role->picked_destinies[i] != nullptr) {
                std::cout << "[" << enemy_role->picked_destinies[i]->name << "] ";
            }
        }
        std::cout << std::endl;
        std::cout << "敌方卡组" << std::endl;
        battle->decks[1]->ShowDeck();
        std::cout << "战斗开始…………" << std::endl;
        int result = battle->BattleStart();
        if (result > 0) {
            std::cout << "我方胜利" << std::endl;
        } else if (result < 0) {
            std::cout << "敌方胜利" << std::endl;
        } else {
            std::cout << "平局" << std::endl;
        }
        std::cout << "战斗结束…………" << std::endl;

        // 战斗后需要向源状态同步的一些状态（若不同步，下次战斗会继续使用上次的状态）
        if (is_sync) {
            // 同步体魄
            if (my_status->ti_po->getValue() > sor_my_status->ti_po_max->getValue()) {
                sor_my_status->ti_po->setValue(my_status->ti_po_max->getValue());
            } else {
                sor_my_status->ti_po->setValue(my_status->ti_po->getValue());
            }
        }

        // 删除战斗
        delete battle;
        // 删除战斗使用的状态和卡组
        delete my_status;
        delete enemy_status;
        delete my_deck;
        delete enemy_deck;
    }

    // 角色
    BaseRole *my_role;
    BaseRole *enemy_role;

    // 源状态与卡组
    Status *sor_my_status;
    Status *sor_enemy_status;

    Deck *sor_my_deck;
    Deck *sor_enemy_deck;

    // 战斗
    Battle *battle;
    int battle_round;
    
    // 是否在战斗后同步一些需要同步的状态，这在需要反复进行同一场战斗时需要设置为false
    bool is_sync;
};




#endif // GAME_H