#ifndef __QUEUEFIFO_H__
#define __QUEUEFIFO_H__

#include "task.h"

typedef struct ReadyQueueFIFO {
    TCB* data;
    unsigned long head, tail;
    unsigned long maxsize;
    unsigned long nowsize;
} ReadyQueueFIFO;


extern ReadyQueueFIFO ReadyQueueFF; 

extern void QInit(ReadyQueueFIFO* queue, const unsigned long MaxQueueLen);
//Initial Queue

extern void display_readyqueueFIFO(const ReadyQueueFIFO* queue);

// TCB qback(const ReadyQueueFIFO* queue);
// TCB qfront(const ReadyQueueFIFO* queue);

extern Bool Qpush(ReadyQueueFIFO* queue, TCB tcb);
extern Bool Qfull(const ReadyQueueFIFO* queue);
extern Bool Qempty(const ReadyQueueFIFO* queue);
extern TCB Qpop(ReadyQueueFIFO* queue);
extern unsigned long Qlen(const ReadyQueueFIFO* queue);


#endif