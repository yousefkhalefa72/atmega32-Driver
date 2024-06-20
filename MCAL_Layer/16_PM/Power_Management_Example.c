#if 0

    #include "Power_Management_Interface.h"
    
    DDRA =0XFF;
    DDRB =0XFF;
    
    DDRD =0X00;
    
    MGIE_Enable();
    MEXTI_SenseControl(EXT_INT0,RISING_EDGE);
    
    MPM_Enable(Sleep_Idle_Mode);
    MEXTI_Enable(EXT_INT0);
    
    MPM_EnterSleep();
    while(1)
    {
        PORTB=0XFF;
        MCAL_Delay_ms(500);
        PORTB=0X00;
        MCAL_Delay_ms(500);
    }
    
    
    
    ISR(INT0_vect)
    {
        PORTA=0XFF;
        MCAL_Delay_ms(500);

        PORTA=0X00;
        MCAL_Delay_ms(500);

    }
#endif















