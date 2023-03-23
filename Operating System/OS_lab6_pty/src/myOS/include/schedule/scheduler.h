#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "QueueFIFO.h"
#include "QueuePRI.h"
#include "QueueSJF.h"
#include "task.h"

extern unsigned long ReadyQueue_MaxLen;
// Limitation of ReadyQueue's length
// Main memory requirement

typedef enum ScheduleWay {
    FCFS,
    SJF,
    PRI
}ScheduleWay;

extern ScheduleWay SW;
extern Bool ReadyQueueEmpty;

void taskManager_init();
void taskReadyQueue_init();
TCB nextRunningTsk();

int createTsk(void (*tskBody)(void));
void destroyTsk(int tsk_sp);

Bool tskStart_By_ID(int tsk_id);
Bool tskStart(TCB tsk);

void New_to_ReadyQueue(TCB tsk);

void display_NewQueue();

void display_ReadyQueue();
Bool Check_ReadyQueue();

#endif