#include <semaphore.h>
#include <listx.h>

HIDDEN semd_t semd_table[MAX_PROC];

LIST_HEAD(semdFree_h);

void initASL () {
  int i=0;

  for (i;i<=MAX_PROC;i++){

    semd_t* semt= &semd_table[MAX_PROC];
        list_add_tail(&(semt.s_next),&(semdFree_h));
  }
}
