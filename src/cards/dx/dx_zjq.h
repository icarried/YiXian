#ifndef DX_ZJQ_H
#define DX_ZJQ_H
#include "../base_card.h"

// 锻玄宗_筑基期


class Card_dx_zjq_haoranzhengqi : public BaseCard {
public:
    Card_dx_zjq_haoranzhengqi(int level, int position);
    Card_dx_zjq_haoranzhengqi* Clone() const override;
    Card_dx_zjq_haoranzhengqi(const Card_dx_zjq_haoranzhengqi& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_zjq_qichendantian : public BaseCard {
public:
    Card_dx_zjq_qichendantian(int level, int position);
    Card_dx_zjq_qichendantian* Clone() const override;
    Card_dx_zjq_qichendantian(const Card_dx_zjq_qichendantian& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_zjq_shidalichen : public BaseCard {
public:
    Card_dx_zjq_shidalichen(int level, int position);
    Card_dx_zjq_shidalichen* Clone() const override;
    Card_dx_zjq_shidalichen(const Card_dx_zjq_shidalichen& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_zjq_kuiranbudong : public BaseCard {
public:
    Card_dx_zjq_kuiranbudong(int level, int position);
    Card_dx_zjq_kuiranbudong* Clone() const override;
    Card_dx_zjq_kuiranbudong(const Card_dx_zjq_kuiranbudong& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_zjq_yeguixiao : public BaseCard {
public:
    Card_dx_zjq_yeguixiao(int level, int position);
    Card_dx_zjq_yeguixiao* Clone() const override;
    Card_dx_zjq_yeguixiao(const Card_dx_zjq_yeguixiao& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_zjq_fengmingzhua : public BaseCard {
public:
    Card_dx_zjq_fengmingzhua(int level, int position);
    Card_dx_zjq_fengmingzhua* Clone() const override;
    Card_dx_zjq_fengmingzhua(const Card_dx_zjq_fengmingzhua& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_zjq_tanmazhang : public BaseCard {
public:
    Card_dx_zjq_tanmazhang(int level, int position);
    Card_dx_zjq_tanmazhang* Clone() const override;
    Card_dx_zjq_tanmazhang(const Card_dx_zjq_tanmazhang& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_zjq_duanjin : public BaseCard {
public:
    Card_dx_zjq_duanjin(int level, int position);
    Card_dx_zjq_duanjin* Clone() const override;
    Card_dx_zjq_duanjin(const Card_dx_zjq_duanjin& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_zjq_bengquan_han : public BaseCard {
public:
    Card_dx_zjq_bengquan_han(int level, int position);
    Card_dx_zjq_bengquan_han* Clone() const override;
    Card_dx_zjq_bengquan_han(const Card_dx_zjq_bengquan_han& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};

class Card_dx_zjq_bengquan_can : public BaseCard {
public:
    Card_dx_zjq_bengquan_can(int level, int position);
    Card_dx_zjq_bengquan_can(const Card_dx_zjq_bengquan_can& other);
    Card_dx_zjq_bengquan_can* Clone() const override;
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_zjq_bengquan_tu : public BaseCard {
public:
    Card_dx_zjq_bengquan_tu(int level, int position);
    Card_dx_zjq_bengquan_tu(const Card_dx_zjq_bengquan_tu& other);
    Card_dx_zjq_bengquan_tu* Clone() const override;
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};



#endif // DX_ZJQ_H