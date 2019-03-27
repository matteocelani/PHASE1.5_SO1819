#include "pcb.h"
#include "const.h"
#include "handler.h"
#include "interrupt.h"
#include "listx.h"
#include "scheduler.h"
#include "types_rikaya.h"
#include "p1.5test_rikaya_v0.c"

INIT_LIST(ready_queue);

int main(void){
    
    initPCB();



    return 0;
}
