#ifndef QT_LQQ_H
#define QT_LQQ_H
#include "../base_card.h"

// 其他_炼气期

class Card_qt_lqq_pttonggongji : public BaseCard {
public:
    Card_qt_lqq_pttonggongji(int level, int position);
    Card_qt_lqq_pttonggongji* Clone() const override;
    Card_qt_lqq_pttonggongji(const Card_qt_lqq_pttonggongji& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};

class Card_qt_lqq_zouhuorumo : public BaseCard {
public:
    Card_qt_lqq_zouhuorumo(int level, int position);
    Card_qt_lqq_zouhuorumo* Clone() const override;
    Card_qt_lqq_zouhuorumo(const Card_qt_lqq_zouhuorumo& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


#endif // !QT_LQQ_H