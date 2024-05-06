#ifndef DX_LQQ_H
#define DX_LQQ_H
#include "../base_card.h"

// 锻玄宗_炼气期


class Card_dx_lqq_xueqifanggang : public BaseCard {
public:
    Card_dx_lqq_xueqifanggang(int level, int position);
    Card_dx_lqq_xueqifanggang* Clone() const override;
    Card_dx_lqq_xueqifanggang(const Card_dx_lqq_xueqifanggang& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_lqq_qianjinzhui : public BaseCard {
public:
    Card_dx_lqq_qianjinzhui(int level, int position);
    Card_dx_lqq_qianjinzhui* Clone() const override;
    Card_dx_lqq_qianjinzhui(const Card_dx_lqq_qianjinzhui& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_lqq_pokongzhua : public BaseCard {
public:
    Card_dx_lqq_pokongzhua(int level, int position);
    Card_dx_lqq_pokongzhua* Clone() const override;
    Card_dx_lqq_pokongzhua(const Card_dx_lqq_pokongzhua& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_lqq_zhaoqipengbo : public BaseCard {
public:
    Card_dx_lqq_zhaoqipengbo(int level, int position);
    Card_dx_lqq_zhaoqipengbo* Clone() const override;
    Card_dx_lqq_zhaoqipengbo(const Card_dx_lqq_zhaoqipengbo& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_lqq_qishi : public BaseCard {
public:
    Card_dx_lqq_qishi(int level, int position);
    Card_dx_lqq_qishi* Clone() const override;
    Card_dx_lqq_qishi(const Card_dx_lqq_qishi& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_lqq_luochapu : public BaseCard {
public:
    Card_dx_lqq_luochapu(int level, int position);
    Card_dx_lqq_luochapu(const Card_dx_lqq_luochapu& other);
    Card_dx_lqq_luochapu* Clone() const override;
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};

/*
灵气+1，体魄+2，生命+1/4/7
*/
class Card_dx_lqq_baoqifa : public BaseCard {
public:
    Card_dx_lqq_baoqifa(int level, int position);
    Card_dx_lqq_baoqifa(const Card_dx_lqq_baoqifa& other);
    Card_dx_lqq_baoqifa* Clone() const override;
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_lqq_pishanzhang : public BaseCard {
public:
    Card_dx_lqq_pishanzhang(int level, int position);
    Card_dx_lqq_pishanzhang(const Card_dx_lqq_pishanzhang& other);
    Card_dx_lqq_pishanzhang* Clone() const override;
    int Effect(Status* my_status, Status* enemy_status) override;
    int HealthCostModify(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_lqq_duanquan : public BaseCard {
public:
    Card_dx_lqq_duanquan(int level, int position);
    Card_dx_lqq_duanquan(const Card_dx_lqq_duanquan& other);
    Card_dx_lqq_duanquan* Clone() const override;
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_lqq_bengquan_tan : public BaseCard {
public:
    Card_dx_lqq_bengquan_tan(int level, int position);
    Card_dx_lqq_bengquan_tan(const Card_dx_lqq_bengquan_tan& other);
    Card_dx_lqq_bengquan_tan* Clone() const override;
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_lqq_bengquan_feng : public BaseCard {
public:
    Card_dx_lqq_bengquan_feng(int level, int position);
    Card_dx_lqq_bengquan_feng* Clone() const override;
    Card_dx_lqq_bengquan_feng(const Card_dx_lqq_bengquan_feng& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};

class Card_dx_lqq_bengquan_chuo : public BaseCard {
public:
    Card_dx_lqq_bengquan_chuo(int level, int position);
    Card_dx_lqq_bengquan_chuo* Clone() const override;
    Card_dx_lqq_bengquan_chuo(const Card_dx_lqq_bengquan_chuo& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};



// BaseCard* dx_lqq_create(int card_serial_number, int level, int position) {
//     switch (card_serial_number) {
//         case 1:
//             return new Card_dx_lqq_xueqifanggang(level, position);
//         case 2:
//             return new Card_dx_lqq_qianjinzhui(level, position);
//         case 3:
//             return new Card_dx_lqq_pokongzhua(level, position);
//         case 4:
//             return new Card_dx_lqq_zhaoqipengbo(level, position);
//         case 5:
//             return new Card_dx_lqq_qishi(level, position);
//         case 6:
//             return new Card_dx_lqq_luochapu(level, position);
//         case 7:
//             return new Card_dx_lqq_baoqifa(level, position);
//         case 8:
//             return new Card_dx_lqq_pishanzhang(level, position);
//         case 9:
//             return new Card_dx_lqq_duanquan(level, position);
//         case 10:
//             return new Card_dx_lqq_bengquan_tan(level, position);
//         case 11:
//             return new Card_dx_lqq_bengquan_feng(level, position);
//         case 12:
//             return new Card_dx_lqq_bengquan_chuo(level, position);
//         default:
//             throw std::invalid_argument("Invalid type");
//     }
// }

#endif // DX_LQQ_H