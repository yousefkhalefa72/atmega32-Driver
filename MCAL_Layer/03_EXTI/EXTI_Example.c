#if 0

#include "EXTI_Interface.h"

pin_t INT0_pin = {.port=PORTD_INDEX, .pin=PIN2_INDEX, .direction=DIO_DIRECTION_INPUT};
MDIO_SetPinDirection(&INT0_pin);

MEXTI_SenseControl(EXT_INT0,LOW_LEVEL);
MEXTI_Enable(EXT_INT0);

MGIE_Enable();

MEXTI_Disable(EXT_INT0);

ISR(INT0_vect)
{

}
 
ISR(INT1_vect)
{

}

ISR(INT2_vect)
{

} 

#endif