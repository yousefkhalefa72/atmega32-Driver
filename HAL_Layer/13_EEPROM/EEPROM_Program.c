/* 
 * File:   EEPROM_Program.c
 * Author: Yousef.Khalefa
 * Created on June 19, 2024, 6:27 PM
 */

#include "EEPROM_Interface.h"

Std_Return HEEPROM_Write_Byte(uint16 address_11bit,uint8 data)
{
    Std_Return ret = E_OK;
    
    uint8 address = ((EEPROM_ID<<3)&0xf0) | ((address_11bit>>7)&0x07);
    ret = MTWI_Master_Send_Start();
    
    ret &= MTWI_Master_Send_SlaveAddressWr(address);
    ret &= MTWI_Master_Send_Byte(address_11bit&0xff);
    
    ret &= MTWI_Master_Send_Byte(data);
    
    ret &= MTWI_Master_Send_Stop();
    
    return ret;
}

Std_Return HEEPROM_Read_Byte(uint16 address_11bit,uint8 *data)
{
    Std_Return ret = E_OK;
    
    if(NULL == data)
    {
        ret = E_NOK;
    }
    else
    {
        uint8 address = ((EEPROM_ID<<3)&0xf0) | ((address_11bit>>7)&0x07);
        ret = MTWI_Master_Send_Start();
    
        ret &= MTWI_Master_Send_SlaveAddressWr(address);
        ret &= MTWI_Master_Send_Byte(address_11bit&0xff);

        ret &= MTWI_Master_Send_Start();
        ret &= MTWI_Master_Send_SlaveAddressRd(address);
        ret &= MTWI_Master_Read_Byte_NACK(data);

        ret &= MTWI_Master_Send_Stop();
    }
    
    return ret;
    
}