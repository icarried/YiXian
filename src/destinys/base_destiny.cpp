#include "base_destiny.h"


// 空仙命，注册REALM_NONE到REALM_HSQ

bool EmptyDestiny::registered = []() {
    for (int i = REALM_NONE; i <= ROLE_REALM_MAX; ++i) {
        BaseDestiny::registerDestiny(i, "空仙命", [](BaseRole* role) -> BaseDestiny* {
            return new EmptyDestiny(role);
        });
    }
    return true;
}();