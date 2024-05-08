#ifndef ZSXM_HSQ_H
#define ZSXM_HSQ_H
#include "../base_card.h"

// 专属仙命_化神期

class Card_zsxm_hsq_mingyuechanguang : public BaseCard {
public:
    Card_zsxm_hsq_mingyuechanguang(int level, int position);
    Card_zsxm_hsq_mingyuechanguang(const Card_zsxm_hsq_mingyuechanguang& other);
    Card_zsxm_hsq_mingyuechanguang* Clone() const override;
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};

#endif // ZSXM_HSQ_H