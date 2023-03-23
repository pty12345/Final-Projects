#include "../../include/malloc.h"

#include "../../include/schedule/scheduler.h"

extern void myMain(void);

void idleTsk(void);
void schedule(void);

extern int tick_number;


Bool ReadyQueueEmpty = True;

unsigned long ReadyQueue_MaxLen = 1000;
int idle_id,idle_sp;

unsigned long **prevTSK_StackPtrAddr;
unsigned long *nextTSK_StackPtr;

ScheduleWay SW;

TCB current_tsk;



void context_switch(unsigned long **prevTskStkAddr, unsigned long *nextTskStk) {
    prevTSK_StackPtrAddr = prevTskStkAddr;
    nextTSK_StackPtr = nextTskStk;
    CTX_SW();
}

// TCB nextRunningTsk() {
//     return Qpop(&ReadyQueueFF);
// }

unsigned long *BspContextBase;
unsigned long *BspContext;void startMultitask(void) {
    BspContextBase = (unsigned long *)kmalloc(0x1000); 
    BspContext = BspContextBase + 0x1000 - 1; ///

    //firstTsk = nextFCFSTsk();
    schedule();
}

void schedule(void){    
    while (1){			
        TCB NextTask;            
        if (ReadyQueueEmpty == True) {
            tskStart_By_ID(idle_id);
        } else {
            ;
        }
        // display_ReadyQueue();
        switch (SW)
        {
            case FCFS:
                NextTask = Qpop(&ReadyQueueFF);
                //PrintTCB(NextTask);
               // myPrintk(0x7, "\nnext_id:%d\n",NextTask.tid);
                break;
            case SJF:
                NextTask = QpopSJF();
                break;
            case PRI:
                NextTask = QpopPRI();
                break;

            default:
                break;
        }

        //if(NextTask.tid == 3)
        //PrintTCB(NextTask);
        //display_ReadyQueue();
        NextTask.state = RUNNING;
        current_tsk = NextTask;
       // myPrintk(0x7, "time: %d, task%d is in the CPU\n", tick_times, CurrentTask->tid);
         // myPrintk(0x7, "task%d is in the CPU\n", current_tsk.tid);      
        // runtime = 0;
        context_switch(&BspContext, current_tsk.sp);
        // myPrintk(0x7,"1\n");
    }	
}

void idleTsk(void) {
    while(ReadyQueueEmpty) {
        ;//myPrintk(0x7,"Time:%d\n",tick_number);	
    }

}

void taskReadyQueue_init() {
    switch (SW)
    {
        case FCFS:
            QInit(&ReadyQueueFF, ReadyQueue_MaxLen);
            break;
        case SJF:
            QInitSJF(ReadyQueue_MaxLen);
            break;
        case PRI:
            QInitPRI(ReadyQueue_MaxLen);
           // myPrintf(0x7,"ReadyQueuePri_head_size: %d\n",ReadyQueuePri_head->maxsize);
            break;
        default:
            break;
    }
}

void taskManager_init() {
    // 为tasklist分配空间
    NewTask_list_head = (NewTask_list*) kmalloc(sizeof(NewTask_list));
    NewTask_list_head->next = 0;
    taskReadyQueue_init();

    idle_id = createTsk(idleTsk);
    idle_sp = NewTask_list_head->next->data.sp;


    int myMain_id = createTsk(myMain);

    tskStart_By_ID(myMain_id);

    startMultitask();
}

int createTsk(void (*tskBody)(void)) {
    TCB tcb ;
    tcb.tid = tid_count++;
    tcb.state = NEW;
    tcb.params = (tskPara) {.priority = 0, .arrTime = 0, .exeTime = 0};

    unsigned long stack_top = kmalloc(stack_size);
    tcb.stk_top = stack_top;
    tcb.sp = (unsigned long* )(stack_top + stack_size) - 1;

    stack_init(&tcb.sp, tskBody);
   // myPrintf(0x7,"tcb_sp%x \n",tcb.sp);

    NewTask_list* tmp = (NewTask_list*) kmalloc(sizeof(NewTask_list));
   // myPrintf(0x7,"tmp_place%x ",tmp);
    tmp->data = tcb;
    
    tmp->next = NewTask_list_head->next;
    NewTask_list_head->next = tmp;
    
    //myPrintf(0x7,"tmp_id%x\n",tmp->data.tid);

    return tcb.tid;
} 

Bool tskStart(TCB tsk) {

    if(Check_ReadyQueue() == False)
        return False;

    tsk.state = READY;
    New_to_ReadyQueue(tsk);

    return True;
}

void destroyTsk(int tsk_stack_top) {
    kfree(tsk_stack_top); 
}

void tskEnd() {
    //if(current_tsk.tid != idle_id)
    destroyTsk(current_tsk.stk_top);
    // display_ReadyQueue();
    context_switch(&current_tsk.sp,BspContext);
    //myPrintk(0x7, "task%d will be destroy\n", current_tsk.tid);  
    schedule();
    return;
}

Bool tskStart_By_ID(int tsk_id) {
    NewTask_list* tmp = NewTask_list_head->next;
    NewTask_list* prev = NewTask_list_head;

    for (; tmp; tmp = tmp->next) {
        if (tmp->data.tid == tsk_id) break;
        prev = tmp;
    }

    if (!tmp) return False;
    TCB tsk = tmp->data;

    if(tskStart(tsk) == False)
        return False; //The Ready Queue is full

    ReadyQueueEmpty = False;
    //if(tsk_id == 1)
    //    PrintTCB(tsk);
    prev->next = tmp->next;
    //kfree((unsigned long) tmp);

    return True;
}

void New_to_ReadyQueue(TCB tsk) {
    switch (SW)
    {
        case FCFS:
            Qpush(&ReadyQueueFF, tsk); 
            break;
        case SJF:
            QpushSJF(ReadyQueueSJF_head, tsk);
            break;
        case PRI:
            QpushPRI(ReadyQueuePri_head, tsk); 
            break;
    
    default:
        break;
    }
    
    // manage according to FIFO

}

Bool Check_ReadyQueue() {
    
    switch (SW)
    {
        case FCFS:
            return Qfull(&ReadyQueueFF) == True ? False : True;
            break;
        case SJF:
            return QfullSJF(ReadyQueueSJF_head) == True ? False : True;
            break;
        case PRI:
            return QfullPRI(ReadyQueuePri_head) == True ? False : True;
            break;
    
    default:
        break;
    }
    


}

void display_ReadyQueue() {
    switch (SW)
    {
        case FCFS:
            display_readyqueueFIFO(&ReadyQueueFF);
            break;
        case SJF:
            display_ReadyQueueSJF(ReadyQueueSJF_head);
            break;
        case PRI:
            display_readyqueuePRI(ReadyQueuePri_head);
            break;
    
    default:
        break;
    }

}

void display_NewQueue() {
    myPrintf(0x7, "NewQueue_id:\n");

    NewTask_list* tmp = NewTask_list_head->next;

    for (; tmp; tmp = tmp->next) 
        myPrintf(0x7, "tid : %d pri : %d\n",tmp->data.tid, tmp->data.params.priority);
}