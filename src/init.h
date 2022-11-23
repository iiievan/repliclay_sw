#ifndef __INIT_H
#define __INIT_H

#include "app_utils.h"
#include <uC_cpu.h>
#include <os.h>

extern void GPIOModuleClkConfig(CPU_INT32U x);
extern void init_board(void);
extern uint32_t board_info_check(uint8_t *board_ver);

#endif  //__INIT_H