#if 0

#include "Ultrasonic_Interface.h"

ultrasonic_t ultrasonic = {.Echo_Pin.port=PORTD_INDEX,.Echo_Pin.pin=PIN6_INDEX,
                                 .Trigger_Pin.port=PORTD_INDEX,.Trigger_Pin.pin=PIN7_INDEX};
    
HUltrasonic_Init(&ultrasonic);


/* method 1 -> ICU */
/* connect ECHO to ICP1 pin (PD6) */
float32 distance = 0;
HUltrasonic_ICU_Calculate_Distance(&ultrasonic,&distance);


/* method 2 -> T0 */
float32 distance = 0;
HUltrasonic_t0_Calculate_Distance(&ultrasonic,&distance);


#endif
