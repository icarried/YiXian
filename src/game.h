#ifndef GAME_H
#define GAME_H

#include <yaml-cpp/yaml.h>
#include <filesystem>
#include "battle.h"
#include "./roles/roles.h"
#include "./destinys/base_destiny.h"

/*
在InitMyInfo()和InitEnemyInfo()中初始化己方和敌方的信息，包括角色、仙命、状态和卡组
*/
class Game {
public:
    Game() {
        is_sync = false;
        is_game_ready = false;
        battle_round = 10;

        battle = nullptr;
        sor_my_deck = new Deck();
        sor_enemy_deck = new Deck();

        // 初始化状态，传入对应deck指针（方便检索卡组的效果）
        sor_my_status = new Status(sor_my_deck);
        sor_enemy_status = new Status(sor_enemy_deck);
        sor_my_status->style = "\033[34m";
        sor_enemy_status->style = "\033[31m";

        // 初始化角色
        my_role = new RoleDxXiaobu(sor_my_status, sor_enemy_status);
        enemy_role = new RoleDxXiaobu(sor_enemy_status, sor_my_status);

        // 加载信息的yaml文件路径
        std::string my_info_yaml_path = "./yaml/my_info.yaml";
        std::string enemy_info_yaml_path = "./yaml/enemy_info.yaml";
        std::string battle_info_yaml_path = "./yaml/battle_info.yaml";
        // 输出当前路径
        // std::cout << "当前路径：" << std::filesystem::current_path() << std::endl;
        //判断文件是否存在
        if (!std::filesystem::exists(my_info_yaml_path)) {
            std::cout << "文件不存在：" << my_info_yaml_path << std::endl;
            return;
        }
        if (!std::filesystem::exists(enemy_info_yaml_path)) {
            std::cout << "文件不存在：" << enemy_info_yaml_path << std::endl;
            return;
        }
        if (!std::filesystem::exists(battle_info_yaml_path)) {
            std::cout << "文件不存在：" << battle_info_yaml_path << std::endl;
            return;
        }

        // 初始化角色、状态、卡组
        InitPlayerInfo(my_info_yaml_path, my_role, sor_my_deck, sor_my_status, sor_enemy_status);
        InitPlayerInfo(enemy_info_yaml_path, enemy_role, sor_enemy_deck, sor_enemy_status, sor_my_status);
        // 初始化战斗信息
        InitBattleInfo(battle_info_yaml_path);

        // 准备好开始战斗
        is_game_ready = true;
    }
    ~Game() {
        if (battle != nullptr) {
            delete battle;
        }
        delete sor_my_status;
        delete sor_enemy_status;
        delete sor_my_deck;
        delete sor_enemy_deck;
        delete my_role;
        delete enemy_role;
    }

    // 初始化玩家信息
    void InitPlayerInfo(const std::string& info_yaml_path, BaseRole*& role, Deck* deck, Status* status, Status* another_status) {
        // 初始化角色
        YAML::Node config = YAML::LoadFile(info_yaml_path);
        
        YAML::Node role_node = config["role"];
        delete role;
        role = BaseRole::createInstance(role_node["name"].as<std::string>(), status, another_status);
        role->realm = StrToRealm(role_node["realm"].as<std::string>());
        // std::cout << "Role name: " << role->name << std::endl;
        // 初始化仙命
        YAML::Node destiny_node = config["destinys"];
        int realm_index = REALM_LQQ;
        for (auto it = destiny_node.begin(); it != destiny_node.end(); ++it, ++realm_index) {
            std::string destiny_name = (*it)["name"].as<std::string>();
            BaseDestiny* destiny = BaseDestiny::createInstance(realm_index, destiny_name, role);
            role->PickDestiny(destiny);
            // std::cout << "Destiny name: " << destiny_name << std::endl;
        }
        // 初始化状态
        YAML::Node status_node = config["status"];
        if (status_node["health"]) {
            status->health->setValue(status_node["health"].as<int>());
        }
        if (status_node["health_max"]) {
            status->health_max->setValue(status_node["health_max"].as<int>());
        }
        if (status_node["ling_qi"]) {
            status->ling_qi->setValue(status_node["ling_qi"].as<int>());
        }
        if (status_node["xiu_wei"]) {
            status->xiu_wei->setValue(status_node["xiu_wei"].as<int>());
        }
        if (status_node["ti_po"]) {
            status->ti_po->setValue(status_node["ti_po"].as<int>());
        }
        if (status_node["ti_po_max"]) {
            status->ti_po_max->setValue(status_node["ti_po_max"].as<int>());
        }
        // 初始化卡组
        YAML::Node cards_node = config["cards"];
        int index = 0;
        for (auto it = cards_node.begin(); it != cards_node.end(); ++it, ++index) {
            std::string card_name = (*it)["name"].as<std::string>();
            int card_level = (*it)["level"].as<int>();
            BaseCard* card = BaseCard::createInstance(card_name, card_level, index);
            delete deck->cards[index];
            deck->cards[index] = card;
            // std::cout << "Card name: " << card_name << ", level: " << card_level << std::endl;
        }
    }

    void InitBattleInfo(const std::string& info_yaml_path) {
        // 初始化战斗信息
        YAML::Node config = YAML::LoadFile(info_yaml_path);
        battle_round = config["battle_round"].as<int>();
        battle_seed = config["battle_seed"].as<int>();
    }

    void BattleStart() {
        // 从源状态复制当前状态和卡组
        Deck *battle_my_deck = sor_my_deck->Clone();
        Deck *battle_enemy_deck = sor_enemy_deck->Clone();
        Status *battle_my_status = sor_my_status->Clone(battle_my_deck);
        Status *battle_enemy_status = sor_enemy_status->Clone(battle_enemy_deck);

        // 更新角色战斗状态指针
        my_role->battle_my_status = battle_my_status;
        enemy_role->battle_my_status = battle_enemy_status;

        // 体力同步到体力上限
        battle_my_status->health->setValue(battle_my_status->health_max->getValue());
        battle_enemy_status->health->setValue(battle_enemy_status->health_max->getValue());
        // 从体魄获得体力上限
        battle_my_status->health_max->setValue(battle_my_status->health_max->getValue() + battle_my_status->ti_po->getValue());
        battle_enemy_status->health_max->setValue(battle_enemy_status->health_max->getValue() + battle_enemy_status->ti_po->getValue());

        // 创建战斗
        if (battle != nullptr) {
            delete battle;
        }
        battle = new Battle(battle_my_deck, battle_enemy_deck, battle_my_status, battle_enemy_status, battle_round, battle_seed);

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
        // std::cout << "我方手牌" << std::endl;
        // battle->decks[0]->ShowHand();
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
        // std::cout << "敌方手牌" << std::endl;
        // battle->decks[1]->ShowHand();
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
            if (battle_my_status->ti_po->getValue() > sor_my_status->ti_po_max->getValue()) {
                sor_my_status->ti_po->setValue(battle_my_status->ti_po_max->getValue());
            } else {
                sor_my_status->ti_po->setValue(battle_my_status->ti_po->getValue());
            }
        }

        // 删除战斗
        delete battle;
        // 删除战斗使用的状态和卡组
        delete battle_my_status;
        delete battle_enemy_status;
        delete battle_my_deck;
        delete battle_enemy_deck;
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
    int battle_seed;
    
    // 是否在战斗后同步一些需要同步的状态，这在需要反复进行同一场战斗时需要设置为false
    bool is_sync;

    // 是否准备好开始战斗
    bool is_game_ready;
};




#endif // GAME_H