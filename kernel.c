/**
 * naas v1.0 - 24-apr-2013
 * Author: Emilio Guernik - Argentina
 * License: MIT
 * Microcontroler: Atmel atTiny2313
 *
 * Not just Another AVR Scheduler: teeny tiny little tasker made for AVR microcontrollers (particulary atitny2313)
 * Firmware and primitive layers are in same file for simplification.
 * As primitive layer is properly separated from firmware, it should be easy to port to another microcontroller.
 *
 * See main.c for a usage example.
 *
 * USAGE:
 *
 * 0) Configure the TICK macro to desired kernel tick value. (default = 250). This means that the task list will revised every 250us
 *
 * Note: minimun safe value of TICK is 200 us. This is due to the time that takes to execute the Timer interrupt.
 * Take in consideration that if you add a lot of tasks,
 *
 * 1) Define the task using TASK macro and a task number (usually a macro defined number).
 *
 * 2) Initialize femtoTasker with fTaskerSetUp(); this will initialize
 * necesary hardware resources as timer1 and corresponding IRQs and setup the tasks
 * buffer.
 *
 * 3) Add the function to the task list using ADDTASK macro
 *  IE: ADDTASK(task_n,task_ticks,sng_shot)
 *              * task_n->task number;
 *              * task_ticks->number of kernel ticks after the task will be fired.
 *              * sng_shot: may be SINGLE_SHOT or NO_SINGLE_SHOT. The first will call the task every "tsk_timer" milliseconds,
 *                  The second will call the task once and set it to inactive state.
 *  For example, a task defined with a tick value of 1, will be fired every TICK amount of uSeconds (default is 250 microSeconds)
 *
 *
 * 5) see the example main.c, add KERNELTICK(); macro to your while(1) or for(;;) main loop.
 * TODO: semaphores (see utask)
 *
 *sadiff*/
#include "kernel.h"
#define TRUE 1
#define TICK 1000 //tick time value in micro seconds
#define CTC_VAL (F_CPU/(1/(TICK*(0.000001))))-1
//TODO: task that accepts parameters


volatile task taskList[MAX_TASKS];
volatile uint8_t computeTimersFlag = 0;
static uint8_t free_task_id = 0; //Module global variable (just this file).

/*************************************************/
/**                  Firmware Layer              */
/*************************************************/
void _fw_timer1_start( void )
{
    /**start timer1 with no prescaling*/
    TCCR1B |= (1 << CS10);
}
//@TODO:  hacer algo
void _fw_timer1_stop( void )
{
    TCCR1B &= ~(1 << CS10);
}

void _fw_timer1_ctc_setup (int compValue)
{
    /*Timer1 CTC mode*/
    TCCR1B |= (1 << WGM12);

    /*Enable CTC interrupt*/
    TIMSK |= (1 << OCIE1A); //OCIE==OutputCompareInterruptEnable

    /*Enable global interrupts*/
    sei();

    /*CTC compare value to compValue*/
    OCR1A = compValue;
}

ISR (TIMER1_COMPA_vect)
{
   cli();
   computeTimersFlag = 1;
   sei();
}
/* **************End of firmware layer****************************** */
/* ***************************************************************** */



/*************************************************/
/*                  Primitives                   */
/*************************************************/
void taskerSetUp( void )
{
    _fw_timer1_ctc_setup (CTC_VAL); //interrupts every TICK micro seconds.
    _fw_timer1_start();
}



/**
@brief Add new task to task list
Add a new task to list, make it active, load default interval, and return a pointer to the task.
@param  funcPtr     pointer to function that takes a task* as parameter and returns nothing
*/
task* _addTask( void (*funcPtr)(task* this) )
{
	task* new_task = &taskList[free_task_id];

    if (free_task_id == MAX_TASKS)
    {
        return NULL; //No empty task available, return NULL;
    }
    else
    {
        taskList[free_task_id]->stauts = TASK_ACTIVE;
        taskList[free_task_id]->_reload_ticks = TASK_DEFAULT_INTERVAL;
        taskList[free_task_id]->ticks = TASK_DEFAULT_INTERVAL;
        taskList[free_task_id]->singleShot = NO_SINGLE_SHOT;
        taskList[free_task_id]->fPtr = funcPtr;
        free_task_id++;
        return new_task;/*pointer to current task*/;
    }
}

void _taskDeactivate ( void (*ptr)(task* this) )
{
    int i;
    for (i=0;i<MAX_TASKS;i++)
    {
        if (taskList[i].funcPtr == ptr)
        {
            taskList[i].stauts=TASK_STOP;
            break;
        }
    }
}

void _taskActivate ( void (*ptr)(task* this) )
{
    int i;
    for (i=0;i<MAX_TASKS;i++)
    {
        if (taskList[i].funcPtr == ptr)
        {
            taskList[i].stauts=TASK_ACTIVE;
            break;
        }
    }
}


/**
 * This function iterates the task list and fires the callback function in case the
 * corresponding timer has expired.
 * If it was not a single shot task, refill the counter with the initial timer value and
 * set it to active state again. If it was a single shot task, set it to inactive state.
 **/
void _doEvents ( void )
{
	int i = 0;
    for (i = 0; i <= MAX_TASKS; i++)
	{
		if ( taskList[i].active == 1)
		{
			if	( taskList[i].expired == 1)
			{
		        taskList[i].fPtr (); /**Call the task function*/
                taskList[i].active 	= taskList[i].singleShot; /**if task is a singleshot, we set status to inactive*/
                taskList[i].expired = 0;
                //taskList[i].fPtr = 0;
			}
		}
	}
}//doEvents? Hmm that sounds familiar


/**
 * Iterate the task list, reduce the timer by 1 tick
 * and set the flag to "expired" if necessary.
 **/
// void computeTimers ( void )
void kerneltick( void )
{
    if (computeTimersFlag)
    {
        int i = 0;
        computeTimersFlag = 0;
        for ( i = 0; i <= MAX_TASKS; i++)
        {
            if ( taskList[i].active == 1 )
            {
                taskList[i].ticks--;
                if ( taskList[i].ticks == 0 )
                {
                    taskList[i].expired = 1;
                }
            }
        }
        _doEvents(); /**Iterate task list and call due tasks*/
    }
}
/* **************End of primitives layer**************************** */
/* ***************************************************************** */