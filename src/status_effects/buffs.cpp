#include "buffs.h"
#include "../status.h"

BuffJiaGong::BuffJiaGong(Status* linking_status, int val) : replace_Buff(linking_status, val) {
    name = "加攻";
    id = BUFF_JIA_GONG;
}

BuffJianYi::BuffJianYi(Status* linking_status, int val) : replace_Buff(linking_status, val) {
    name = "剑意";
    id = BUFF_JIAN_YI;
}

BuffFengRui::BuffFengRui(Status* linking_status, int val) : replace_Buff(linking_status, val) {
    name = "锋锐";
    id = BUFF_FENG_RUI;
}

BuffXingLi::BuffXingLi(Status* linking_status, int val) : replace_Buff(linking_status, val) {
    name = "星力";
    id = BUFF_XING_LI;
}

BuffQiShi::BuffQiShi(Status* linking_status, int val) : replace_Buff(linking_status, val) {
    name = "气势";
    id = BUFF_QI_SHI;
}

void BuffQiShi::add(int val) {
    // 气势超过上限部分转为防
    if (linked_status->replace_buffs[BUFF_QI_SHI]->getValue() + val > linked_status->replace_buffs[BUFF_QI_SHI_MAX]->getValue()) {
        int exceed_value = linked_status->replace_buffs[BUFF_QI_SHI]->getValue() + val - linked_status->replace_buffs[BUFF_QI_SHI_MAX]->getValue();
        val -= exceed_value;
        linked_status->defense->add(exceed_value);
        replace_Buff::add(val);
        if (exceed_value > 0) {
            std::cout << "，超出部分转为" << exceed_value << "点防";
        }
    }
}

BuffQiShiMax::BuffQiShiMax(Status* linking_status, int val) : replace_Buff(linking_status, val) {
    name = "气势上限";
    id = BUFF_QI_SHI_MAX;
}

BuffQianDun::BuffQianDun(Status* linking_status, int val) : replace_Buff(linking_status, val) {
    name = "潜遁";
    id = BUFF_QIAN_DUN;
}

BuffTieGu::BuffTieGu(Status* linking_status, int val) : replace_Buff(linking_status, val) {
    name = "铁骨";
    id = BUFF_TIE_GU;
}

BuffBiXie::BuffBiXie(Status* linking_status, int val) : replace_Buff(linking_status, val) {
    name = "辟邪";
    id = BUFF_BI_XIE;
}

BuffShenFa::BuffShenFa(Status* linking_status, int val) : replace_Buff(linking_status, val) {
    name = "身法";
    id = BUFF_SHEN_FA;
}

BuffHuTi::BuffHuTi(Status* linking_status, int val) : replace_Buff(linking_status, val) {
    name = "护体";
    id = BUFF_HU_TI;
}

BuffGongJiWuShiFangYu::BuffGongJiWuShiFangYu(Status* linking_status, int val) : replace_Buff(linking_status, val) {
    name = "攻击无视防御";
    id = BUFF_GONG_JI_WU_SHI_FANG_YU;
}

BuffSkipCard::BuffSkipCard(Status* linking_status, int val) : replace_Buff(linking_status, val) {
    name = "跳过牌";
    id = SKIP_CARD;
}

BuffWuFaXingDong::BuffWuFaXingDong(Status* linking_status, int val) : replace_Buff(linking_status, val) {
    name = "无法行动";
    id = WU_FA_XING_DONG;
}

BuffDuanGuTimes::BuffDuanGuTimes(Status* linking_status, int val) : replace_Buff(linking_status, val) {
    name = "锻骨剩余次数";
    id = DUANGU_TIMES;
}

BuffQiRuoXuanHeTimes::BuffQiRuoXuanHeTimes(Status* linking_status, int val) : replace_Buff(linking_status, val) {
    name = "气若悬河剩余次数";
    id = QIRUOXUANHE_TIMES;
}

replace_Buff* buff_create(int id, Status* linking_status, int val) {
    switch (id) {
        case BUFF_JIA_GONG:
            return new BuffJiaGong(linking_status, val);
        case BUFF_JIAN_YI:
            return new BuffJianYi(linking_status, val);
        case BUFF_FENG_RUI:
            return new BuffFengRui(linking_status, val);
        case BUFF_XING_LI:
            return new BuffXingLi(linking_status, val);
        case BUFF_QI_SHI:
            return new BuffQiShi(linking_status, val);
        case BUFF_QI_SHI_MAX:
            return new BuffQiShiMax(linking_status, val);
        case BUFF_QIAN_DUN:
            return new BuffQianDun(linking_status, val);
        case BUFF_TIE_GU:
            return new BuffTieGu(linking_status, val);
        case BUFF_BI_XIE:
            return new BuffBiXie(linking_status, val);
        case BUFF_SHEN_FA:
            return new BuffShenFa(linking_status, val);
        case BUFF_HU_TI:
            return new BuffHuTi(linking_status, val);
        case BUFF_GONG_JI_WU_SHI_FANG_YU:
            return new BuffGongJiWuShiFangYu(linking_status, val);
        case SKIP_CARD:
            return new BuffSkipCard(linking_status, val);
        case WU_FA_XING_DONG:
            return new BuffWuFaXingDong(linking_status, val);
        case DUANGU_TIMES:
            return new BuffDuanGuTimes(linking_status, val);
        case QIRUOXUANHE_TIMES:
            return new BuffQiRuoXuanHeTimes(linking_status, val);
        default:
            return nullptr;
    }
}
