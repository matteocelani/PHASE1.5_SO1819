#include <pcb.h>
#include <const.h>
#include <typer_rikaya.H>
#include <listx.h>

HIDDEN pcb_t pcbFree_table[MAXPROC];

/* Lista con sentinella dei pcb liberi o inutilizzati */
LIST_HEAD(pcbFree_h);


/* PCB free list handling functions */

/* Inizializza la pcbFree in modo da contenere tutti gli elementi della pcbFree_table. */
/* Questo metodo deve essere chiamato una volta sola in fase di inizializzazione della struttura dati. */
void initPcbs(void){
    int i=0;
    for (i;i<MAXPROC;i++){
        /* Metto nella lista pcbFree_h i puntatori ai pcb */
        pcb_t* pcb= &pcbFree_table[MAXPROC];
        list_add_tail(&(pcb.p_next),&(pcbFree_h))
        ;

    }
}

/* Inserisce il pcb puntato da p nella lista dei PCB liberi */
void freePcb(pcb_t *p){
    list_add_tail(&(p->p_next, &(pcbFree_h);
}


/* Restituisce NULL se la pcbFree +vuota.                                 */
/* Altrimenti rimuove un elemento dalla pcbFree,                          */
/* inizializza tutti i campi (NULL\0) e restituisce l'elemento rimosso    */
pcb_t *allocPcb(void){
    /* Controllo per verificare se pcbFree sia vuoto o no */
    if (list_empty(&(pcbFree_h))) return NULL;

    /* Elemento precedente alla sentinella è l'ultimo elemento della lista */
    /* */
    pcb_t *tmp=container_of(pcbFree_h.prev, pcb_t, p_next);
    
    /* Rimuove tmp dalla lista pcbFree_H che lo contiene */
    list_del(tmp->p_next);

    /* Inizializzo tutti i campi di tmp a NULL */
    tmp->p_parent=NULL;
    tmp->p_semkey=NULL;
    tmp->priority=0;
    
    /* tmp->p_s bisogna azzerare tutta la struttura */
    /* non so quali siano i campi, vanno cercati nel manuale */


    INIT_LIST_HEAD(tmp->p_next);
    INIT_LIST_HEAD(tmp->p_child);
    INIT_LIST_HEAD(tmp->p_sib);

    return tmp;
}

/* PCB queue handling functions */
void mkEmptyProcQ(struct list_head *head);
int emptyProcQ(struct list_head *head);
void insertProcQ(struct list_head *head, pcb_t *p);
pcb_t *headProcQ(struct list_head *head);

pcb_t *removeProcQ(struct list_head *head);
pcb_t *outProcQ(struct list_head *head, pcb_t *p);


/* Tree view functions */
int emptyChild(pcb_t *this);
void insertChild(pcb_t *prnt, pcb_t *p);
pcb_t *removeChild(pcb_t *p);
pcb_t *outChild(pcb_t *p);
