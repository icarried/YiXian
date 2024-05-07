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
    if (realm_str == "炼气期") {
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
    return 0;
}