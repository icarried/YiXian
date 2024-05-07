#include "dx_xiaobu.h"

bool RoleDxXiaobu::registered = BaseRole::registerRole("小布", [](Status* my_status, Status* enemy_status) {
    return new RoleDxXiaobu(my_status, enemy_status);
});