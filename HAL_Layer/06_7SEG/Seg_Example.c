#if 0

#include "Seg_Interface.h"

segment_Pins_t seg1={.pins[0].port=PORTA_INDEX,.pins[0].pin=PIN0_INDEX,
                     .pins[1].port=PORTA_INDEX,.pins[1].pin=PIN1_INDEX,
                     .pins[2].port=PORTA_INDEX,.pins[2].pin=PIN2_INDEX,
                     .pins[3].port=PORTA_INDEX,.pins[3].pin=PIN3_INDEX,
                     .pins[4].port=PORTA_INDEX,.pins[4].pin=PIN4_INDEX,
                     .pins[5].port=PORTA_INDEX,.pins[5].pin=PIN5_INDEX,
                     .pins[6].port=PORTA_INDEX,.pins[6].pin=PIN6_INDEX,
                     .type=SEGMENT_COMMON_ANODE};

segment_Port_t seg2={.port=PORTB_INDEX, .type=SEGMENT_COMMON_CATHODE};
        
BCD_segment_t seg3={.pins[0].port=PORTC_INDEX,.pins[0].pin=PIN0_INDEX,
                    .pins[1].port=PORTC_INDEX,.pins[1].pin=PIN1_INDEX,
                    .pins[2].port=PORTC_INDEX,.pins[2].pin=PIN2_INDEX,
                    .pins[3].port=PORTC_INDEX,.pins[3].pin=PIN3_INDEX}; 

HSeven_seg_Pins_intialize(&seg1);
HSeven_seg_Port_intialize(&seg2);
HSeven_seg_BCD_intialize(&seg3);
MCAL_Delay_ms(1000);
HSeven_seg_Pins_write_number(&seg1,1);
HSeven_seg_Port_write_number(&seg2,2);
HSeven_seg_BCD_write_number(&seg3,3);
MCAL_Delay_ms(1000);
HSeven_seg_Pins_write_char(&seg1,'a');
HSeven_seg_Port_write_char(&seg2,'b');

#endif
