#include "pcb.h"
#include "const.h"
#include "handler.h"
#include "listx.h"
#include "types_rikaya.h"
#include "p1.5test_rikaya_v0.c"

/* Funzioni per la gestione delle eccezioni */
void sysbk_handler(void);
void int_handler(void);
void tlb_handler(void);
void pgmtrp_handler(void);
