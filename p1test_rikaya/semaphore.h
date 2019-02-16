#include <types_rikaya.h>
#include <umps/types.h>

/*Gestione della ASL*/
semd_t* getSemd (int key);
int insertBlocked (int key, pcb_t *p);
pcb_t* removeBlocked(int key);
pcb_t* outBlocked(pcb_t *p);
pcb_t* hedBlocked(int key);

void outChildBlocked(pcb_t *p);
void initASL();
