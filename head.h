#ifndef HEAD_H
#define HEAD_H
// 用于前置声明

#define DECK_END_INDEX 8 // 卡组结束索引


// 牌特殊属性是指对牌的结算有影响的属性
#define CARD_SP_ATTR_SUI_FANG 0 //碎防
#define CARD_SP_ATTR_WU_SHI_FANG_YU 1 //无视防
#define CARD_SP_ATTR_DUO_GONG 2 //多攻
#define CARD_SP_ATTR_SHUANG_BEI_QI_SHI 3 //双倍气势
#define CARD_SP_ATTR_END_INDEX 4 //牌特殊属性结束索引，通过牌的效果传入Attack进行结算

#endif // HEAD_H