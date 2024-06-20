#if 0

#include "Button_Interface.h"

 button_t but1 ={.pin.port=PORTA_INDEX, .pin.pin=PIN0_INDEX, .type=BUTTON_ACTIVE_LOW};
 button_state_t but1_status;
    
HButton_Initialize(&but1);

HButton_Internal_PullUp(&but1);

HButton_state(&but1,&but1_status);

if(but1_status == BUTTON_PRESSED)
    /* button pressed */
else
    /* button release */
    
#endif