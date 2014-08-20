AVRS
==============
AVRS es un scheduler para la familia 8 bits de atmel, particularmente ATTiny2313, pero facilmente portable.

Características
---
 - sintaxis simple
 - tamaño reducido
 - hace lo que promete

Ejemplo
--
```c
TASK(1){
    if GET_PIN(LED_0)
    {
        CLR_PIN(LED_0);
    }
    else
    {
        SET_PIN(LED_0);
    }
}
int main( void ){
    SET_OUT (LED_0);
    taskerSetUp();
    ADDTASK(1,10000,RUN_FOREVER);
    while(1)
    {
        KERNELTICK();
    }
}
```
Versión
---
1.1f
Autor
---
>Emilio Nahuel Guernik

>UTN.BA, Ing. Electrónica

Roadmap
---
 - V2.0 : implementar maquina de estados finitos, ejemplo: (ver branch "task_sleep")

```C
void task1 (task* this)
{
    switch (this->state_machine.state)
    {
        case 0:
            SET_PIN(LED_0);
            task_sleep(this,MS(1000));
            /**task will sleep for 40 msec, and then 'state' will automatically
            increment by 1*/
            break;
        case 1:
            CLR_PIN(LED_0);
            task_sleep(this,MS(1000));
            this->state_machine.next_state = 0;
            /**We need to tell the dispatcher that next state is state A,
            instead of B+1 */
            break;
    }

}
```
 

