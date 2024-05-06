#ifndef DX_JDQ_H
#define DX_JDQ_H
#include "../base_card.h"

// 锻玄宗_金丹期


class Card_dx_jdq_shirupozhu : public BaseCard {
public:
    Card_dx_jdq_shirupozhu(int level, int position);
    Card_dx_jdq_shirupozhu* Clone() const override;
    Card_dx_jdq_shirupozhu(const Card_dx_jdq_shirupozhu& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};





class Card_dx_jdq_tapojiuxiao : public BaseCard {
public:
    Card_dx_jdq_tapojiuxiao(int level, int position);
    Card_dx_jdq_tapojiuxiao* Clone() const override;
    Card_dx_jdq_tapojiuxiao(const Card_dx_jdq_tapojiuxiao& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};





class Card_dx_jdq_qiruoxuanhe : public BaseCard {
public:
    Card_dx_jdq_qiruoxuanhe(int level, int position);
    Card_dx_jdq_qiruoxuanhe* Clone() const override;
    Card_dx_jdq_qiruoxuanhe(const Card_dx_jdq_qiruoxuanhe& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};





class Card_dx_jdq_shuangguipaimeng : public BaseCard {
public:
    Card_dx_jdq_shuangguipaimeng(int level, int position);
    Card_dx_jdq_shuangguipaimeng* Clone() const override;
    Card_dx_jdq_shuangguipaimeng(const Card_dx_jdq_shuangguipaimeng& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};





class Card_dx_jdq_ehupushi : public BaseCard {
public:
    Card_dx_jdq_ehupushi(int level, int position);
    Card_dx_jdq_ehupushi* Clone() const override;
    Card_dx_jdq_ehupushi(const Card_dx_jdq_ehupushi& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    int LingQiCostModify(Status* my_status, Status* enemy_status);
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};





class Card_dx_jdq_yingfengzhang : public BaseCard {
public:
    Card_dx_jdq_yingfengzhang(int level, int position);
    Card_dx_jdq_yingfengzhang* Clone() const override;
    Card_dx_jdq_yingfengzhang(const Card_dx_jdq_yingfengzhang& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};





class Card_dx_jdq_hezhongqianxing : public BaseCard {
public:
    Card_dx_jdq_hezhongqianxing(int level, int position);
    Card_dx_jdq_hezhongqianxing* Clone() const override;
    Card_dx_jdq_hezhongqianxing(const Card_dx_jdq_hezhongqianxing& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};





class Card_dx_jdq_duangu : public BaseCard {
public:
    Card_dx_jdq_duangu(int level, int position);
    Card_dx_jdq_duangu* Clone() const override;
    Card_dx_jdq_duangu(const Card_dx_jdq_duangu& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};





class Card_dx_jdq_bengquan_xianglong : public BaseCard {
public:
    Card_dx_jdq_bengquan_xianglong(int level, int position);
    Card_dx_jdq_bengquan_xianglong* Clone() const override;
    Card_dx_jdq_bengquan_xianglong(const Card_dx_jdq_bengquan_xianglong& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};





class Card_dx_jdq_bengquan_jiemai : public BaseCard {
public:
    Card_dx_jdq_bengquan_jiemai(int level, int position);
    Card_dx_jdq_bengquan_jiemai* Clone() const override;
    Card_dx_jdq_bengquan_jiemai(const Card_dx_jdq_bengquan_jiemai& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};





class Card_dx_jdq_bengtianbu : public BaseCard {
public:
    Card_dx_jdq_bengtianbu(int level, int position);
    Card_dx_jdq_bengtianbu* Clone() const override;
    Card_dx_jdq_bengtianbu(const Card_dx_jdq_bengtianbu& other);
    int Effect(Status* my_status, Status* enemy_status) override;
    static BaseCard* create(int level, int position);
    static const std::string name;
    static bool registered;
};



#endif // DX_JDQ_H