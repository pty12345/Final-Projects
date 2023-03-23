#include "../../include/schedule/task.h"

unsigned long stack_size = 0x100;
int tid_count = 0; //tid_value
NewTask_list* NewTask_list_head;


void PrintTCB(TCB tsk) {
    myPrintf(0x7,"TSK_id:%x\n",tsk.tid);
    myPrintf(0x7,"TSK_sp:%x\n",*tsk.sp);
    myPrintf(0x7,"TSK_state:%x\n",tsk.state);
     for(int i = 1;i <= 10;i++) 
         myPrintf(0x7,"TSK_stack[%d]:%x\n",i,tsk.sp[i]);

    // myPrintf(0x7,"Main_enter:%x\n",myMain);   
    // myPrintf(0x7,"Idle_enter:%x\n",idleTsk);  
    myPrintf(0x7,"\n");   
}

void stack_init(unsigned long **stk, void (*task)(void)) { 
    *(*stk)-- = (unsigned long)tskEnd; // CS 

    *(*stk)-- = (unsigned long)task; // eip 

    // pushf 
    *(*stk)-- = (unsigned long)0x0202; // flag registers 
  
    // pusha 
    *(*stk)-- = (unsigned long)0xAAAAAAAA; // eax 
    *(*stk)-- = (unsigned long)0xCCCCCCCC; // ecx 
    *(*stk)-- = (unsigned long)0xDDDDDDDD; // edx 
    *(*stk)-- = (unsigned long)0xBBBBBBBB; // ebx 
    *(*stk)-- = (unsigned long)0x44444444; // esp 
    *(*stk)-- = (unsigned long)0x55555555; // ebp 
    *(*stk)-- = (unsigned long)0x66666666; // esi 
    **stk = (unsigned long)0x77777777; // edi 
}

void setPara(unsigned long attr, unsigned long value, unsigned long id){
    NewTask_list *tmp;   
    tmp = NewTask_list_head->next;
    
    while (tmp != 0){
        if (tmp->data.tid == id)  break;

        tmp = tmp->next;
    }

    if (tmp == 0)
        return;

    //myPrintf(0x7,("arrhere!"));
    switch (attr)
    {
        case 0:
            tmp->data.params.priority = value;
            break;
        case 1:
            tmp->data.params.arrTime= value;
            break;
        case 2:
            tmp->data.params.exeTime = value;        
            break;

        default:
            break;
    }
    

    return;
}

