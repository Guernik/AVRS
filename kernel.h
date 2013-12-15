#ifndef NAAS_H
// INCLUDES
#include <avr/io.h>
#include <avr/interrupt.h>


//*****User config starts here*****
#define MAX_TASKS 6
#define FSM_AUTOINCREMENT //state of fsm's will autoincrement every time the task is called. Comment this line to prevent that.
#define TICK 100000 //timer interrupt in u seconds, used for presicion counters and task ticks
#define TASK_DEFAULT_INTERVAL 10 * (TICK) //default task tick. Task list will be revised according to this value
//*****User config ends here*****



//MACROS
#define SINGLE_SHOT 0    //If we define single_shot as 0 here, we can save an If statement later in doEvents.
#define NO_SINGLE_SHOT 1

#define MS(msec) ( (unsigned int) (((msec)*1000L)/(TICK)) )  //Returns number of ticks equivalent to "msec" miliseconds
#define TICKS(tks) (((long)tks)*TICK)/1000L
// #define ADD_TASK(task_n,singleshot) ADD_TASK_INTERVAL(task_n,TASK_DEFAULT_INTERVAL,singleshot)
// #define ADD_TASK_INTERVAL(task_n,time,singleshot) _addTask(task_n,time,singleshot,task_##task_n )
// #define TASK(task_n) void task_##task_n( void )
// #define TASK_STOP(task_n) _taskDeactivate(task_n)
// #define TASK_START(task_n) _taskActivate(task_n)
/**Task Status**/
#define TASK_ACTIVE 0
#define TASK_ASLEEP 1
#define TASK_STOP 2
#define TASK_EXPIRED 3


//Remove this line in next commit
//#define KERNELTICK() if (computeTimersFlag){ computeTimers(); doEvents();}

//STRUCTS

    struct fsm
    {
        uint8_t state;
        uint8_t next_state;

    };
    typedef struct _task
    {
        uint8_t status;
        uint32_t _reload_ticks;
        uint32_t ticks;
        uint32_t sleep_ticks;
        uint8_t singleshot;
        void (*func_ptr) (struct _task* this);
        struct fsm state_machine;
    }task;

//PROTOTYPES
    //Firmware (internal usaage)
    void _fw_timer1_start( void );
    void _fw_timer1_stop ( void );
    void _fw_timer1_ctc_setup ( uint16_t compValue );
    //Primitives
        /**External*/
        void task_sleep( task* this, uint16_t ticks);
        void taskerSetUp( void );
        void kernelTick( void );
        /**Internal*/
        void _doEvents ( void );
        task* add_task ( void (*func_ptr)(task* this)) ;
        void _taskDeactivate (void (*func_ptr)(task* this));
        void _taskActivate (void (*func_ptr)(task* this));
#define NAAS_H
#endif