#include "types_rikaya.h"
#include "const.h"
#include "pcb.h"


void scheduler(void) {

	/*gestione dei deadlock poi dei processi*/
	if (!ready_queue) {
		/* se process count = 0 invoco HALT ROM */
		if (process_count == 0) 
			HALT();
    		/* se process count > 0 e soft block count = 0 deadlock */
		if (process_count > 0 && soft_block_count == 0)
			PANIC();
    		/* se process count e soft block count > 0 invoco un istruzione WAIT*/
		if (process_count > 0 && soft_block_count > 0)
			WAIT();
	}
	else {
		/*Caso anomalo: nessun processo corrente*/
		if (current_process == NULL)
			PANIC();
		//headProcQ(current_process);
	}
	
	/*Verifica che i processi vengano alternati correttamente*/
	log_process_order(current_process->original_priority) ;
		
}

// restorePriority e priorityAgin vanno chiamate dopo aver estratto il processo (con priorità massima) dalla readyqueue

/* Funzione che si occupa del meccanismo di aging delle priorità dei PCB nella ready queue */
HIDDEN inline void priorityAging(void) {
	if (ready_queue) {
    		/* PCB temporaneo che uso per scorrere la ready_queue */
		pcb_t *tmp = readyQueue;
		/* Scorro tra processi che già hanno priorità massima */
		while (tmp->p_priority == MAXPRIO && tmp->p_next != NULL) tmp = tmp->p_next;
		/* Scorro tra i processi che non hanno priorità massima e la aumento */
		while (tmp->p_next != NULL) {
			tmp->p_priority++;
			tmp = tmp->p_next;
		}
	}

}

/* Funzione che si occupa di ripristinare la priorità originale di un PCB */
HIDDEN inline void restorePriority(pcb_t *pcb){
	pcb->priority = pcb->original_priority 	
}
