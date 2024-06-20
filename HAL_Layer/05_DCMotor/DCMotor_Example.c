#if 0

#include "DCMotor_Interface.h"

dc_motor_t motor1 ={.pin[0].port=PORTA_INDEX, .pin[0].pin=PIN0_INDEX,
                    .pin[1].port=PORTA_INDEX, .pin[1].pin=PIN1_INDEX,
                    .Status=MOTOR_OFF}; 

HDCMotor_initialize(&motor1);
MCAL_Delay_ms(1000);
HDCMotor_move_left(&motor1);
MCAL_Delay_ms(1000);
HDCMotor_move_right(&motor1);
MCAL_Delay_ms(1000);
HDCMotor_stop(&motor1);

#endif