#include "../../include/schedule/QueuePRI.h"
#include "../../include/myPrintk.h"

#define QUEUE ReadyQueuePRI


ReadyQueuePRI* ReadyQueuePri_head; 

void QInitPRI(int ReadyQueue_MaxLen) {
    ReadyQueuePri_head = (ReadyQueuePRI* )kmalloc(sizeof(ReadyQueuePRI));
    ReadyQueuePri_head->nowsize = 0;
    ReadyQueuePri_head->next = 0;
    ReadyQueuePri_head->maxsize = ReadyQueue_MaxLen;
    myPrintf(0x7,"InitQueueMaxsize:%d\n",ReadyQueuePri_head->maxsize);
}

Bool QpushPRI(QUEUE* queue, TCB tcb) {

    ReadyQueuePRI* prev = ReadyQueuePri_head;

    while(prev->next != 0 && prev->next->data.params.priority <= tcb.params.priority) {
        prev = prev->next;
    }


    ReadyQueuePRI* tmp = (ReadyQueuePRI* )kmalloc(sizeof(ReadyQueuePRI));

    tmp->data = tcb;
    tmp->next = prev->next;

    prev->next = tmp;
    ReadyQueuePri_head->nowsize += 1;
        
    return True;
}


TCB QpopPRI() {
    if(!ReadyQueuePri_head->nowsize) 
        return NULL_TCB;

    ReadyQueuePRI* Next = ReadyQueuePri_head->next;
    TCB tmp = Next->data;
    ReadyQueuePri_head->next = Next->next;
    --(ReadyQueuePri_head->nowsize);
    return tmp;
}

Bool QfullPRI(const QUEUE* queue) {
    if(queue->nowsize == queue->maxsize) 
        return True;
    else
        return False;
}

Bool QemptyPRI(const QUEUE* queue) {
    if(queue->nowsize == 0) 
        return True;
    else
        return False;
}

unsigned long QlenPRI(const QUEUE* queue) {
    return queue->nowsize;
}

void display_readyqueuePRI(ReadyQueuePRI* queue) {
    ReadyQueuePRI* tmp = queue;
    myPrintf(0x7, "\nreadyqueuePRI:\n");
    while(tmp != 0) {
        myPrintf(0x7, "tid: %d pri: %d \n", tmp->data.tid,tmp->data.params.priority);
        tmp = tmp->next;
    }
}


