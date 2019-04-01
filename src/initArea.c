#include "pcb.h"
#include "const.h"
#include "handler.h"
#include "interrupt.h"
#include "listx.h"
#include "scheduler.h"
#include "types_rikaya.h"
#include "initArea.h"
#include "p1.5test_rikaya_v0.c"

/* Funzioni per l'inizializzazione delle NEW AREA */
HIDDEN inline void initSYS(u32 status){
    sys_newarea->status = status;
    state->reg_sp = RAMTOP;
    /* Indirizzo della funzione che gestisce le SYSCALL */
    state->pc_epc = sys_handler;  // La funzione la dobbiamo scrivere, intanto metto il nome
    state->reg_t9 = sys_handler;
}

HIDDEN inline void initPGMTRP(u32 status){  
    program_trap_newarea->status = status;
    state->reg_sp = RAMTOP;
    state->pc_epc = gmtrp_handler;
    state->reg_t9 = gmtrp_handler;
}
    
HIDDEN inline void initINT(u32 status){  
    interrupt_newarea->status = status;
    state->reg_sp = RAMTOP;
    state->pc_epc = int_handler;
    state->reg_t9 = int_handler;
}

HIDDEN inline void initTLB(u32 status){  
    tblmgt_newarea->status = status;
    state->reg_sp = RAMTOP;
    state->pc_epc = tlb_handler;
    state->reg_t9 = tlb_handler;
}

/* Funzione che si occupa dell'inizializzazione delle NEWAREA della ROM.
 * Viene essere settato il campo status in maniera tale da:
 *  - Mascherare gli interrupt
 *  - Disabilitare la virtual memory
 *  - Abilita il processor local timer 
 *  - Essere in kernel mode
*/
void initNEWAREA(void){  
    u32 s = 0;
    // intanto metto zero, ma andrà cambiato
    initSYS(s);
    initPGMTRAP(s);
    initINT(s);
    initTLB(s);
}
