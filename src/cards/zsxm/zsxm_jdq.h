#ifndef ZSXM_JDQ_H
#define ZSXM_JDQ_H
#include "../base_card.h"

// 专属仙命_金丹期

class Card_zsxm_jdq_fengmo : public BaseCard {
public:
    Card_zsxm_jdq_fengmo(int level, int position);
    Card_zsxm_jdq_fengmo(const Card_zsxm_jdq_fengmo& other);
    Card_zsxm_jdq_fengmo* Clone() const override;
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};

#endif // ZSXM_JDQ_H