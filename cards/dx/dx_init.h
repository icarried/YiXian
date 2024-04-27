#ifndef DX_INIT_H
#define DX_INIT_H
#include "dx_lqq.h"
#include "dx_zjq.h"
#include "dx_jdq.h"
#include "dx_yyq.h"
#include "dx_hsq.h"

/*
cultivation_realm_serial_number:
炼气期 llq 1
筑基期 zjq 2
金丹期 jdq 3
元婴期 yyq 4
化神期 hsq 5
*/
// BaseCard* dx_create(int cultivation_realm_serial_number, int card_serial_number, int level, int position) {
//     switch (cultivation_realm_serial_number) {
//     case 1:
//         return dx_lqq_create(card_serial_number, level, position);
//     case 2:
//         return dx_zjq_create(card_serial_number, level, position);
//     case 3:
//         return dx_jdq_create(card_serial_number, level, position);
//     case 4:
//         return dx_yyq_create(card_serial_number, level, position);
//     case 5:
//         return dx_hsq_create(card_serial_number, level, position);
//     default:
//         throw std::invalid_argument("Invalid cultivation_realm_serial_number");
//     }
// }

#endif // DX_INIT_H
