#ifndef GAME_H
#define GAME_H

#include "battle.h"
#include "./roles/roles.h"


class Game {
public:
    Game() {
        battle_round = 10;
        sor_my_deck = new Deck();
        sor_enemy_deck = new Deck();

        // 初始化状态，传入对应deck指针（方便检索卡组的效果）
        sor_my_status = new Status(sor_my_deck);
        sor_enemy_status = new Status(sor_enemy_deck);

        // 初始化角色，目前初始化为小布
        my_role = new RoleDxXiaobu(sor_my_status, sor_enemy_status);
        enemy_role = new RoleDxXiaobu(sor_enemy_status, sor_my_status);

        // 初始化卡组
        InitMyDeck();
        InitEnemyDeck();

        // 选取仙命
        my_role->PickDestiny(new RoleDxXiaobu::ExclusiveDestinyHSQ(my_role));
        enemy_role->PickDestiny(new RoleDxXiaobu::ExclusiveDestinyHSQ(enemy_role));

        // 创建战斗。！！！正常情况下应传入从源状态复制的当前状态，避免战斗造成的状态改变影响源状态，这里为了简化直接传入源状态
        battle = new Battle(sor_my_deck, sor_enemy_deck, sor_my_status, sor_enemy_status, battle_round);
    }
    ~Game() {
        delete battle;

        delete sor_my_status;
        delete sor_enemy_status;
        delete sor_my_deck;
        delete sor_enemy_deck;
    }
    void BattleStart() {
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
    }

    // 初始化卡组
    void InitMyDeck() {
        delete sor_my_deck->cards[0];
        sor_my_deck->cards[0] = new Card_dx_hsq_xiuluohou(1, 0);

        delete sor_my_deck->cards[1];
        sor_my_deck->cards[1] = new Card_dx_lqq_luochapu(1, 1);

        delete sor_my_deck->cards[2];
        sor_my_deck->cards[2] = new Card_dx_lqq_luochapu(1, 2);

        delete sor_my_deck->cards[3];
        sor_my_deck->cards[3] = new Card_dx_hsq_xuanxinzhanpo(1, 3);
    }

    void InitEnemyDeck() {
        delete sor_enemy_deck->cards[0];
        sor_enemy_deck->cards[0] = new Card_dx_hsq_xiuluohou(1, 0);

        delete sor_enemy_deck->cards[1];
        sor_enemy_deck->cards[1] = new Card_dx_lqq_luochapu(1, 1);

        delete sor_enemy_deck->cards[2];
        sor_enemy_deck->cards[2] = new Card_dx_lqq_luochapu(1, 2);

        delete sor_enemy_deck->cards[3];
        sor_enemy_deck->cards[3] = new Card_dx_hsq_xuanxinzhanpo(1, 3);
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
};




#endif // GAME_H