/* 
 * File:   Ultrasonic_Program.c
 * Author: Yousef.Khalefa
 * Created on June 19, 2024, 9:18 AM
 */

#include "Ultrasonic_Interface.h"

Std_Return HUltrasonic_Init(ultrasonic_t *ultrasonic)
{
    Std_Return ret = E_OK;
    
    if(NULL == ultrasonic)
    {
        ret = E_NOK;
    }
    else
    {
        ultrasonic->Echo_Pin.direction=DIO_DIRECTION_INPUT;
        ultrasonic->Trigger_Pin.direction=DIO_DIRECTION_OUTPUT;
        ret = MDIO_SetPinDirection(&(ultrasonic->Echo_Pin));
        ret &= MDIO_SetPinDirection(&(ultrasonic->Trigger_Pin));
    }
    
    return ret;
}

#if ULTRASONIC_BY_T0==ENABLE
static uint8 timerOverflow;
Std_Return HUltrasonic_t0_Calculate_Distance(ultrasonic_t *ultrasonic, float32 *dist)
{
    Std_Return ret = E_OK;
    
    uint32 echo_width = 0;
    uint8 Timer0_counts = 0;
    logic_t Echo_status = DIO_LOW;
    
    if((NULL == ultrasonic)||(NULL == dist))
    {
        ret = E_NOK;
    }
    else
    { 
        MTimer0_Init(T0_NORMAL,OC0_DISCONNECTED);
        timerOverflow=0;
        /* Send Trigger Signal */
        ret = MDIO_SetPinValue(&(ultrasonic->Trigger_Pin), DIO_HIGH);
        MCAL_Delay_us(10);
        ret &= MDIO_SetPinValue(&(ultrasonic->Trigger_Pin), DIO_LOW);
        
        /* Wait the Echo pin to be High */
        while(DIO_LOW == Echo_status)
        {
            ret &= MDIO_GetPinValue(&(ultrasonic->Echo_Pin), &Echo_status);
        }
        /* Clear Timer0 Ticks -> Already Enabled */
        MTimer0_Star(T0_PRESCALER_8);
        ret &= MTimer0_SetPreloadValue(0);

        /* Wait the Echo pin to be Low */
        while(DIO_HIGH == Echo_status)
        {
            ret &= MDIO_GetPinValue(&(ultrasonic->Echo_Pin), &Echo_status);
        }
        
        /* Read the time */
        ret = MTimer0_Read_Counts(&Timer0_counts);
        MTimer0_Stop();
        
        // Calculate the total count (time)
        echo_width = Timer0_counts + (timerOverflow * 256);
        /* Calculate the distance 
         * tick = 8/8000000 = 10^-6
         * sound travelled time = (counts * tick )/2 in sec
         * sound travelling speed = 343 m/s
         * distance = speed * time = sound travelled time * 343 * 100 (m to cm)
         */ 

    // Calculate the distance in cm
    *dist = (echo_width * 0.01725);
    }
    
    return ret;
}

ISR(TIMER0_OVF_vect) 
{
    // Increment the overflow counter
    timerOverflow++;
}
#endif

#if ULTRASONIC_BY_ICU==ENABLE
uint16 TimerOverflow = 0;

Std_Return HUltrasonic_ICU_Calculate_Distance(ultrasonic_t *ultrasonic, float32 *dist)
{
    Std_Return ret = E_OK;
    
    if((NULL == ultrasonic)||(NULL == dist))
    {
        ret = E_NOK;
    }
    else
    { 
        uint16 count;
        ret = MTimer1_Init(T1_NORMAL,OC1A_DISCONNECTED,OC1B_DISCONNECTED);

        /* Send Trigger Signal */
        ret &= MDIO_SetPinValue(&(ultrasonic->Trigger_Pin), DIO_HIGH);
        MCAL_Delay_us(10);
        ret &= MDIO_SetPinValue(&(ultrasonic->Trigger_Pin), DIO_LOW);

        ret &= MTimer1_SetPreloadValue(0);	/* Clear Timer counter */

        /* Capture on rising edge, No prescaler*/
        MTimer1_IC_Rising_Edge_Select();
        ret &= MTimer1_Star(T1_NO_PRESCALER);

        MTimer1_IC_CLEAR_FLAG();
        MTimer1_OV_CLEAR_FLAG();

        /*Calculate width of Echo by Input Capture (ICP) */
        while (MTimer1_IC_READ_FLAG() == 0);/* Wait for rising edge */
        MTimer1_SetPreloadValue(0);	/* Clear Timer counter */
        
        MTimer1_IC_Falling_Edge_Select();
        
        MTimer1_IC_CLEAR_FLAG();
        MTimer1_OV_CLEAR_FLAG();
        TimerOverflow = 0;/* Clear Timer overflow count */

        while (MTimer1_IC_READ_FLAG() == 0);/* Wait for falling edge */
        MTimer1_DeInit();
        count = ICR1 + (65535 * TimerOverflow);	/* Take count */

        /* 8MHz Timer freq, sound speed =343 m/s */
        *dist = (float64)count / 466.47;
    }
    return ret;
}

ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;	/* Increment Timer Overflow count */
}

#endif