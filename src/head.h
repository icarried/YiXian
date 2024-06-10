#ifndef HEAD_H
#define HEAD_H
// 用于前置声明

#define DECK_END_INDEX 8 // 卡组结束索引


// 牌特殊属性是指对牌的结算有影响的属性
// card_sp_attr数组的索引
#define CARD_SP_ATTR_SUI_FANG 0 //碎防
#define CARD_SP_ATTR_WU_SHI_FANG_YU 1 //无视防
#define CARD_SP_ATTR_DUO_GONG 2 //多攻
#define CARD_SP_ATTR_SHUANG_BEI_QI_SHI 3 //双倍气势
#define CARD_SP_ATTR_END_INDEX 4 //牌特殊属性结束索引，通过牌的效果传入Attack进行结算

// 境界id
#define REALM_NONE 0 //无境界
#define REALM_START_INDEX 1 //境界开始索引
#define REALM_LQQ 1 //炼气期
#define REALM_ZJQ 2 //筑基期
#define REALM_JDQ 3 //金丹期
#define REALM_YYQ 4 //元婴期
#define REALM_HSQ 5 //化神期
#define REALM_FXQ 6 //返虚期
#define REALM_QTQ 7 //其他境界
#define REALM_END_INDEX 8 //境界结束索引
#define ROLE_REALM_MAX REALM_HSQ //角色最大境界

// 门派id
#define SECT_NONE 0 //无门派
#define SECT_START_INDEX 1 //门派开始索引
#define SECT_YL 1 //云灵剑宗
#define SECT_QX 2 //七星阁
#define SECT_WX 3 //五行道盟
#define SECT_DX 4 //锻玄宗
#define SECT_END_INDEX 5 //门派结束索引

// 副职id
#define VICE_JOB_NONE 0 //无副职
#define VICE_JOB_START_INDEX 1 //副职开始索引
#define VICE_JOB_LDS 1 //炼丹师
#define VICE_JOB_FLS 2 //符箓师
#define VICE_JOB_QS 3 //琴师
#define VICE_JOB_HS 4 //画师
#define VICE_JOB_ZFS 5 //阵法师
#define VICE_JOB_LZS 6 //灵植师
#define VICE_JOB_END_INDEX 7 //副职结束索引

// card_tag数组索引
#define PU_TONG_GONG_JI_CARD 0 //普通攻击牌
#define XIAO_HAO_CARD 1 //消耗牌
#define CHI_XU_CARD 2 //持续牌
#define ZHI_HUAN_CARD 3 //置换牌 一般为不可用牌
#define LIAN_HUA_CARD 4 //炼化牌 一般为不可用牌
#define BU_KE_YONG_CARD 5 //不可用牌 不可置入牌组
#define LING_JIAN_CARD 6 //灵剑牌
#define YUN_JIAN_CARD 7 //云剑牌
#define KUANG_JIAN_CARD 8 //狂剑牌
#define BENG_QUAN_CARD 9 //崩拳牌
#define TI_PO_CARD 10 //体魄牌
#define CARD_TAG_END_INDEX 11 //牌标签结束索引

// 默认文字样式
#define DEFAULT_STYLE "\033[0m"

#include "cal.h"

#endif // HEAD_H