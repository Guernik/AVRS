#ifndef MYHEADER_H
    /*Logic of inputs, uncomment one of two*/
    #define ACTIVE_LOW
  //#define ACTIVE_HIGH

    /*defines the if the buttons are active high or active low logic*/
    #ifdef  ACTIVE_LOW
        #define ACTIVE 0
        #define INACTIVE 1
    #else
        #define ACTIVE      1
        #define INACTIVE    0
    #endif


    #define CLR_PIN(v) _CLR_PIN(v)
    #define _CLR_PIN(port,pin) (PORT##port) &= ~ (0x01 << (pin))

    #define SET_PIN(v) _SET_PIN(v)
    #define _SET_PIN(port,pin) (PORT##port) |=   (0x01 << (pin))

    #define SET_IN(v)  _SET_IN(v)
    #define _SET_IN(ddr,pin)  (DDR##ddr) &= ~ (0x01 << (pin))

    #define SET_OUT(v) _SET_OUT(v)
    #define _SET_OUT(ddr,pin) (DDR##ddr) |=   (0x01 << (pin))

    #define GET_PIN(v) _GETPIN(v)
    #define _GETPIN(port,pin) (((PORT##port) & (0x01 << (pin))) >> (pin) )
    #define __GETPIN(port,pin) (((port) & (0x01 << (pin))) >> (pin) )

    #define GLUE(a,b) a##b

    #define FALSE 0
    #define TRUE 1

#define MYHEADER_H
#endif
