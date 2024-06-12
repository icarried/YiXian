#include "cal.h"

// buff数值减少且不小于0
int buff_reduce(int value){
    if (value > 0) {
        return value - 1;
    }
    return value;
}

// 炼气期转为1，筑基期转为2，金丹期转为3，元婴期转为4，化神期转为5
int StrToRealm(std::string realm_str) {
    if (realm_str == "无境界") {
        return 0;
    }
    else if (realm_str == "炼气期") {
        return 1;
    }
    else if (realm_str == "筑基期") {
        return 2;
    }
    else if (realm_str == "金丹期") {
        return 3;
    }
    else if (realm_str == "元婴期") {
        return 4;
    }
    else if (realm_str == "化神期") {
        return 5;
    }
    else if (realm_str == "返虚期") {
        return 6;
    }
    return 0;
}

// 1转为炼气期，2转为筑基期，3转为金丹期，4转为元婴期，5转为化神期
std::string RealmToStr(int realm) {
    
    if (realm == 0) {
        return "无境界";
    }
    else if (realm == 1) {
        return "炼气期";
    }
    else if (realm == 2) {
        return "筑基期";
    }
    else if (realm == 3) {
        return "金丹期";
    }
    else if (realm == 4) {
        return "元婴期";
    }
    else if (realm == 5) {
        return "化神期";
    }
    else if (realm == 6) {
        return "返虚期";
    }
    return "无境界";
}