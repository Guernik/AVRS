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


extern volatile struct _st_tasker taskList[MAX_TASKS]; //TODO: fix this!
volatile int computeTimersFlag = 0;


int main( void )
{
    SET_OUT (LED_0);
    /*PB4 pullup on*/
    //SET_PIN(PORTD,0);
    taskerSetUp();
    ADDTASK(TASK_SOFT_PWM,15000,NO_SINGLE_SHOT);


    while(1)
    {
        KERNELTICK();
    }
}

