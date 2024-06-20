/* 
 * File:   Stepper_Program.c
 * Author: Yousef.Khalefa
 * Created on March 12, 2024, 11:58 AM
 */

#include "Stepper_Interface.h"

#if T0_for_STEPPER == ENABLE
static uint8 G_ms_per_step = 0;
uint16 t0_CTC_milsec = 0;
static stepper_t* p_to_stepper = NULL;
static uint8 step = stepper_0d;
#endif

Std_Return HStepper_init(stepper_t *motor)
{
    Std_Return ret = E_OK; 
    /* config all pins output */
    motor->blue_coil.direction = DIO_DIRECTION_OUTPUT;
    motor->pink_coil.direction = DIO_DIRECTION_OUTPUT;
    motor->yellow_coil.direction = DIO_DIRECTION_OUTPUT;
    motor->orange_coil.direction = DIO_DIRECTION_OUTPUT;
    
    /* init zero degree*/
    motor->blue_coil.logic = DIO_HIGH;
    motor->orange_coil.logic = DIO_HIGH;
    
    /* init pins */
    ret &= MDIO_SetPinDirection(&motor->blue_coil);
    ret &= MDIO_SetPinDirection(&motor->pink_coil);
    ret &= MDIO_SetPinDirection(&motor->yellow_coil);
    ret &= MDIO_SetPinDirection(&motor->orange_coil);
    return ret;
}

Std_Return HStepper_Rotate(stepper_t *motor,degree_t degree)
{
    Std_Return ret = E_OK;
    
    ret = MDIO_SetPinValue(&motor->blue_coil,DIO_LOW);
    ret &= MDIO_SetPinValue(&motor->pink_coil,DIO_LOW);
    ret &= MDIO_SetPinValue(&motor->yellow_coil,DIO_LOW);
    ret &= MDIO_SetPinValue(&motor->orange_coil,DIO_LOW);
    
    switch(degree)
    {
        case stepper_0d:
            ret &= MDIO_SetPinValue(&motor->orange_coil,DIO_HIGH);
            ret &= MDIO_SetPinValue(&motor->blue_coil,DIO_HIGH);
            break;
                        
        case stepper_45d:
            ret &= MDIO_SetPinValue(&motor->blue_coil,DIO_HIGH);
            break;
        
        case stepper_90d:
            ret &= MDIO_SetPinValue(&motor->blue_coil,DIO_HIGH);
            ret &= MDIO_SetPinValue(&motor->pink_coil,DIO_HIGH);
            break;
                        
        case stepper_135d:
            ret &= MDIO_SetPinValue(&motor->pink_coil,DIO_HIGH);
            break;
                        
        case stepper_180d:
            ret &= MDIO_SetPinValue(&motor->pink_coil,DIO_HIGH);
            ret &= MDIO_SetPinValue(&motor->yellow_coil,DIO_HIGH);
            break;
                        
        case stepper_225d:
            ret &= MDIO_SetPinValue(&motor->yellow_coil,DIO_HIGH);
        break;
                        
        case stepper_270d:
            ret &= MDIO_SetPinValue(&motor->yellow_coil,DIO_HIGH);
            ret &= MDIO_SetPinValue(&motor->orange_coil,DIO_HIGH);
            break;
                        
        case stepper_315d:
            ret &= MDIO_SetPinValue(&motor->orange_coil,DIO_HIGH);
        break;

        default : ret = E_NOK;               
    }
    return ret;
}
#if T0_for_STEPPER == ENABLE
Std_Return HStepper_Speed_t0(stepper_t *motor,float32 RPS)
{
    Std_Return ret = E_OK;
    
    if(motor == NULL)
        return E_NOK;
    
    if((RPS == 0) ||(RPS > 12.5))
    {
        HStepper_Rotate(motor,stepper_0d);
        MTimer0_DeInit(0);
        return !RPS;
    }
    
    p_to_stepper = motor;
//    float32 step_per_sec = ((float32)RPS * 8.0) ;
//    float32 sec_per_step = 1.0/step_per_sec ;
//    uint16 ms_per_step = sec_per_step*1000 ;
    
    G_ms_per_step = ((1.0/((float32)RPS * 8.0)) * 1000);
    
    HStepper_Rotate(motor,stepper_0d);
    DDRA =0xff;
    MTimer0_Init(T0_CTC,OC0_DISCONNECTED);
    
    MTimer0_SetOCR0Value(125);
    MTimer0_SetPreloadValue(0);
    
    MTimer0_Star(T0_PRESCALER_64);
    
    return ret;
}

ISR(TIMER0_COMP_vect)
{
    t0_CTC_milsec++;
    if(t0_CTC_milsec == G_ms_per_step - TIME_ERROR_MS)
    {
        if(step != stepper_315d)
            step++;
        else
            step = stepper_0d;
        
        HStepper_Rotate(p_to_stepper,step);
        t0_CTC_milsec = 0;
    }
}
#endif