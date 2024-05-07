#include "dx_tukui.h"

bool RoleDxTukui::registered = BaseRole::registerRole("屠馗", [](Status* my_status, Status* enemy_status) {
    return new RoleDxTukui(my_status, enemy_status);
});