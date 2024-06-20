#if 0

/* tick = (prescaler * counts)/frecuancy */

#include "Timer2_Interface.h"

uint8 counts = 0;
    
MTimer2_Init(T2_NORMAL,OC2_DISCONNECTED);

MTimer2_SetPreloadValue(0);
MTimer2_SetOCR2Value(100);

MTimer2_Star(T0_RISING_EDGE_on_T0);

MTimer2_Read_Counts(&counts);


ISR(TIMER2_COMP_vect)
{
    
}

ISR(TIMER2_OVF_vect)
{
    
}

#endif
