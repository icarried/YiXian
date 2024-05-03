#ifndef DX_XIAOBU_H
#define DX_XIAOBU_H

#include "../base_role.h"

class RoleDxXiaobu : public BaseRole {
public:
    // ！！未完成
    class ExclusiveDestinyLQQ : public BaseDestiny {
    public:
        ExclusiveDestinyLQQ() {
            name = "磨砺不止";
            realm = REALM_LQQ;
        }
        ~ExclusiveDestinyLQQ() = default;
    };

    // ！！未完成
    class ExclusiveDestinyZJQ : public BaseDestiny {
    public:
        ExclusiveDestinyZJQ() {
            name = "锻体不息";
            realm = REALM_ZJQ;
        }
        ~ExclusiveDestinyZJQ() = default;
    };

    // ！！未完成
    class ExclusiveDestinyJDQ : public BaseDestiny {
    public:
        ExclusiveDestinyJDQ() {
            name = "灵涌不竭";
            realm = REALM_JDQ;
        }
        ~ExclusiveDestinyJDQ() = default;
    };

    // ！！未完成
    class ExclusiveDestinyYYQ : public BaseDestiny {
    public:
        ExclusiveDestinyYYQ() {
            name = "生机不灭";
            realm = REALM_YYQ;
        }
        ~ExclusiveDestinyYYQ() = default;
    };

    // ！！未完成
    class ExclusiveDestinyHSQ : public BaseDestiny {
    public:
        ExclusiveDestinyHSQ() {
            name = "修玄不泯";
            realm = REALM_HSQ;
        }
        ~ExclusiveDestinyHSQ() = default;
    };

    RoleDxXiaobu();
};


#endif // DX_XIAOBU_H