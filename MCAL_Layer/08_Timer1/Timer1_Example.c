#if 0

/* tick = (prescaler * counts)/frecuancy */

#include "Timer1_Interface.h"

uint16 counts = 0;
    
MTimer1_Init(T1_NORMAL,OC1A_DISCONNECTED,OC1B_DISCONNECTED);

MTimer1_SetPreloadValue(100);
MTimer1_SetOCR1AValue(150);
MTimer1_SetOCR1BValue(200);

MTimer1_Star(T1_PRESCALER_1024);

MTimer1_Read_Counts(&counts);


ISR(TIMER1_CAPT_vect)
{
    
}

ISR(TIMER1_COMPA_vect)
{
    
}

ISR(TIMER1_COMPB_vect)
{
    
}

ISR(TIMER1_OVF_vect)
{
    
}

#endif
