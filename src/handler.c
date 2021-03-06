#include "pcb.h"
#include "const.h"
#include "handler.h"
#include "listx.h"
#include "types_rikaya.h"
#include "p1.5test_rikaya_v0.c"

/* Gestione SYSCALL/BREAKPOINT */
void sysbk_handler(void){
    /* Stato dell'esecuzione prima dell'eccezione */
    state_t *old_state = sysbk_oldarea;
    /* Registro nel quale è salvata la SYSCALL chiamata */
    u32 syscall_number = old_state->reg_a0
    
    switch (syscall_number){
        /* Eseguo la SYSCALL richiesta */
        case TERMINATEPROCESS:
            // SYSCALL TERMINATE PROCESS
            break;
        default:
            /* Errore numero SYSCALL inesistente */
            PANIC();
    }
    scheduler():
    
    /* Gestione dei BREAKPOINT da implementare nella PHASE2 */
}

/* Gestione INTERRUPT */
void int_handler(void){
    
}

/* Gestione TLB */
void tlb_handler(void){
    /* Da implementare nella PHASE2 */
}

/* Gestione PGMTRP */
void pgmtrp_handler(void){
    /* Da implementare nella PHASE2 */
}


/* SYSTEMCALL */
/* Definite HIDDEN perché devono essere accessibili solo da sysbk_handler */


/* SYSCALL3
 * Quando invocata termina il processo corrente
 * e tutta la sua progenie, rimuovendoli dalla
 * Ready Queue.
*/
HIDDEN void terminateProcess(pcb_t *p){  
    while(!list_empty(p->p_child))
        freePcb(removeChild(p->p_child));
    outChild(p);
    freePcb(p);
}
