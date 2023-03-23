#ifndef TASK_H
#define TASK_H

#include "../malloc.h""

typedef enum Bool {
    False,
    True
}Bool;

typedef enum State {
    WAITING,
    READY,
    RUNNING,
    NEW,
    TERMINATED
} State;

typedef struct tskPara {
    unsigned priority;
    unsigned arrTime;
    unsigned exeTime;
} tskPara;

typedef struct TCB {
    int tid; 
    State state;
    unsigned long* sp; // stack point
    unsigned long stk_top; // stack point
    tskPara params; //parameter list
} TCB;

#define NULL_TCB ((TCB){.tid = -1, .state = READY, .sp = 0, .params = (tskPara){0, 0, 0}})

typedef struct NewTask_list {
    TCB data;                    // TCB_value
    struct NewTask_list* next;
} NewTask_list;                 //NewTask_Set

extern void setPara(unsigned long attr, unsigned long value, unsigned long id);

extern NewTask_list* NewTask_list_head;

extern void PrintTCB(TCB tcb);

extern unsigned long stack_size ;
extern int tid_count ;//tid_value

extern void stack_init(unsigned long **stk, void (*task)(void));
extern void tskEnd();


#endif