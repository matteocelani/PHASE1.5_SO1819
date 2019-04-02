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
HIDDEN inline void initSYSBK(u32 status){
    sysbk_newarea->status = status;
    sysbk_newarea->reg_sp = RAMTOP;
    /* Indirizzo della funzione che gestisce le SYSCALL */
    sysbk_newarea->pc_epc = sys_handler;  // La funzione la dobbiamo scrivere, intanto metto il nome
    sysbk_newarea->reg_t9 = sys_handler;
}

HIDDEN inline void initPGMTRP(u32 status){  
    program_trap_newarea->status = status;
    program_trap_newarea->reg_sp = RAMTOP;
    program_trap_newarea->pc_epc = gmtrp_handler;
    program_trap_newarea->reg_t9 = gmtrp_handler;
}
    
HIDDEN inline void initINT(u32 status){  
    interrupt_newarea->status = status;
    interrupt_newarea->reg_sp = RAMTOP;
    interrupt_newarea->pc_epc = int_handler;
    interrupt_newarea->reg_t9 = int_handler;
}

HIDDEN inline void initTLB(u32 status){  
    tblmgt_newarea->status = status;
    tblmgt_newarea->reg_sp = RAMTOP;
    tblmgt_newarea->pc_epc = tlb_handler;
    tblmgt_newarea->reg_t9 = tlb_handler;
}

/* Funzione che si occupa dell'inizializzazione delle NEWAREA della ROM.
 * Viene essere settato il campo status in maniera tale da:
 *  - Mascherare gli interrupt
 *  - Disabilitare la virtual memory
 *  - Abilita il processor local timer 
 *  - Essere in kernel mode
*/
void initAREA(void){  
    u32 s = 0;
    
    memset(sysbk_newarea, 0, 0x8C);
    memset(sysbk_oldarea, 0, 0x8C);
    memset(program_trap_newarea, 0, 0x8C);
    memset(program_trap_oldarea, 0, 0x8C);
    memset(interrupt_newarea, 0, 0x8C);
    memset(interrupt_oldarea, 0, 0x8C);
    memset(tblmgt_newarea, 0, 0x8C);
    memset(tblmgt_oldarea, 0, 0x8C);
    
    // intanto metto zero, ma andrà cambiato
    initSYS(s);
    initPGMTRAP(s);
    initINT(s);
    initTLB(s);
}
