#ifndef BUFF_H
#define BUFF_H
/*
# 对于伤害结算影响的buff有：
# 增加buff 加攻、剑意、锋锐、星力、气势、破绽（对方、负面）、外伤（对方、负面）
# 减少buff 减攻（负面）、虚弱（负面）、潜遁（对方）、铁骨（对方）

# 优先级：
# 先加减并最终至少为1：加攻、剑意、锋锐、星力、外伤（对方）、减攻
# 乘以百分比（多个百分比之间先相加）最终至少为1：气势、破绽（对方）、虚弱
# 额外结算，最终至少为1：潜遁、铁骨


# 其他buff：
# 正面buff 辟邪、......
# 负面buff 内伤(负面) 困缚(负面)

# buff值若大于0则减少1
*/

#include <iostream>
#include <string>

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

#define DEBUFF_START_INDEX 16 //负面buff开始索引

#define DEBUFF_PO_ZHAN DEBUFF_START_INDEX+0 //破绽
#define DEBUFF_WAI_SHANG DEBUFF_START_INDEX+1 //外伤
#define DEBUFF_JIAN_GONG DEBUFF_START_INDEX+2 //减攻
#define DEBUFF_XU_RUO DEBUFF_START_INDEX+3 //虚弱
#define DEBUFF_NEI_SHANG DEBUFF_START_INDEX+4 //内伤
#define DEBUFF_KUN_FU DEBUFF_START_INDEX+5 //困缚
#define DEBUFF_END_INDEX DEBUFF_START_INDEX+6 //负面buff结束索引
// 修改需要修改DEBUFF_END_INDEX，并同时修改buff_name数组

int buff_reduce(int value){
    if (value > 0) {
        return value - 1;
    }
    return value;
}


// Buff类
/*
Buff使用BuffGain和BuffReduce进行增加和减少
Debuff使用DebuffGain和DebuffReduce进行增加和减少
不属于buff和debuff的特殊想过有其它函数进行增加和减少
一次攻击牌打出后、一次伤害结算后、一次回合结束后，结算BUFF变更
*/
class Buff {
public:
    // 构造函数
    Buff() {
        // buff数组，初始化为0
        for (int i = 0; i < DEBUFF_END_INDEX; i++) {
            buff[i] = 0;
        }
    }

    // 析构函数
    ~Buff() {
        
    }

    // 成员函数
    // 一次攻击结算后，结算BUFF变更
    void attack_change() {
        this->buff[BUFF_GONG_JI_WU_SHI_FANG_YU] = buff_reduce(this->buff[BUFF_GONG_JI_WU_SHI_FANG_YU]);
    }

    void a_card_change() {
        if (is_card_attacked) {
            this->buff[BUFF_JIAN_YI] = buff_reduce(this->buff[BUFF_JIAN_YI]);
        }
        else {
            is_card_attacked = false;
        }
    }

    // 一次伤害结算后，结算BUFF变更
    void a_damage_change(bool attacking, bool hurting) {
        if (attacking) {
            is_card_attacked = true;
            this->buff[BUFF_QI_SHI] = buff_reduce(this->buff[BUFF_QI_SHI]);

            if (hurting) {
                this->buff[BUFF_FENG_RUI] = buff_reduce(this->buff[BUFF_FENG_RUI]);
            }
        }
    }

    // 一方回合结束后，结算该方BUFF变更
    void a_side_round_change() {
        this->buff[DEBUFF_PO_ZHAN] = buff_reduce(this->buff[DEBUFF_PO_ZHAN]);
        this->buff[DEBUFF_XU_RUO] = buff_reduce(this->buff[DEBUFF_XU_RUO]);

        this->buff[BUFF_QIAN_DUN] = buff_reduce(this->buff[BUFF_QIAN_DUN]);
        this->buff[BUFF_TIE_GU] = buff_reduce(this->buff[BUFF_TIE_GU]);
    }

    // 打印所有不为0的buff
    void print_buff() {
        for (int i = 0; i < DEBUFF_END_INDEX; i++) {
            if (buff[i] != 0) {
                std::cout << buff_name[i] << ": " << buff[i] << " ";
            }
        }
    }
    
    // 成员变量
    int buff[DEBUFF_END_INDEX];
    const std::string buff_name[DEBUFF_END_INDEX] = {
        "加攻", "剑意", "锋锐", "星力", "气势", "气势上限", "潜遁", "铁骨", "辟邪", "身法", "护体", "攻击无视防御",
        "跳过牌", "无法行动", "锻骨剩余次数", "气若悬河剩余次数",
        "破绽", "外伤", "减攻", "虚弱", "内伤", "困缚"
    };
    bool is_card_attacked = false;

};
#endif // BUFF_H
