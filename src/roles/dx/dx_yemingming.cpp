#include "dx_yemingming.h"

bool RoleDxYemingming::registered = BaseRole::registerRole("叶冥冥", [](Status* my_status, Status* enemy_status) {
    return new RoleDxYemingming(my_status, enemy_status);
});