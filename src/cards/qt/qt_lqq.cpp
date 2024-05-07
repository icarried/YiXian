#include "qt_lqq.h"

const std::string Card_qt_lqq_pttonggongji::name = "普通攻击";
bool Card_qt_lqq_pttonggongji::registered = BaseCard::registerCard(Card_qt_lqq_pttonggongji::name, Card_qt_lqq_pttonggongji::create);
/*
普通攻击，3/6/9攻
*/
Card_qt_lqq_pttonggongji::Card_qt_lqq_pttonggongji(int level, int position) : BaseCard(level, position) {
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