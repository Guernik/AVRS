#ifndef NAAS_H
// INCLUDES
#include <avr/io.h>
#include <avr/interrupt.h>


//*****User config starts here*****
#define MAX_TASKS 10
#define TICK 1000 //timer interrupt in u seconds, used for presicion counters and task ticks
#define TASK_DEFAULT_INTERVAL 10 * (TICK) //default task tick. Task list will be revised according to this value
//*****User config ends here*****



//MACROS
#define SINGLE_SHOT 0    //If we define single_shot as 0 here, we can save an If statement later in doEvents.
#define NO_SINGLE_SHOT 1

#define MS(msec) ( (msec)*1000/(TICK) )  //Returns number of ticks equivalent to "msec" miliseconds
#define ADD_TASK(task_n,singleshot) ADD_TASK_INTERVAL(task_n,TASK_DEFAULT_INTERVAL,singleshot)
#define ADD_TASK_INTERVAL(task_n,time,singleshot) _addTask(task_n,time,singleshot,task_##task_n )
#define TASK(task_n) void task_##task_n( void )
#define TASK_STOP(task_n) _taskDeactivate(task_n)
#define TASK_START(task_n) _taskActivate(task_n)
#define TICKS(tks) (((long)tks)*TICK)/1000L
/**Task Status**/
#define TASK_ACTIVE 0
#define TASK_ASLEEP 1
#define TASK_STOP 2


//Remove this line in next commit
//#define KERNELTICK() if (computeTimersFlag){ computeTimers(); doEvents();}

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

    struct fsm
    {
        int state;
        int next_state;

    };
    typedef struct _task
    {
        int stauts;
        long _reload_ticks;
        long ticks;
        int singleshot;
        void (*fPtr) (struct _task* this);
        struct fsm state_machine;
    }task;

//PROTOTYPES
    //Firmware (internal usaage)
    void _fw_timer1_start( void );
    void _fw_timer1_stop ( void );
    void _fw_timer1_ctc_setup ( int compValue );
    //Primitives
        /**External*/
        void taskerSetUp( void );
        /**Internal*/
        void _doEvents ( void );
        void _addTask ( int taskN, long ms, int singleShot, void (*funcPtr)(void)) ;
        //@TODO: remove this line in next commit
        // void computeTimers(void;)
        void _taskDeactivate (int task_n);
        void _taskActivate (int task_n);
#define NAAS_H
#endif