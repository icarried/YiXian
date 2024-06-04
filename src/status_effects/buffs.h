#ifndef BUFFS_H
#define BUFFS_H

#include "base_status_effect.h"

#define BUFF_JIA_GONG 0 //加攻
#define BUFF_JIAN_YI 1 //剑意
#define BUFF_FENG_RUI 2 //锋锐
#define BUFF_XING_LI 3 //星力
#define BUFF_QI_SHI 4 //气势
#define BUFF_QI_SHI_MAX 5 //气势上限
#define BUFF_QIAN_DUN 6 //潜遁
#define BUFF_TIE_GU 7 //铁骨
#define BUFF_BI_XIE 8 //辟邪
#define BUFF_SHEN_FA 9 //身法
#define BUFF_HU_TI 10 //护体
#define BUFF_GONG_JI_WU_SHI_FANG_YU 11 //攻击无视防御（下N次攻击无视防御）

#define SKIP_CARD 12 //跳过下N张牌
#define WU_FA_XING_DONG 13 //无法行动

#define BUFF_END_INDEX 14 //buff结束索引

class BuffJiaGong : public Buff {
public:
    BuffJiaGong(Status* linking_status, int val);
    BuffJiaGong* Clone(Status* new_status) const override;
    BuffJiaGong(const BuffJiaGong& other, Status* new_status);
};

class BuffJianYi : public Buff {
public:
    BuffJianYi(Status* linking_status, int val);
    BuffJianYi* Clone(Status* new_status) const override;
    BuffJianYi(const BuffJianYi& other, Status* new_status);
};

class BuffFengRui : public Buff {
public:
    BuffFengRui(Status* linking_status, int val);
    BuffFengRui* Clone(Status* new_status) const override;
    BuffFengRui(const BuffFengRui& other, Status* new_status);
};

class BuffXingLi : public Buff {
public:
    BuffXingLi(Status* linking_status, int val);
    BuffXingLi* Clone(Status* new_status) const override;
    BuffXingLi(const BuffXingLi& other, Status* new_status);
};

class BuffQiShi : public Buff {
public:
    BuffQiShi(Status* linking_status, int val);
    BuffQiShi* Clone(Status* new_status) const override;
    BuffQiShi(const BuffQiShi& other, Status* new_status);
    void add(int val) override;
};

class BuffQiShiMax : public Buff {
public:
    BuffQiShiMax(Status* linking_status, int val);
    BuffQiShiMax* Clone(Status* new_status) const override;
    BuffQiShiMax(const BuffQiShiMax& other, Status* new_status);
};

class BuffQianDun : public Buff {
public:
    BuffQianDun(Status* linking_status, int val);
    BuffQianDun* Clone(Status* new_status) const override;
    BuffQianDun(const BuffQianDun& other, Status* new_status);
};

class BuffTieGu : public Buff {
public:
    BuffTieGu(Status* linking_status, int val);
    BuffTieGu* Clone(Status* new_status) const override;
    BuffTieGu(const BuffTieGu& other, Status* new_status);
};

class BuffBiXie : public Buff {
public:
    BuffBiXie(Status* linking_status, int val);
    BuffBiXie* Clone(Status* new_status) const override;
    BuffBiXie(const BuffBiXie& other, Status* new_status);
};

class BuffShenFa : public Buff {
public:
    BuffShenFa(Status* linking_status, int val);
    BuffShenFa* Clone(Status* new_status) const override;
    BuffShenFa(const BuffShenFa& other, Status* new_status);
};

class BuffHuTi : public Buff {
public:
    BuffHuTi(Status* linking_status, int val);
    BuffHuTi* Clone(Status* new_status) const override;
    BuffHuTi(const BuffHuTi& other, Status* new_status);
};

class BuffGongJiWuShiFangYu : public Buff {
public:
    BuffGongJiWuShiFangYu(Status* linking_status, int val);
    BuffGongJiWuShiFangYu* Clone(Status* new_status) const override;
    BuffGongJiWuShiFangYu(const BuffGongJiWuShiFangYu& other, Status* new_status);
};

class BuffSkipCard : public Buff {
public:
    BuffSkipCard(Status* linking_status, int val);
    BuffSkipCard* Clone(Status* new_status) const override;
    BuffSkipCard(const BuffSkipCard& other, Status* new_status);
};

class BuffWuFaXingDong : public Buff {
public:
    BuffWuFaXingDong(Status* linking_status, int val);
    BuffWuFaXingDong* Clone(Status* new_status) const override;
    BuffWuFaXingDong(const BuffWuFaXingDong& other, Status* new_status);
};

Buff* buff_create(int id, Status* linking_status, int val);

#endif // !BUFFS_H
