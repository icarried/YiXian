#ifndef DX_YYQ_H
#define DX_YYQ_H
#include "../base_card.h"

// 锻玄宗_元婴期



class Card_dx_yyq_xuanshouduohun : public BaseCard {
public:
    Card_dx_yyq_xuanshouduohun(int level, int position);
    Card_dx_yyq_xuanshouduohun* Clone() const override;
    Card_dx_yyq_xuanshouduohun(const Card_dx_yyq_xuanshouduohun& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_yyq_pangbozhishi : public BaseCard {
public:
    Card_dx_yyq_pangbozhishi(int level, int position);
    Card_dx_yyq_pangbozhishi* Clone() const override;
    Card_dx_yyq_pangbozhishi(const Card_dx_yyq_pangbozhishi& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_yyq_chongxiaopolang : public BaseCard {
public:
    Card_dx_yyq_chongxiaopolang(int level, int position);
    Card_dx_yyq_chongxiaopolang* Clone() const override;
    Card_dx_yyq_chongxiaopolang(const Card_dx_yyq_chongxiaopolang& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_yyq_mingyingshenfa : public BaseCard {
public:
    Card_dx_yyq_mingyingshenfa(int level, int position);
    Card_dx_yyq_mingyingshenfa* Clone() const override;
    Card_dx_yyq_mingyingshenfa(const Card_dx_yyq_mingyingshenfa& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_yyq_lingxuanmizongbu : public BaseCard {
public:
    Card_dx_yyq_lingxuanmizongbu(int level, int position);
    Card_dx_yyq_lingxuanmizongbu* Clone() const override;
    Card_dx_yyq_lingxuanmizongbu(const Card_dx_yyq_lingxuanmizongbu& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_yyq_hebu : public BaseCard {
public:
    Card_dx_yyq_hebu(int level, int position);
    Card_dx_yyq_hebu* Clone() const override;
    Card_dx_yyq_hebu(const Card_dx_yyq_hebu& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_yyq_duansui : public BaseCard {
public:
    Card_dx_yyq_duansui(int level, int position);
    Card_dx_yyq_duansui* Clone() const override;
    Card_dx_yyq_duansui(const Card_dx_yyq_duansui& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_yyq_bengquan_cunjing : public BaseCard {
public:
    Card_dx_yyq_bengquan_cunjing(int level, int position);
    Card_dx_yyq_bengquan_cunjing* Clone() const override;
    Card_dx_yyq_bengquan_cunjing(const Card_dx_yyq_bengquan_cunjing& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_yyq_bengquan_lianbeng : public BaseCard {
public:
    std::vector<EffectTaskQueue::Task> recordedTasks;
    Card_dx_yyq_bengquan_lianbeng(int level, int position);
    Card_dx_yyq_bengquan_lianbeng* Clone() const override;
    Card_dx_yyq_bengquan_lianbeng(const Card_dx_yyq_bengquan_lianbeng& other);
    int BeforeTaskQueueEffect(Status* my_status, Status* enemy_status);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


class Card_dx_yyq_bengmiexinfa : public BaseCard {
public:
    Card_dx_yyq_bengmiexinfa(int level, int position);
    Card_dx_yyq_bengmiexinfa* Clone() const override;
    Card_dx_yyq_bengmiexinfa(const Card_dx_yyq_bengmiexinfa& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};


#endif // DX_YYQ_H