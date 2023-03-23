#include "../../include/schedule/QueueFIFO.h"
#include "../../include/myPrintk.h"

#define QUEUE ReadyQueueFIFO


ReadyQueueFIFO ReadyQueueFF; 

void QInit(QUEUE* queue,const unsigned long MaxQueueLen) {
    queue->maxsize = MaxQueueLen;
    queue->data = (TCB* ) kmalloc(sizeof(TCB) * queue->maxsize);
    queue->head = 0; //point to the first element
    queue->tail = 0; //point to the last element's next place
    queue->nowsize = 0;
}

Bool Qpush(QUEUE* queue, TCB tcb) {
    if(queue->nowsize == queue->maxsize) 
        return False; // The queue is full;

    unsigned long next_pos = queue->tail;
    *(queue->data + next_pos) = tcb;

    queue->tail = (queue->tail + 1) % queue->maxsize ;
    queue->nowsize += 1;
        
    return True;
}


TCB Qpop(QUEUE* queue) {
    if(!queue->nowsize) 
        return NULL_TCB;

    TCB tmp = queue->data[queue->head];
    queue->head = (queue->head + 1) % queue->maxsize ;
    queue->nowsize -= 1;
    return tmp;
}

Bool Qfull(const QUEUE* queue) {
    if(queue->nowsize == queue->maxsize) 
        return True;
    else
        return False;
}

Bool Qempty(const QUEUE* queue) {
    if(queue->nowsize == 0) 
        return True;
    else
        return False;
}

unsigned long Qlen(const QUEUE* queue) {
    return queue->nowsize;
}

void display_readyqueueFIFO(const ReadyQueueFIFO* queue) {

   
    if (queue->nowsize == 0) 
        return;

    myPrintf(0x7,"ReadyQueue:\n");
    unsigned long pos = queue->head;
    while (pos != queue->tail) {
        // if(queue->data[pos].tid == 5 || queue->data[pos].tid == 6 )
            // PrintTCB(queue->data[pos]);
        myPrintf(0x7,"%d ",queue->data[pos].tid);
        pos = (pos + 1) % queue->maxsize;
    }
     myPrintf(0x7, "\nreadyqueueFIFO:%d\n",queue->nowsize);
}
