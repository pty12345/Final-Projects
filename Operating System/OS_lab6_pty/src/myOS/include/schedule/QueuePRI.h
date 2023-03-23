#ifndef __QUEUEPRI_H__
#define __QUEUEPRI_H__

#include "task.h"

typedef struct ReadyQueuePRI {
    TCB data;
    struct ReadyQueuePRI* next;
    int nowsize;
    int maxsize;
} ReadyQueuePRI;


extern ReadyQueuePRI *ReadyQueuePri_head; 

extern void QInitPRI(int ReadyQueue_MaxLen); 

extern void display_readyqueuePRI(ReadyQueuePRI* queue);
extern Bool QpushPRI(ReadyQueuePRI* queue, TCB tcb);

extern Bool QemptyPRI(const ReadyQueuePRI* queue);
extern TCB QpopPRI();
extern unsigned long QlenPRI(const ReadyQueuePRI* queue);


#endif