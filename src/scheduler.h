#include "types_rikaya.h"
#include "const.h"
#include "pcb.h"

#define TIME_SLICE  3


void priorityAging();

/*funzione che in caso di deadlock lo gestisce altrimenti Round Robin tra i processi */
void contextSwitch();
