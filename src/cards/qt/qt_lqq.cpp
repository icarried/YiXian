#include "qt_lqq.h"

// 定义文件内所有牌的变量
#define FILE_CARDS_SOVJ "其它"
#define FILE_CARDS_REALM REALM_LQQ
// 该文件中的牌不注册门派副职和境界

const std::string Card_qt_lqq_pttonggongji::name = "普通攻击";
bool Card_qt_lqq_pttonggongji::registered = BaseCard::registerCard(Card_qt_lqq_pttonggongji::name, Card_qt_lqq_pttonggongji::create);
/*
普通攻击，3/6/9攻
*/
Card_qt_lqq_pttonggongji::Card_qt_lqq_pttonggongji(int level, int position) : BaseCard(level, position) {
    sovj = FILE_CARDS_SOVJ;
    realm = FILE_CARDS_REALM;
    card_name = "普通攻击";
    is_attacking = true;
    attack = level * 3;
    card_tag[PU_TONG_GONG_JI_CARD] = true;
}

Card_qt_lqq_pttonggongji* Card_qt_lqq_pttonggongji::Clone() const {
    return new Card_qt_lqq_pttonggongji(*this);
}

Card_qt_lqq_pttonggongji::Card_qt_lqq_pttonggongji(const Card_qt_lqq_pttonggongji& other) : BaseCard(other) {}

int Card_qt_lqq_pttonggongji::Effect(Status* my_status, Status* enemy_status) {
    Attack(my_status, enemy_status, attack, card_sp_attr);
    return 0;
}

BaseCard* Card_qt_lqq_pttonggongji::create(int level, int position) {
    return new Card_qt_lqq_pttonggongji(level, position);
}


const std::string Card_qt_lqq_zouhuorumo::name = "走火入魔";
bool Card_qt_lqq_zouhuorumo::registered = BaseCard::registerCard(Card_qt_lqq_zouhuorumo::name, Card_qt_lqq_zouhuorumo::create);
/*
走火入魔：无任何效果
*/
Card_qt_lqq_zouhuorumo::Card_qt_lqq_zouhuorumo(int level, int position) : BaseCard(level, position) {
    sovj = FILE_CARDS_SOVJ;
    realm = FILE_CARDS_REALM;
    card_name = "走火入魔";
    is_attacking = false;
    card_tag[BU_KE_YONG_CARD] = true;
}

Card_qt_lqq_zouhuorumo* Card_qt_lqq_zouhuorumo::Clone() const {
    return new Card_qt_lqq_zouhuorumo(*this);
}

Card_qt_lqq_zouhuorumo::Card_qt_lqq_zouhuorumo(const Card_qt_lqq_zouhuorumo& other) : BaseCard(other) {}

int Card_qt_lqq_zouhuorumo::Effect(Status* my_status, Status* enemy_status) {
    return 0;
}

BaseCard* Card_qt_lqq_zouhuorumo::create(int level, int position) {
    return new Card_qt_lqq_zouhuorumo(level, position);
}