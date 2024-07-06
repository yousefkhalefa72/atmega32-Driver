#if 0

#include "LED_Interface.h"

led_t green_led ={.led.port=PORTA_INDEX,.led.pin=PIN0_INDEX,.type=LED_SOURCE,.status=LED_OFF};
led_t red_led ={.led.port=PORTC_INDEX,.led.pin=PIN4_INDEX,.type=LED_SINK,.status=LED_ON};

HLED_initialize(&green_led);
HLED_initialize(&red_led);

MCAL_Delay_ms(1000);

HLED_turn_on(&green_led);
HLED_turn_off(&red_led);

MCAL_Delay_ms(1000);

HLED_toggle(&green_led);

#endif
