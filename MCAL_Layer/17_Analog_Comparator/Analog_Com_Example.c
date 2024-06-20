#if 0

#include "Analog_Com_Interface.h"

MAnalogComparator_SetInterruptMode(INT_ON_RISING_EDGE);
MAnalogComparator_Init(NEG_IN_AIN1,ICU_NOT_CONNECT);

MANA_COMP_ENABLE();

if(MANA_COMP_OUTREAD() == 0)
{
    /*AIN0 < NEG_PIN*/
}
else
{
    /*AIN0 > NEG_PIN*/
}
    
/* depend on (MAnalogComparator_SetInterruptMode)*/
ISR(ANA_COMP_vect)
{
    
}

#endif
