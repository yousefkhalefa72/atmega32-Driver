#if 0

#include "Buzzer_Interface.h"

buzzer_t alarm ={.pin.port=PORTA_INDEX,.pin.pin=PIN0_INDEX,.type=Source_Buzzer,.status=BUZZER_OFF};
    
HBuzzer_initialize(&alarm);
MCAL_Delay_ms(1000);
HBuzzer_turn_on(&alarm);
MCAL_Delay_ms(1000);
HBuzzer_turn_off(&alarm);
MCAL_Delay_ms(1000);
HBuzzer_toggle(&alarm);
MCAL_Delay_ms(1000);

#endif