/**
 * naas v1.0 - 05-dic-2013
 * Author: Emilio Guernik - Buenos Aires- Argentina
 * University: UTN BA
 * License: MIT
 * File: main.c
**/

// #include <avr/io.h>
// #include <avr/interrupt.h>
#undef F_CPU
#define F_CPU   8000000UL
#include <util/delay.h>

#include "main.h"
#include "kernel.h"

#define LED_0 D,(PD2)


// Example of intended usage (no semaphores yet).
void task1 (task* this)
{
    switch (this->state_machine.state)
    {
        case 0:
            SET_PIN(LED_0);
            task_sleep(this,MS(1000)); //task will sleep for 40 msec, and then 'state' will automatically increment by 1,
            break;
        case 1:
            CLR_PIN(LED_0);
            task_sleep(this,MS(1000));
            this->state_machine.next_state = 0; //We need to tell the dispatcher that next state is state A, instead of B+1
            break;
    }

}
void task2 (task* this)
{
    //    if GET_PIN(LED_0)
    // {
    //     CLR_PIN(LED_0);
    // }
    // else
    // {
    //     SET_PIN(LED_0);
    // }
    SET_PIN(LED_0);
}

int main( void )
{
   SET_OUT (LED_0);
    /*PB4 pullup on*/
    //SET_PIN(PORTD,0);
    taskerSetUp();
    // ADDTASK(TASK_SOFT_PWM,15000,NO_SINGLE_SHOT);

    add_task(task2);





    while(1)
    {
        kernelTick(); //TODO: taskdispatch();
    }
}

