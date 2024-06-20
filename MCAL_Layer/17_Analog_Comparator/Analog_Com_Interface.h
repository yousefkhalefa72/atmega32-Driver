/* 
 * File:   Analog_Com_Interface.h
 * Author: Yousef_Khalefa
 * Created on June 20, 2024, 10:53 AM
 */

#ifndef ANALOG_COM_INTERFACE_H
#define	ANALOG_COM_INTERFACE_H

/* Section : Includes */
#include "Analog_Com_Config.h"
#include "../00_Device_Config/Device_Config.h"
#include "../../LIB_Layer/STD_LIB.h"
#include "../06_ADC/ADC_Interface.h"

/* Section: Macro Declarations */

/* Section: Macro Functions Declarations */
#define MANA_COMP_INTERRUPT_ENABLE()     (SET_BIT(ACSR,ACIE))
#define MANA_COMP_INTERRUPT_DISABLE()    (CLR_BIT(ACSR,ACIE))

#define MANA_COMP_CLEAR_INT_FLAG()       (SET_BIT(ACSR,ACI))
#define MANA_COMP_READ_INT_FLAG()        (READ_BIT(ACSR,ACI))

#define MANA_COMP_ENABLE()               (CLR_BIT(ACSR,ACD))
#define MANA_COMP_DISABLE()              (SET_BIT(ACSR,ACD))

#define MANA_COMP_OUTREAD()              (READ_BIT(ACSR,ACO))

#define MANA_COMP_BANDGAP_ENABLE()       (SET_BIT(ACSR,ACBG))
#define MANA_COMP_BANDGAP_DISABLE()      (CLR_BIT(ACSR,ACBG))

/* Section: Data Type Declarations */
typedef enum
{
    INT_ON_TOGGLE,
    INT_ON_FALLING_EDGE,
    INT_ON_RISING_EDGE
}ANA_COMP_INTMode_t;

typedef enum
{
    NEG_IN_ADC0,
    NEG_IN_ADC1,
    NEG_IN_ADC2,
    NEG_IN_ADC3,
    NEG_IN_ADC4,
    NEG_IN_ADC5,
    NEG_IN_ADC6,
    NEG_IN_ADC7,
    NEG_IN_AIN1
}ANACOMP_neg_Input_t;

typedef enum
{
    OUT_TRIGGER_ICU,
    ICU_NOT_CONNECT
}ANACOMP_ICU_Trigger_t;

/* Section: Function Declarations */
Std_Return MAnalogComparator_Init(ANACOMP_neg_Input_t input_pin, ANACOMP_ICU_Trigger_t ICU_Status);
Std_Return MAnalogComparator_SetInterruptMode(ANA_COMP_INTMode_t mode);

#endif	/* ANALOG_COM_INTERFACE_H */

