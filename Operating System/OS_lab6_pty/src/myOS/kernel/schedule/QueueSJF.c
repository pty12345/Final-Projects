#include "../../include/schedule/QueueSJF.h"
#include "../../include/myPrintk.h"

#define QUEUE ReadyQueueSJF


ReadyQueueSJF* ReadyQueueSJF_head; 

void QInitSJF(int ReadyQueue_MaxLen) {
    ReadyQueueSJF_head = (ReadyQueueSJF* )kmalloc(sizeof(ReadyQueueSJF));
    ReadyQueueSJF_head->nowsize = 0;
    ReadyQueueSJF_head->next = 0;
    ReadyQueueSJF_head->maxsize = ReadyQueue_MaxLen;
    myPrintf(0x7,"InitQueueMaxsize:%d\n",ReadyQueueSJF_head->maxsize);
}

Bool QpushSJF(QUEUE* queue, TCB tcb) {

    ReadyQueueSJF* prev = ReadyQueueSJF_head;

    while(prev->next != 0 && prev->next->data.params.exeTime <= tcb.params.exeTime) {
        prev = prev->next;
    }


    ReadyQueueSJF* tmp = (ReadyQueueSJF* )kmalloc(sizeof(ReadyQueueSJF));

    tmp->data = tcb;
    tmp->next = prev->next;

    prev->next = tmp;
    ReadyQueueSJF_head->nowsize += 1;
        
    return True;
}


TCB QpopSJF() {
    if(!ReadyQueueSJF_head->nowsize) 
        return NULL_TCB;

    ReadyQueueSJF* Next = ReadyQueueSJF_head->next;
    TCB tmp = Next->data;
    ReadyQueueSJF_head->next = Next->next;
    --(ReadyQueueSJF_head->nowsize);
    return tmp;
}

Bool QfullSJF(const QUEUE* queue) {
    if(queue->nowsize == queue->maxsize) 
        return True;
    else
        return False;
}

Bool QemptySJF(const QUEUE* queue) {
    if(queue->nowsize == 0) 
        return True;
    else
        return False;
}

unsigned long QlenSJF(const QUEUE* queue) {
    return queue->nowsize;
}

void display_ReadyQueueSJF(ReadyQueueSJF* queue) {
    ReadyQueueSJF* tmp = queue;
    myPrintf(0x7, "\nReadyQueueSJF:\n");
    while(tmp != 0) {
        myPrintf(0x7, "tid: %d pri: %d \n", tmp->data.tid,tmp->data.params.exeTime);
        tmp = tmp->next;
    }
}


