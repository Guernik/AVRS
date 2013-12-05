/**
 * femtoTasker v0.4 - 24-apr-2013
 * Author: Emilio Guernik - Argentina
 * License: AS IS
 * Microcontroler: Atmel atTiny2313
 *
 * readKey(hw_port,hw_pin): usefulll primitive to read a press-unpress button cycle (simple state machine)
 *
 **/


#include <avr/io.h>

#include "PR_BTN.h"
#include "myHeader.h"

#define PUSHBTN (PINB), (PB4)



char _fw_getKey (int hw_port, int hw_pin)
{
    if (  __GETPIN(hw_port, hw_pin) == ACTIVE )
    {
        return ACTIVE; // button pushed
    }
    return INACTIVE;
}

/*function to read a button press-unpress cycle*/
char readKey (int hw_port, int hw_pin)
{
    static char fKeyPressed;
    //static char fKeyCycle;

    if (_fw_getKey (hw_port,hw_pin) == ACTIVE)
    {
        if (fKeyPressed == 0 )
        {
            fKeyPressed = 1;
        }
    }
    if (fKeyPressed == 1 && (_fw_getKey(hw_port,hw_pin) == INACTIVE) )
    {
        fKeyPressed = 0;
        //fKeyCycle == 1;
        return 1;
    }

    return 0;
}
