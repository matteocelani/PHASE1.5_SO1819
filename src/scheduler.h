#include "types_rikaya.h"
#include "const.h"
#include "pcb.h"

#define TIME_SLICE  3

/*funzione che in caso di deadlock lo gestisce altrimenti Round Robin tra i processi */
void scheduler();

HIDDEN inline void priorityAging(void);
HIDDEN inline void restorePriority(pcb_t *pcb);
