/**
 * femtoTasker v0.4 - 24-apr-2013
 * Author: Emilio Guernik
 * License: MIT
 * Microcontroler: Atmel atTiny2313
 *
 * FemtoTasker: teeny tiny little tasker made for AVR microcontrollers (particulary atitny2313)
 * Firmware and primitive layers are in same file for simplification.
 *
 * Copy femtotasker.c and femtotasker.h to your project folder, and see the example main program.
 *
 * Good luck!
 *
 **/

shavr
yaas


Todo proyecto debe estar correctamente estructurado, incluso los pequeños. Para aquellos proyectos, un RTOS completo, o incluso un shceduler preventivo con cambios de contexto es demasiado. Surge entonces la nececidad de un shceduler mas simple, cooperativo. No pude encontrar ninguno en la web lo suficientemente claro y prolijo, así que hice uno yo mismo.

Naas es un shceduler cooperativo escrito con codigo claro y sin vueltas. Simplemente hace lo que dice.


Uso:

Agregar una tarea al scheduler es tan simple como ejecutar:

ADDTASK(taskname,interval,singleshot);
*taskname es, evidentemente, el nombre de la tarea
*interval define cada cuantos kernel ticks el shceduler llama a la tarea
* sng_shot: may be SINGLE_SHOT or NO_SINGLE_SHOT. The first will call the task every "tsk_timer" milliseconds,
                  The second will call the task once and set it to inactive state.

En el main, debemos recordar llamar al shceduler:
while (1)
{
	kerneltick();
}

Esta acción recorre la lista de tareas, verificando si alguna venció y neceista ejecutarse.