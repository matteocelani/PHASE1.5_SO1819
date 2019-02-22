#include "listx.h"
#include "types_rikaya.h"
#include "const.h"

/* array di semd con dimensione massima MAX PROC*/
HIDDEN semd_t semd_table[MAX_PROC];

/*lista dei semd liberi o inutilizzati*/
/*HIDDEN struct list_head semdFree = LIST_HEAD_INIT(semdFree);
inizializzazione elemento sentinella*/

HIDDEN LIST_HEAD(semdFree_h);

/* Creo lista ASL e sentinella*/

HIDDEN LIST_HEAD(semd_h);

/*LIST_HEAD(semdFree_h);*/

void initASL () {
  int i=0;

  for (i;i<=MAX_PROC;i++){

    semd_t* semt= &semd_table[MAX_PROC];
        list_add_tail(&(semt.s_next),&(semdFree_h));
  }
}


/* DESCRIZIONE: 
restituisce il puntatore al SEMD nella ASL la cui chiave è pari a key. Se non 
esiste un elemento nella ASL con chiave eguale a key, viene restituito NULL. */

HIDDEN semd_t* getSemd(int *key){

	if (list_empty(semd_h)) return NULL; 		
	semd_t* p; 
	semd_t* res = NULL;
	list_for_each_entry(p, semd_h, s_next){		
		if( key == p->s_key){
		 res = container_of(semd_h->next , semd_t, s_next);
	}
	return res; 
}

/* DESCRIZIONE: Viene inserito il PCB puntato da p nella coda dei processi bloccati 
associata al SEMD con chiave key. Se il semaforo corrispondente non è presente nella ASL, 
alloca un nuovo SEMD dalla lista di quelli liberi (semdFree) e lo inserisce nella ASL, 
settando I campi in maniera opportuna (i.e. key e s_procQ). Se non è possibile allocare 
un nuovo SEMD perché la lista di quelli liberi è vuota, restituisce TRUE. 
In tutti gli altri casi, restituisce FALSE.*/


/*int insertBlocked(int *key, pcb_t* p){
	
	semd_t* semd =  getSemd(key); 
	if (semd != NULL){
		insertProcQ( &(semd->s_procQ) , p);	
		return FALSE;
	}

}*/






