#include "pcb.h"
#include "const.h"
#include "handler.h"
#include "interrupt.h"
#include "listx.h"
#include "scheduler.h"
#include "types_rikaya.h"
#include "p1.5test_rikaya_v0.c"

INIT_LIST(ready_queue);
pcb_t current_process;
u32 process_count;
u32 soft_block_count;

int main(void){
    
    initPcbs();
    



    return 0;
}
