#include "pcb.h"
#include "const.h"
#include "handler.h"
#include "interrupt.h"
#include "listx.h"
#include "scheduler.h"
#include "types_rikaya.h"
#include "initArea.h"
#include "utils.h"
#include "p1.5test_rikaya_v0.c"

/* Lista dei processi ready */
INIT_LIST(ready_queue);
/* Puntatore al processo attivo */
pcb_t current_process = NULL;
/* Contatore processi */
u32 process_count = 0;
/* Contatore processi bloccati per I/O */
u32 soft_block_count = 0;

/* Puntatori alle NEW AREA della ROM */
HIDDEN state_t *sysbk_newarea = SYSBK_NEWAREA;
HIDDEN state_t *program_trap_newarea = PRGTRP_NEWAREA;
HIDDEN state_t *interrupt_newarea = INT_NEWAREA;
HIDDEN state_t *tblmgt_newarea = TLB_NEWAREA;

/* Puntatori alle OLD AREA della ROM */
HIDDEN state_t *sysbk_oldarea = SYSBK_OLDAREA;
HIDDEN state_t *program_trap_oldarea = PRGTRP_OLDAREA;
HIDDEN state_t *interrupt_oldarea = INT_OLDAREA;
HIDDEN state_t *tblmgt_oldarea = TBL_OLDAREA;


int main(void){
    
    initNEWAREA();
    initPcbs();
    
    current_process = allocPCB();
    process_count++;
    

    return 0;
}
