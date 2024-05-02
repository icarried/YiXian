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
#define DUANGU_TIMES 14 //锻骨剩余次数（非正常buff）
#define QIRUOXUANHE_TIMES 15 //气若悬河剩余次数（非正常buff）

#define BUFF_END_INDEX 16 //buff结束索引

class BuffJiaGong : public replace_Buff {
public:
    BuffJiaGong(Status* linking_status, int val);
};

class BuffJianYi : public replace_Buff {
public:
    BuffJianYi(Status* linking_status, int val);
};

class BuffFengRui : public replace_Buff {
public:
    BuffFengRui(Status* linking_status, int val);
};

class BuffXingLi : public replace_Buff {
public:
    BuffXingLi(Status* linking_status, int val);
};

class BuffQiShi : public replace_Buff {
public:
    BuffQiShi(Status* linking_status, int val);
    void add(int val) override;
};

class BuffQiShiMax : public replace_Buff {
public:
    BuffQiShiMax(Status* linking_status, int val);
};

class BuffQianDun : public replace_Buff {
public:
    BuffQianDun(Status* linking_status, int val);
};

class BuffTieGu : public replace_Buff {
public:
    BuffTieGu(Status* linking_status, int val);
};

class BuffBiXie : public replace_Buff {
public:
    BuffBiXie(Status* linking_status, int val);
};

class BuffShenFa : public replace_Buff {
public:
    BuffShenFa(Status* linking_status, int val);
};

class BuffHuTi : public replace_Buff {
public:
    BuffHuTi(Status* linking_status, int val);
};

class BuffGongJiWuShiFangYu : public replace_Buff {
public:
    BuffGongJiWuShiFangYu(Status* linking_status, int val);
};

class BuffSkipCard : public replace_Buff {
public:
    BuffSkipCard(Status* linking_status, int val);
};

class BuffWuFaXingDong : public replace_Buff {
public:
    BuffWuFaXingDong(Status* linking_status, int val);
};

class BuffDuanGuTimes : public replace_Buff {
public:
    BuffDuanGuTimes(Status* linking_status, int val);
};

class BuffQiRuoXuanHeTimes : public replace_Buff {
public:
    BuffQiRuoXuanHeTimes(Status* linking_status, int val);
};

replace_Buff* buff_create(int id, Status* linking_status, int val);

#endif // !BUFFS_H
