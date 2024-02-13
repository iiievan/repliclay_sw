#ifndef __FSM_SHEDULER_H
#define __FSM_SHEDULER_H

#include <stdbool.h>
#include "stdint.h"
#include "fsm.h"
#include "fsm_types_capi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_FSM_FIFO_LEN    (16U)       // fsm list length
#define MAX_ACTIVE_FSM      (2)         // number of simultaneously operating FSMs at the moment
#define FSM_ITEM_SIZE       (sizeof(fsm_t))
#define FSM_PARAM_TYPE      action_cmd
#define FSM_PARAM_SIZE      (sizeof(action_cmd))

#ifdef __cplusplus
}
#endif

#endif  // __FSM_SHEDULER_H
