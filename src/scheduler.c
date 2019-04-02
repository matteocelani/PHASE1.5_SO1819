#include "types_rikaya.h"
#include "const.h"
#include "pcb.h"


void priorityAging() {
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
