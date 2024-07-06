#if 0

#include "PCA9685_Interface.h"

/*
 * TWI frame 1 A5 A4 A3 A2 A1 A0 R/W
 * 
 * address      GND             5v
 * 0x40         ALL             NON
 * 0x41         5,4,3,2,1       0
 * 0x42         5,4,3,2,0       1
 */

HPCA9685_init();

HPCA9685_set_pwm(0,1*4096/20);
HPCA9685_set_pwm(1,1.5*4096/20);
HPCA9685_set_pwm(2,2*4096/20);

HPCA9685_set_servo_angle(0,-90);
HPCA9685_set_servo_angle(1,0);
HPCA9685_set_servo_angle(2,90);

#endif