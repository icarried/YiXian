#ifndef ZSXM_YYQ_H
#define ZSXM_YYQ_H
#include "../base_card.h"

// 专属仙命_元婴期

class Card_zsxm_yyq_bengquan_mingye : public BaseCard {
public:
    Card_zsxm_yyq_bengquan_mingye(int level, int position);
    Card_zsxm_yyq_bengquan_mingye(const Card_zsxm_yyq_bengquan_mingye& other);
    Card_zsxm_yyq_bengquan_mingye* Clone() const override;
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};

#endif // ZSXM_YYQ_H