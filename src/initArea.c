#include "pcb.h"
#include "const.h"
#include "handler.h"
#include "interrupt.h"
#include "listx.h"
#include "scheduler.h"
#include "types_rikaya.h"
#include "initArea.h"
#include "p1.5test_rikaya_v0.c"

state_t* state;
/* Puntatori alle NEW AREA della ROM */
HIDDEN state_t *sys_newarea;
HIDDEN state_t *program_trap_newarea;
HIDDEN state_t *interrupt_newarea;
HIDDEN state_t *tblmgt_newarea;

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
