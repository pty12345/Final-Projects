#include "vga.h"
#include "myPrintk.h"
#include "interrupt.h"
#include "tick.h"
#include "wallClock.h"
#include "mem.h"
#include "../include/schedule/scheduler.h"

void pressAnyKeyToStart(void) {
	myPrintk(0x3, "Prepare uart device\n");
	myPrintk(0x3, "Then, press any key to start...\n");

	uart_get_char();
}

void Set_Model() {

    SW = SJF;

}

void myMain(void);

void osStart(void) {

    disable_interrupt();
    clear_screen();
    pressAnyKeyToStart();

    clear_screen();
    init8259A();
    init8253();
    init_tick();
    init_wall_clock(0, 0, 0);
    pMemInit();
    enable_interrupt();

    Set_Model();

    taskManager_init();
    

    myPrintk(0x2, "Starting the OS...\n");
    //myMain();
    myPrintk(0x2, "Stop running... shutdown\n");

    while(1); 
}
