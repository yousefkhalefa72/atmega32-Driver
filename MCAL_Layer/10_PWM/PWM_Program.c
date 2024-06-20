/*
 * File:   PWM_Prog.c
 * Author: Yousef.Khalefa
 * Created on: May 15, 2024, 10:31 AM
 */

#include "PWM_Interface.h"

#if PWM0_CONFIG==ENABLE
Std_Return MPWM0_Start(pwm_mode_t mode, timer0_prescaler_t prescaller, uint8 oc0_value)
{
    switch(mode)/* set PWM mode */
    {
        /*MTimer0_Init(T0_FAST_PWM,OC0_FP_Clear_on_compare_Set_at_BOTTOM);*/
        case FAST_PWM:SET_BIT(TCCR0,WGM00);SET_BIT(TCCR0,WGM01);break;
        /*MTimer0_Init(T0_PWM_PHASE_CORRECT,OC0_PPC_Clear_on_up_compare_Set_at_down_compare);*/
        case PHASE_CORRECT:SET_BIT(TCCR0,WGM00);CLR_BIT(TCCR0,WGM01);break;
        default: return E_NOK;
    }
    /* set  pin OC0 mode */
	CLR_BIT(TCCR0,COM00);SET_BIT(TCCR0,COM01);
    /* set timer count */
	OCR0 = oc0_value;
    
    return MTimer0_Star(prescaller);
}

Std_Return MPWM0_Start_duty(pwm_mode_t mode, timer0_prescaler_t prescaller, uint8 duty_cycle)
{
    switch(mode)/* set PWM mode */
    {
        /*MTimer0_Init(T0_FAST_PWM,OC0_FP_Clear_on_compare_Set_at_BOTTOM);*/
        case FAST_PWM:SET_BIT(TCCR0,WGM00);SET_BIT(TCCR0,WGM01);break;
        /*MTimer0_Init(T0_PWM_PHASE_CORRECT,OC0_PPC_Clear_on_up_compare_Set_at_down_compare);*/
        case PHASE_CORRECT:SET_BIT(TCCR0,WGM00);CLR_BIT(TCCR0,WGM01);break;
        default: return E_NOK;
    }
    /* set  pin OC0 mode */
	CLR_BIT(TCCR0,COM00);SET_BIT(TCCR0,COM01);
    /* set timer count */
	OCR0 = (duty_cycle*255)/100;
    
    return MTimer0_Star(prescaller);
}

Std_Return MPWM0_Start_volt(pwm_mode_t mode, timer0_prescaler_t prescaller, float32 volt)
{
    switch(mode)/* set PWM mode */
    {
        /*MTimer0_Init(T0_FAST_PWM,OC0_FP_Clear_on_compare_Set_at_BOTTOM);*/
        case FAST_PWM:SET_BIT(TCCR0,WGM00);SET_BIT(TCCR0,WGM01);break;
        /*MTimer0_Init(T0_PWM_PHASE_CORRECT,OC0_PPC_Clear_on_up_compare_Set_at_down_compare);*/
        case PHASE_CORRECT:SET_BIT(TCCR0,WGM00);CLR_BIT(TCCR0,WGM01);break;
        default: return E_NOK;
    }
    /* set  pin OC0 mode */
	CLR_BIT(TCCR0,COM00);SET_BIT(TCCR0,COM01);
    /* set timer count */
	OCR0 = (uint8)(volt*51);
    
    return MTimer0_Star(prescaller);
}

Std_Return MPWM0_Stop()
{
    return MTimer0_Stop();
}
#endif

#if PWM1_CONFIG==ENABLE
#warning "by using PWM for timer1 setting duty cycle for any channal to 0 not working u must set OC1x manual to 0"
Std_Return MPWM1_Start(pwm_mode_t mode, timer1_prescaler_t prescaller, uint16 top, uint16 oc1A_value, uint16 oc1B_value)
{
    switch(mode)/* set PWM mode */
    {
        case FAST_PWM:CLR_BIT(TCCR1A,WGM10);SET_BIT(TCCR1A,WGM11);
                      SET_BIT(TCCR1B,WGM12);SET_BIT(TCCR1B,WGM13);break;
        case PHASE_CORRECT:CLR_BIT(TCCR1A,WGM10);CLR_BIT(TCCR1A,WGM11);
                           CLR_BIT(TCCR1B,WGM12);SET_BIT(TCCR1B,WGM13);break;
        default: return E_NOK;
    }
    if(oc1A_value)
    {
        CLR_BIT(TCCR1A,COM1A0);SET_BIT(TCCR1A,COM1A1);
        OCR1A = oc1A_value;
    }
    if(oc1B_value)
    {
        CLR_BIT(TCCR1A,COM1B0);SET_BIT(TCCR1A,COM1B1);
        OCR1B = oc1B_value;
    }
   
    /* set top value*/
	ICR1 = top ;
    
    return MTimer1_Star(prescaller);
}
Std_Return MPWM1_Start_duty(pwm_mode_t mode, timer1_prescaler_t prescaller, uint16 top, uint8 A_duty_cycle, uint8 B_duty_cycle)
{
    switch(mode)/* set PWM mode */
    {
        case FAST_PWM:CLR_BIT(TCCR1A,WGM10);SET_BIT(TCCR1A,WGM11);
                      SET_BIT(TCCR1B,WGM12);SET_BIT(TCCR1B,WGM13);break;
        case PHASE_CORRECT:CLR_BIT(TCCR1A,WGM10);CLR_BIT(TCCR1A,WGM11);
                           CLR_BIT(TCCR1B,WGM12);SET_BIT(TCCR1B,WGM13);break;
        default: return E_NOK;
    }
    if(A_duty_cycle)
    {
        CLR_BIT(TCCR1A,COM1A0);SET_BIT(TCCR1A,COM1A1);
        OCR1A = (uint16)(((uint32)A_duty_cycle*top)/100);
    }
    if(B_duty_cycle)
    {
        CLR_BIT(TCCR1A,COM1B0);SET_BIT(TCCR1A,COM1B1);
        OCR1B = (uint16)(((uint32)B_duty_cycle*top)/100);
    }
   
    /* set top value*/
	ICR1 = top ;
    
    return MTimer1_Star(prescaller);
}

Std_Return MPWM1_Start_volt(pwm_mode_t mode, timer1_prescaler_t prescaller, uint16 top, float32 A_volt, float32 B_volt)
{
    switch(mode)/* set PWM mode */
    {
        case FAST_PWM:CLR_BIT(TCCR1A,WGM10);SET_BIT(TCCR1A,WGM11);
                      SET_BIT(TCCR1B,WGM12);SET_BIT(TCCR1B,WGM13);break;
        case PHASE_CORRECT:CLR_BIT(TCCR1A,WGM10);CLR_BIT(TCCR1A,WGM11);
                           CLR_BIT(TCCR1B,WGM12);SET_BIT(TCCR1B,WGM13);break;
        default: return E_NOK;
    }
    if(A_volt)
    {
        CLR_BIT(TCCR1A,COM1A0);SET_BIT(TCCR1A,COM1A1);
        OCR1A = (uint16)(A_volt*13107);
    }
    if(B_volt)
    {
        CLR_BIT(TCCR1A,COM1B0);SET_BIT(TCCR1A,COM1B1);
        OCR1A = (uint16)(B_volt*13107);
    }
   
    /* set top value*/
	ICR1 = top ;
    
    return MTimer1_Star(prescaller);
}

Std_Return MPWM1_Stop()
{
    return MTimer1_Stop();
}
#endif

#if PWM2_CONFIG==ENABLE
Std_Return MPWM2_Start(pwm_mode_t mode, timer2_prescaler_t prescaller, uint8 oc2_value)
{
    switch(mode)/* set PWM mode */
    {
        /*MTimer2_Init(T2_FAST_PWM,OC2_FP_Clear_on_compare_Set_at_BOTTOM);*/
        case FAST_PWM:SET_BIT(TCCR2,WGM20);SET_BIT(TCCR2,WGM21);break;
        /*MTimer2_Init(T2_PWM_PHASE_CORRECT,OC2_PPC_Clear_on_up_compare_Set_at_down_compare);*/
        case PHASE_CORRECT:SET_BIT(TCCR2,WGM20);CLR_BIT(TCCR2,WGM21);break;
        default: return E_NOK;
    }
    /* set  pin OC2 mode */
	CLR_BIT(TCCR2,COM20);SET_BIT(TCCR2,COM21);
    /* set timer count */
	OCR2 = oc2_value;
    
    return MTimer2_Star(prescaller);
}

Std_Return MPWM2_Start_duty(pwm_mode_t mode, timer2_prescaler_t prescaller, uint8 duty_cycle)
{
    switch(mode)/* set PWM mode */
    {
        /*MTimer2_Init(T2_FAST_PWM,OC2_FP_Clear_on_compare_Set_at_BOTTOM);*/
        case FAST_PWM:SET_BIT(TCCR2,WGM20);SET_BIT(TCCR2,WGM21);break;
        /*MTimer2_Init(T2_PWM_PHASE_CORRECT,OC2_PPC_Clear_on_up_compare_Set_at_down_compare);*/
        case PHASE_CORRECT:SET_BIT(TCCR2,WGM20);CLR_BIT(TCCR2,WGM21);break;
        default: return E_NOK;
    }
    /* set  pin OC2 mode */
	CLR_BIT(TCCR2,COM20);SET_BIT(TCCR2,COM21);
    /* set timer count */
	OCR2 = (duty_cycle*255)/100;
    
    return MTimer2_Star(prescaller);
}

Std_Return MPWM2_Start_volt(pwm_mode_t mode, timer2_prescaler_t prescaller, float32 volt)
{
    switch(mode)/* set PWM mode */
    {
        /*MTimer2_Init(T2_FAST_PWM,OC2_FP_Clear_on_compare_Set_at_BOTTOM);*/
        case FAST_PWM:SET_BIT(TCCR2,WGM20);SET_BIT(TCCR2,WGM21);break;
        /*MTimer2_Init(T2_PWM_PHASE_CORRECT,OC2_PPC_Clear_on_up_compare_Set_at_down_compare);*/
        case PHASE_CORRECT:SET_BIT(TCCR2,WGM20);CLR_BIT(TCCR2,WGM21);break;
        default: return E_NOK;
    }
    /* set  pin OC2 mode */
	CLR_BIT(TCCR2,COM20);SET_BIT(TCCR2,COM21);
    /* set timer count */
	OCR2 = (uint8)(volt*51);
    
    return MTimer2_Star(prescaller);
}

Std_Return MPWM2_Stop()
{
    return MTimer2_Stop();
}
#endif
