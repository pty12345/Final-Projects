#include "../myOS/userInterface.h"   //interface from kernel

#include "shell.h"
#include "memTestCase.h"
#include "taskTestCase.h"
void myMain(void) {

    myPrintf(0x7,"Into myMain\n");
    initShell();
    memTestCaseInit();
    
    enum {
        Pri,
        Arr,
        Exe
    };

    int shell_id = createTsk(startShell);
	int t1_id = createTsk(TaskTest_1);
    int t2_id = createTsk(TaskTest_2);
    int t3_id = createTsk(TaskTest_3);
    int t4_id = createTsk(TaskTest_4);
    int t5_id = createTsk(TaskTest_5);


    // 2 -> 3 -> 1 -> 4 -> 5
    setPara(Pri,3,t1_id);
    setPara(Pri,1,t2_id);
    setPara(Pri,2,t3_id);
    setPara(Pri,4,t4_id);
    setPara(Pri,6,t5_id);
    setPara(Pri,16,shell_id); // Lowest priority
    //display_NewQueue();


    // 1 -> 3 -> 2 -> 4 -> 5
    setPara(Exe,2,t1_id);
    setPara(Exe,5,t2_id);
    setPara(Exe,4,t3_id);
    setPara(Exe,7,t4_id);
    setPara(Exe,8,t5_id);
    setPara(Exe,16,shell_id); // Longest job

    tskStart_By_ID(t1_id);
    tskStart_By_ID(t2_id);
    tskStart_By_ID(t3_id);
    tskStart_By_ID(t4_id);
    tskStart_By_ID(t5_id);

    //display_ReadyQueue();

    tskStart_By_ID(shell_id);
   

}
