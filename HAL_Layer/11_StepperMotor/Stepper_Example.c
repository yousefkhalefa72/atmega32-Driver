#if 0

#include "Stepper_Interface.h"

stepper_t stepper_1 ={.blue_coil.port=PORTC_INDEX,.blue_coil.pin=PIN2_INDEX,
                          .pink_coil.port=PORTC_INDEX,.pink_coil.pin=PIN1_INDEX,
                          .yellow_coil.port=PORTC_INDEX,.yellow_coil.pin=PIN0_INDEX,
                          .orange_coil.port=PORTC_INDEX,.orange_coil.pin=PIN3_INDEX};
    
HStepper_init(&stepper_1);

/* method 1 */
HStepper_Speed_t0(&stepper_1,5.6);

/* method 2*/
HStepper_Rotate(&stepper_1,stepper_0d);
MCAL_Delay_ms(1000);
HStepper_Rotate(&stepper_1,stepper_45d);
MCAL_Delay_ms(1000);
HStepper_Rotate(&stepper_1,stepper_90d);
MCAL_Delay_ms(1000);
HStepper_Rotate(&stepper_1,stepper_135d);
MCAL_Delay_ms(1000);
HStepper_Rotate(&stepper_1,stepper_180d);
MCAL_Delay_ms(1000);
HStepper_Rotate(&stepper_1,stepper_225d);
MCAL_Delay_ms(1000);
HStepper_Rotate(&stepper_1,stepper_270d);
MCAL_Delay_ms(1000);
HStepper_Rotate(&stepper_1,stepper_315d);
MCAL_Delay_ms(1000);


#endif
