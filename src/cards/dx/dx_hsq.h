#ifndef DX_HSQ_H
#define DX_HSQ_H
#include "../base_card.h"

// 锻玄宗_化神期

class Card_dx_hsq_tiandihaodang : public BaseCard {
public:
    Card_dx_hsq_tiandihaodang(int level, int position);
    Card_dx_hsq_tiandihaodang* Clone() const override;
    Card_dx_hsq_tiandihaodang(const Card_dx_hsq_tiandihaodang& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};





class Card_dx_hsq_xiuluohou : public BaseCard {
public:
    Card_dx_hsq_xiuluohou(int level, int position);
    Card_dx_hsq_xiuluohou* Clone() const override;
    Card_dx_hsq_xiuluohou(const Card_dx_hsq_xiuluohou& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};





class Card_dx_hsq_weizhensifang : public BaseCard {
public:
    Card_dx_hsq_weizhensifang(int level, int position);
    Card_dx_hsq_weizhensifang* Clone() const override;
    Card_dx_hsq_weizhensifang(const Card_dx_hsq_weizhensifang& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};





class Card_dx_hsq_xuanxinzhanpo : public BaseCard {
public:
    Card_dx_hsq_xuanxinzhanpo(int level, int position);
    Card_dx_hsq_xuanxinzhanpo* Clone() const override;
    Card_dx_hsq_xuanxinzhanpo(const Card_dx_hsq_xuanxinzhanpo& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};





class Card_dx_hsq_baishapojingzhang : public BaseCard {
public:
    Card_dx_hsq_baishapojingzhang(int level, int position);
    Card_dx_hsq_baishapojingzhang* Clone() const override;
    Card_dx_hsq_baishapojingzhang(const Card_dx_hsq_baishapojingzhang& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};





class Card_dx_hsq_duanshenkaihai : public BaseCard {
public:
    Card_dx_hsq_duanshenkaihai(int level, int position);
    Card_dx_hsq_duanshenkaihai* Clone() const override;
    Card_dx_hsq_duanshenkaihai(const Card_dx_hsq_duanshenkaihai& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};





class Card_dx_hsq_bengquan_jingchu : public BaseCard {
public:
    Card_dx_hsq_bengquan_jingchu(int level, int position);
    Card_dx_hsq_bengquan_jingchu* Clone() const override;
    Card_dx_hsq_bengquan_jingchu(const Card_dx_hsq_bengquan_jingchu& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};





class Card_dx_hsq_bengquan_shanji : public BaseCard {
public:
    Card_dx_hsq_bengquan_shanji(int level, int position);
    Card_dx_hsq_bengquan_shanji* Clone() const override;
    Card_dx_hsq_bengquan_shanji(const Card_dx_hsq_bengquan_shanji& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};





#endif // DX_HSQ_H