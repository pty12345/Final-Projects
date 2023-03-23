#ifndef __QUEUESJF_H__
#define __QUEUESJF_H__

#include "task.h"

typedef struct ReadyQueueSJF {
    TCB data;
    struct ReadyQueueSJF* next;
    int nowsize;
    int maxsize;
} ReadyQueueSJF;


extern ReadyQueueSJF *ReadyQueueSJF_head; 

extern void QInitSJF(int ReadyQueue_MaxLen); 

extern void display_ReadyQueueSJF(ReadyQueueSJF* queue);
extern Bool QpushSJF(ReadyQueueSJF* queue, TCB tcb);

extern Bool QemptySJF(const ReadyQueueSJF* queue);
extern TCB QpopSJF();
extern unsigned long QlenSJF(const ReadyQueueSJF* queue);


#endif