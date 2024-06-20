/* 
 * File:   EEPROM_Program.c
 * Author: Yousef.Khalefa
 * Created on March 10, 2024, 9:26 AM
 */

#include "EEPROM_Interface.h"

Std_Return MEEPROM_WriteByte(uint16 Address_10bit, uint8 Data)
{
    Std_Return ret = E_OK;
    
    uint8 GIE_Status = MGIE_Get_Status(); // Read the Interrupt Status
    MGIE_Disable(); // Disable Global Interrupt
    
    while(READ_BIT(EECR,EEWE)); // Wait for finish write
    while(READ_BIT(SPMCR,SPMEN)); 

    EEAR = Address_10bit; // Update the Address Registers
    //EEARH = (uint8)(HBYTE(Address) & 0x03);
    //EEARL = (uint8)(Address & 0xFF);
            
    EEDR = Data; // Update the Data Register
    
    // Write logical one to EEMWE
    SET_BIT(EECR,EEMWE);

    // Start EEPROM write by setting EEWE within 4 clock cycles
    asm volatile (
        "sbi %[eecr], %[eewe]"
        :
        : [eecr] "I" (_SFR_IO_ADDR(EECR)),
          [eewe] "I" (EEWE)
    );

    /* Restore the Interrupt Status "Enabled or Disabled" */
    if(GIE_Status) 
        MGIE_Enable();
    else 
        MGIE_Disable();
    
    return ret;
}

Std_Return MEEPROM_WriteString(uint16 Address_10bit, uint8* Data)
{
    Std_Return ret = E_OK;
    
    uint8 GIE_Status = MGIE_Get_Status(); // Read the Interrupt Status
    MGIE_Disable(); // Disable Global Interrupt
    
    while(*Data)
    {  
        while(READ_BIT(EECR,EEWE)); // Wait for finish write
        while(READ_BIT(SPMCR,SPMEN)); 

        EEAR = Address_10bit; // Update the Address Registers
        EEDR = *Data; // Update the Data Register

        // Write logical one to EEMWE
        SET_BIT(EECR,EEMWE);

        // Start EEPROM write by setting EEWE within 4 clock cycles
        asm volatile (
            "sbi %[eecr], %[eewe]"
            :
            : [eecr] "I" (_SFR_IO_ADDR(EECR)),
              [eewe] "I" (EEWE)
        );
        Data++;
        Address_10bit++;
    }
    /* Restore the Interrupt Status "Enabled or Disabled" */
    if(GIE_Status) 
        MGIE_Enable();
    else 
        MGIE_Disable();
    return ret;
}
Std_Return MEEPROM_ReadByte(uint16 Address_10bit, uint8 *Data)
{
    Std_Return ret = E_NOK;
    if(NULL == Data)
    {
        ret = E_NOK;
    }
    else
    {
        while(READ_BIT(EECR,EEWE)); // Wait for finish write if found
        
        EEAR = Address_10bit; // Update the Address Registers
        //EEARH = (uint8)(HBYTE(Address) & 0x03);
        //EEARL = (uint8)(Address & 0xFF);
        
        SET_BIT(EECR,EERE); // Start EEPROM read by writing EERE 
        
        *Data = EEDR; // Return data from data register 
        ret = E_OK;
    }
    return ret;
}

Std_Return MEEPROM_ReadString(uint16 Address_10bit, uint8 *Data, uint8 size)
{
     Std_Return ret = E_NOK;
    if(NULL == Data || size == 0)
    {
        ret = E_NOK;
    }
    else
    {
        while(size)
        {
            while(READ_BIT(EECR,EEWE)); // Wait for finish write if found

            EEAR = Address_10bit; // Update the Address Registers

            SET_BIT(EECR,EERE); // Start EEPROM read by writing EERE 

            *Data = EEDR; // Return data from data register 
            
            Address_10bit++;
            Data++;
            size--;
        }
    }
    return ret;
}