#include "types_rikaya.h"
#include "const.h"
#include "pcb.h"


HIDDEN pcb_t pcbFree_table[MAXPROC];

/* Lista con sentinella dei pcb liberi o inutilizzati */
HIDDEN struct list_head pcbFree_h = LIST_HEAD_INIT(pcbFree_h);



/* PCB free list handling functions */

/* Inizializza la pcbFree in modo da contenere tutti gli elementi della pcbFree_table. */
/* Questo metodo deve essere chiamato una volta sola in fase di inizializzazione della struttura dati. */

HIDDEN void initPcbs(void){
	int i = 0;
	for(; i < MAXPROC; i++){
		pcb_t* pcb= &pcbFree_table[MAXPROC];
		list_add_tail(&(pcb->p_next),&(pcbFree_h));
	}
}

/* Inserisce il pcb puntato da p nella lista dei PCB liberi */

HIDDEN void freePcb(pcb_t *p){
	    list_add_tail(&(p->p_next), &(pcbFree_h));
}



/* Restituisce NULL se la pcbFree è vuota.                                 */
/* Altrimenti rimuove un elemento dalla pcbFree,                          */
/* inizializza tutti i campi (NULL\0) e restituisce l'elemento rimosso    */
HIDDEN pcb_t *allocPcb(void){
  
	/* Controllo per verificare se pcbFree sia vuoto o no */
	if (list_empty(&(pcbFree_h))) return NULL;
	/* Elemento precedente alla sentinella è l'ultimo elemento della lista */
	/* */
	pcb_t *tmp=container_of(pcbFree_h.prev, pcb_t, p_next);
					       
	/* Rimuove tmp dalla lista pcbFree_H che lo contiene */
	list_del(&(tmp->p_next));

	/* Inizializzo tutti i campi di tmp a NULL */
	tmp->p_parent = NULL;
	tmp->p_semkey = NULL;
	tmp->priority = 0;
	tmp->p_s.entry_hi = 0;
	tmp->p_s.cause = 0;
	tmp->p_s.status = 0;
	tmp->p_s.pc_epc = 0;
	
	/* Per il campo p_s.gpr[] uso un for per settare a 0 tutti le 29 variabili dell' array */
	int j = 0;
	for(;j<29;j++){
		tmp->p_s.gpr[j];
	}	
	tmp->p_s.hi = 0;
	tmp->p_s.lo = 0;
							        
	INIT_LIST_HEAD(&(tmp->p_next));								    
	INIT_LIST_HEAD(&(tmp->p_child));								        
	INIT_LIST_HEAD(&(tmp->p_sib));
									    
	return tmp;
 }

/* PCB queue handling functions */

HIDDEN void mkEmptyProcQ(struct list_head *head){

	INIT_LIST_HEAD(head);
}

/* Controllo se la lista puntata da head è vuota e restituisco true in caso affermativo, false altrimenti */

HIDDEN int emptyProcQ(struct list_head *head){
	if (list_empty(head))
		return TRUE;
	else 
		return FALSE;
}

/* Inserisco un processo in coda alla lista, controllando che la priorità sia decrescente */
HIDDEN void insertProcQ(struct list_head *head, pcb_t *p){

	/* Uso un puntatore a pcb_t temporaneo per scorrere la lista */
	pcb_t *tmp_pcb;
	/* Uso la macro list_for_each_entry per poter scorrere la lista partendo dalla sentinella head */
	list_for_each_entry(tmp_pcb, head, p_next){
		if(p->priority > tmp_pcb->priority){

			struct list_head *prev = list_prev(&(tmp_pcb->p_next));
			__list_add(&(p->p_next), (prev), &(tmp_pcb->p_next)); /* Inserisco l'elemento p->next se la sua priorità è maggiore della priorità dell'elemento puntato da tmp_pcb */

		}
	}

	/* Se la priorità di p non soddisfa la condizione dell'if, allora la sua priorità sarà minore di tutti gli altri elementi della lista e lo aggiungo in coda */

	list_add_tail(&(p->p_next), (head));


}


/* Restituisce l'elemento di testa della coda dei processi da head, senza rimuoverlo. */
/* Ritorna NULL se la coda non ha elementi 					      */

HIDDEN pcb_t *headProcQ(struct list_head *head){
		/* Controllo iniziale per vedere se head è vuoto */
		if (list_empty(head)) return NULL;		
		/* Devo restituire il primo elemento della lista head non vuota. */	
		return (container_of(head->next, pcb_t, p_next)); 
}

/* Rimuove il primo elemento dalla coda dei processi puntata da head. Ritorna NULL se la coda è vuota. */
/* Altrimenti ritorna il puntatore all'elemento rimosso dalla lista 				       */

HIDDEN pcb_t *removeProcQ(struct list_head *head){
		/* Controllo iniziale per vedere se head è vuoto */
		/* Se lista è vuota restituisco NULL */
		if (list_empty(head)) return NULL; 
				
		/* C'è almeno un elemento nella lista */
		/* Rimuovo il primo e lo restituisco  */
		pcb_t *tmp = container_of(head->next,pcb_t,p_next) ;	/* Puntatore al primo elemento della lista */
		list_del(head->next);					/* Lo rimuovo dalla lista */
		return tmp ;

}

/* Rimuove il PCB puntato da p dalla coda dei processi puntata da head  */
/* Se p non è presente nella coda, restituisce NULL	 		*/

HIDDEN pcb_t *outProcQ(struct list_head *head, pcb_t *p){
		
		/* Scorro la lista head alla ricerca di p */
		/* Puntatore che uso per confrontare gli elementi della coda con p */
		pcb_t *tmp, *i;	
		list_for_each_entry(i, head, p_next){
		/* Se p==i, allora rimuovo p dalla lista e lo restituisco */
		if (p == i) {
		list_del(&(i->p_next));					
		return p;						

		}
	}
	/* Ho finito di scorrere head e non ho trovato p */
	/* Restituisco NULL */
	return NULL; 
}



/* Tree view functions */


/* Controllo se la lista passata come parametro ha figli o meno e restituisco TRUE in caso non ne abbia e FALSE altrimenti */ 
HIDDEN int emptyChild(pcb_t *this){
	if (list_empty(&(this->p_child))) 
		return TRUE;
	else 
		return FALSE;
}

HIDDEN void insertChild(pcb_t *prnt, pcb_t *p){
	/* Aggiungo il processo p alla lista dei figli dei processi di prnt */
	list_add_tail(&(p->p_next), &(prnt->p_child));
	
	/* Collego il figlio con il padre tramite il puntatore *p_parent */
	p->p_parent = prnt;
}


HIDDEN pcb_t *removeChild(pcb_t *p){
	
	/*Controllo se il processo ha dei figlio e restituisco NUll in caso negativo */ 
	if (list_empty(&(p->p_child))){
		return NULL;
	}else{
		/* Se la lista ha dei figli, controllo se ci sono uno o più figli*/
		if(list_is_last(&(p->p_child), &(p->p_child))){
			/* Non ci sono fratelli, elimino il figlio unico */
			list_del(&(p->p_child));
		}else{
			/* Ci sono dei fratelli, elimino il prio figlio 
			 * e imposto il secondo figlio come primo */
			struct list_head *tmp_child = list_next(&p->p_child);
			list_del(&(p->p_child));
			p->p_child = tmp_child;
		}
		return p;
	}
}

/*
HIDDEN pcb_t *outChild(pcb_t *p){
	if(p->p_parent == NULL)
		return NULL;
	else{
		struct list_head *pos, *head;
		head = p->p_parent->p_child;
		list_for_each(pos, head){
				if(&(p->p_next) == head)
					list_del(&head);
			}
		return p;
	}
}
*/

