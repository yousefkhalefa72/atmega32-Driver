#if 0

#include "EEPROM_Interface.h"

MTWI_MasterInit(50000,TWI_ONLY_MASTER_MODE);

HEEPROM_Write_Byte(0b00000000000,'a');
MCAL_Delay_ms(10);
HEEPROM_Write_Byte(0b00001111100,'b');
MCAL_Delay_ms(10);

uint8 data = 0;
HEEPROM_Read_Byte(0b00000000000,&data);
HLCD_send_char(&lcd1,data);
MCAL_Delay_ms(10);
HEEPROM_Read_Byte(0b00001111100,&data);
HLCD_send_char(&lcd1,data);
    
#endif