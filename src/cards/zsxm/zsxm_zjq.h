#ifndef ZSXM_ZJQ_H
#define ZSXM_ZJQ_H
#include "../base_card.h"

// 专属仙命_筑基期

class Card_zsxm_zjq_shengqilingren : public BaseCard {
public:
    Card_zsxm_zjq_shengqilingren(int level, int position);
    Card_zsxm_zjq_shengqilingren(const Card_zsxm_zjq_shengqilingren& other);
    Card_zsxm_zjq_shengqilingren* Clone() const override;
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};

class Card_zsxm_zjq_duantibuxi : public BaseCard {
public:
    Card_zsxm_zjq_duantibuxi(int level, int position);
    Card_zsxm_zjq_duantibuxi(const Card_zsxm_zjq_duantibuxi& other);
    Card_zsxm_zjq_duantibuxi* Clone() const override;
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};

#endif // ZSXM_ZJQ_H