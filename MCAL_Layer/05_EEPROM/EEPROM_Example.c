#if 0

#include "EEPROM_Interface.h"

uint8 data;

MEEPROM_WriteByte(0x0020, 'a');

MEEPROM_ReadByte(0x0020,&data);
MEEPROM_WriteByte(0x0021, data);

char yousef[7]="yousef";
uint8 str[7];

MEEPROM_WriteString(0x0000,yousef);

MEEPROM_ReadString(0x0000,str,6);
MEEPROM_WriteString(0x0008,str);
    
#endif
