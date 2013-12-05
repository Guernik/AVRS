#ifndef FEMTO_TASKER_H
// INCLUDES
#include <avr/io.h>
#include <avr/interrupt.h>

//MACROS
#define MAX_TASKS 10
#define SINGLE_SHOT 0    //If we define single_shot as 0 here, we can save an If statement later in doEvents.
#define NO_SINGLE_SHOT 1

#define ADDTASK(task_n,time,singleshot) _addTask(task_n,time,singleshot,task_##task_n )
#define TASK(task_n) void task_##task_n( void )
#define TASK_DEACTIVATE(task_n) _taskDeactivate(task_n)
#define TASK_ACTIVATE(task_n) _taskActivate(task_n)
#define TICKS(tks) (((long)tks)*TICK)/1000L

#define KERNELTICK doEvents();\
        if (computeTimersFlag) computeTimers  //don't forget the (); when calling kerneltick!

//STRUCTS
    struct _st_tasker
    {
        int active;
        int expired;
        long _reload_ticks;
        long ticks;
        int singleShot;
        void (*fPtr) (void);
    };

//PROTOTYPES
    //Firmware (internal usaage)
    void _fw_timer1_start( void );
    void _fw_timer1_stop ( void );
    void _fw_timer1_ctc_setup ( int compValue );
    //Primitives
    void taskerSetUp( void );
    void doEvents ( void );
    void _addTask ( int taskN, long ms, int singleShot, void (*funcPtr)(void)) ;
    void computeTimers(void);
    void _taskDeactivate (int task_n);
    void _taskActivate (int task_n);
#define FEMTO_TASKER_H
#endif