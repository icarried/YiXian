#include "cal.h"

// buff数值减少且不小于0
int buff_reduce(int value){
    if (value > 0) {
        return value - 1;
    }
    return value;
}