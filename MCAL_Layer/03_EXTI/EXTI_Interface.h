/* 
 * File:   EXTI_Interface.h
 * Author: Yousef.Khalefa
 * Created on March 10, 2024, 8:47 AM
 */

#ifndef EXTI_INTERFACE_H
#define	EXTI_INTERFACE_H

/* ----------------- Includes -----------------*/
#include "EXTI_Config.h"
#include "../00_Device_Config/Device_Config.h"
#include "../../LIB_Layer/STD_LIB.h"

/* ----------------- Macro Declarations -----------------*/

/* ----------------- Macro Functions Declarations -----------------*/
#define MEXTI_INT0_Read_Flag()       (READ_BIT(GIFR,INTF0))
#define MEXTI_INT0_Clear_Flag()      (SET_BIT(GIFR,INTF0))

#define MEXTI_INT1_Read_Flag()       (READ_BIT(GIFR,INTF1))
#define MEXTI_INT1_Clear_Flag()      (SET_BIT(GIFR,INTF1))

#define MEXTI_INT2_Read_Flag()       (READ_BIT(GIFR,INTF2))
#define MEXTI_INT2_Clear_Flag()      (SET_BIT(GIFR,INTF2))

/* ----------------- Data Type Declarations -----------------*/
typedef enum
{
    LOW_LEVEL =0,
    ANY_LOGICAL_CHANGE,
    FALLING_EDGE,
    RISING_EDGE
}Sense_Control_t;

typedef enum
{
    EXT_INT0 =  0,
    EXT_INT1,
    EXT_INT2        
}EXTI_NUM_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return MEXTI_SenseControl(EXTI_NUM_t ExtiNumber,Sense_Control_t Control);
Std_Return MEXTI_Enable(EXTI_NUM_t ExtiNumber);
Std_Return MEXTI_Disable(EXTI_NUM_t ExtiNumber);


#endif	/* EXTI_INTERFACE_H */

