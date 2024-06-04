#ifndef FLAG_H
#define FLAG_H


#define FLAG_YI_ZAI_CI_XING_DONG 0 //已再次行动
#define FLAG_ZAI_CI_XING_DONG 1 //再次行动（不延续到下回合）使用ReexecuteGain获取
#define FLAG_WU_FA_ZAI_CI_XING_DONG 2 //无法再次行动（天音困仙曲）
#define FLAG_END_INDEX 3

// flag类

class Flag {
public:
    // 构造函数
    Flag() {
        for (int i = 0; i < FLAG_END_INDEX; i++) {
            flag[i] = false;
        }
    }

    // // 虚拷贝函数
    // virtual Flag* Clone() const {
    //     return new Flag(*this);
    // }

    // // 拷贝构造函数
    // Flag(const Flag& other) {
    //     for (int i = 0; i < FLAG_END_INDEX; i++) {
    //         flag[i] = other.flag[i];
    //     }
    // }

    // 析构函数
    ~Flag() {

    }

    // 一方回合结束后，结算该方BUFF变更
    void a_side_round_change() {
        flag[FLAG_YI_ZAI_CI_XING_DONG] = false;
        flag[FLAG_ZAI_CI_XING_DONG] = false;
    }

    bool flag[FLAG_END_INDEX]; //标志数组
};


#endif // !FLAG_H