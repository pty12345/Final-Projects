#include "../../include/HookInit.h"
#include "../../include/schedule/scheduler.h"
#include "../../include/tick.h"

void Check_and_Set_ReadyQueueState() {

    switch (SW)
    {
        case FCFS:
                if(Qempty(&ReadyQueueFF) == True) ReadyQueueEmpty = True;
                else ReadyQueueEmpty = False;
            break;
        case SJF:
            if(QemptySJF(ReadyQueueSJF_head) == True) ReadyQueueEmpty = True;
            else ReadyQueueEmpty = False;
            break;
        case PRI:
                if(QemptyPRI(ReadyQueuePri_head) == True) ReadyQueueEmpty = True;
                else ReadyQueueEmpty = False;
            break;
        default:
            break;
    }

   // myPrintk(0x7,"NowRunning id:%d\n",current_tsk.tid);
        
}

void HookInit() {
    append2hook(Check_and_Set_ReadyQueueState);
}