#if 0

#include "ICU_Interface.h"

uint32 freq = 0;
uint8 duty = 0;
MICU_EXTI0_T1_Read(&freq,&duty);

MICU_T1_Read(&freq,&duty); // recommended

#endif