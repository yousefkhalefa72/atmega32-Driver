#if 0

#include "Servo_Interface.h"

pin_t servo_A = {.port=PORTD_INDEX,.pin=PIN5_INDEX,.direction=DIO_DIRECTION_OUTPUT};
pin_t servo_B = {.port=PORTD_INDEX,.pin=PIN4_INDEX,.direction=DIO_DIRECTION_OUTPUT};

MDIO_SetPinDirection(&servo_A);
MDIO_SetPinDirection(&servo_B);


HServo_OC1A_SetServoAngle(-75);
HServo_OC1B_SetServoAngle(75);

#endif