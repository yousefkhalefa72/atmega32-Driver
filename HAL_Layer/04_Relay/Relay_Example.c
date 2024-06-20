#if 0 

#include "Relay_Interface.h"

relay_t relay1 = {.pin.port=PORTA_INDEX,.pin.pin=PIN0_INDEX,.status = RELAY_OFF};

HRelay_Initialize(&relay1);
MCAL_Delay_ms(1000);
HRelay_turn_on(&relay1);
MCAL_Delay_ms(1000);
HRelay_turn_off(&relay1);
MCAL_Delay_ms(1000);
HRelay_toggle(&relay1);
MCAL_Delay_ms(1000);

#endif
