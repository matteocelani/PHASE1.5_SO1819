#include "pcb.h"
#include "const.h"
#include "handler.h"
#include "interrupt.h"
#include "listx.h"
#include "scheduler.h"
#include "types_rikaya.h"
#include "initArea.h"
#include "p1.5test_rikaya_v0.c"

/* Lista dei processi ready */
INIT_LIST(ready_queue);
/* Puntatore al processo attivo */
pcb_t current_process = NULL;
/* Contatore processi */
u32 process_count = 0;
/* Contatore processi bloccati per I/O */
u32 soft_block_count = 0;

int main(void){
    
    initPcbs();
    



    return 0;
}
