/**
 * naas v1.0 - 05-dic-2013
 * Author: Emilio Guernik - Buenos Aires- Argentina
 * University: UTN BA
 * License: MIT
 * File: main.c
**/

#include <avr/io.h>
#include <avr/interrupt.h>
#undef F_CPU
#define F_CPU   8000000UL
#include <util/delay.h>

#include "main.h"
#include "kernel.h"




int main( void )
{
    //SET_OUT (LED_0);
    /*PB4 pullup on*/
    //SET_PIN(PORTD,0);
    taskerSetUp();
    //ADDTASK(TASK_SOFT_PWM,15000,NO_SINGLE_SHOT);

    //add_task(task1);


    while(1)
    {
        kerneltick(); //TODO: taskdispatch();
    }
}


//Example of intended usage (no semaphores yet).
// void task1 (task* this)
// {
//     switch (t->state_machine.state)
//     {
//         case A:
//             led = 1;
//             task_sleep(this,MS(40)); //task will sleep for 40 msec, and then 'state' will automatically increment by 1,
//             break;
//         case B:
//             led = 0;
//             this->state_machine.next_state = A; //We need to tell the dispatcher that next state is state A, instead of B+1
//             task_sleep(this,MS(40));
//             break;
//     }

// }