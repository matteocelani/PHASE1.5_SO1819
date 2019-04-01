#include "pcb.h"
#include "const.h"
#include "handler.h"
#include "interrupt.h"
#include "listx.h"
#include "scheduler.h"
#include "types_rikaya.h"
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
HIDDEN state_t *sys_newarea;
HIDDEN state_t *program_trap_newarea;
HIDDEN state_t *interrupt_newarea;
HIDDEN state_t *tblmgt_newarea;

/* Funzioni per l'inizializzazione delle NEW AREA */
inline void initSYS(u32 status){
    sys_newarea->status = status;
    state->reg_sp = RAMTOP;
    /* Indirizzo della funzione che gestisce le SYSCALL */
    state->pc_epc = sys_handler;  // La funzione la dobbiamo scrivere, intanto metto il nome
    state->reg_t9 = sys_handler;
}
// Bisogna fare la stessa cosa fatta per sys_newarea per gli altri state
// gli indirizzi sono scritti in const.h
inline void initPGMTRP(u32 status){    
}
    
inline void initINT(u32 status){   
}

inline void initTLB(u32 status){   
}

void initNEWAREA(void){
    /* Status deve essere settato in maniera tale da:
     *  - Mascherare gli interrupt
     *  - Disabilitare la virtual memory
     *  - Abilita il processor local timer 
     *  - Essere in kernel mode
    */
    u32 s = 0;
    // intanto metto zero, ma andrà cambiato
    initSYS(s);
    initPGMTRAP(s);
    initINT(s);
    initTLB(s);
}


int main(void){
    
    initPcbs();
    



    return 0;
}
