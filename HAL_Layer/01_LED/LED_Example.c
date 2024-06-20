#if 0

#include "LED_Interface.h"

led_t green_led ={.pin.port=PORTA_INDEX,.pin.pin=PIN0_INDEX,.type=Source_Led,.status=LED_OFF};
led_t red_led ={.pin.port=PORTC_INDEX,.pin.pin=PIN4_INDEX,.type=Sink_Led,.status=LED_ON};

HLED_initialize(&green_led);
HLED_initialize(&red_led);

MCAL_Delay_ms(1000);

HLED_turn_on(&green_led);
HLED_turn_off(&red_led);

MCAL_Delay_ms(1000);

HLED_toggle(&green_led);

#endif