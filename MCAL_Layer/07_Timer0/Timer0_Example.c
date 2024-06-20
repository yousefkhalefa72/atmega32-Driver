#if 0

/* tick = (prescaler * counts)/frecuancy */

#include "Timer0_Interface.h"

uint8 counts = 0;
    
MTimer0_Init(T0_NORMAL,OC0_DISCONNECTED);

MTimer0_SetPreloadValue(0);
MTimer0_SetOCR0Value(100);

MTimer0_Star(T0_RISING_EDGE_on_T0);

MTimer0_Read_Counts(&counts);


ISR(TIMER0_COMP_vect)
{
    
}

ISR(TIMER0_OVF_vect)
{
    
}

#endif