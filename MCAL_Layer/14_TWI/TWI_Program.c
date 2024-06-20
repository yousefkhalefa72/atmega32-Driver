/* 
 * File:   TWI_Program.c
 * Author: Yousef.Khalefa
 * Created on June 2, 2024, 6:00 PM
 */

#include "TWI_Interface.h"

Std_Return MTWI_MasterInit(uint32 SCL_freq, uint8 Slave_7bitAddress)
{
    Std_Return ret = E_OK;
    if(0 == SCL_freq)
    {
        ret = E_NOK;
    }
    else
    {
        TWCR = 0x00;    // Clear Control Register
        TWBR = 0x00;    // Clear bit Rate Register
        TWSR = 0x00;    // Clear prescaller
        
        uint16 bit_rate;
        uint8 prescalers[] = { 1, 4, 16, 64 };

        for (int i = 0; i < 4; i++) 
        {
            bit_rate = ((F_CPU / (2 * SCL_freq)) - 8)/ prescalers[i];
            if (bit_rate <= 255) 
            {
                TWSR = i;                 // Set the prescaler bits in TWSR
                TWBR = (uint8)bit_rate; // Set the TWBR register
                break;
            }
        }
        if(TWBR == 0)
            {return E_NOK;}
            
        if(Slave_7bitAddress != TWI_ONLY_MASTER_MODE)
            {TWAR = Slave_7bitAddress << 1;}
        
        SET_BIT(TWCR,TWEA); // Enable ACK
        SET_BIT(TWCR,TWEN); // Enable module
        CLR_BIT(TWCR,TWIE); // Disable module interrupt
    }
    return ret;
}

Std_Return MTWI_SlaveInit(uint8 Slave_7bitAddress)
{
    Std_Return ret = E_OK;

    TWCR = 0x00;    //clear Control Register

    TWAR = Slave_7bitAddress << 1;

    SET_BIT(TWCR,TWEA); // Enable ACK
    SET_BIT(TWCR,TWEN); // Enable module
//    SET_BIT(TWCR,TWIE); // Enable module interrupt
    
    return ret;
}

Std_Return MTWI_DeInit()
{
    TWCR = 0x00;    // Clear Control Register
    TWBR = 0x00;    // Clear bit Rate Register
    TWSR = 0x00;    // Clear prescaller
    
    return E_OK;
}

Std_Return MTWI_Master_Send_Start()
{    
    /* Send Start condition */
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

    /* Wait for the completion of the Start condition */
    while (!(TWCR & (1<<TWINT)));
   
    if ((TWSR & 0xF8) != 0x08)
        return E_NOK;
    else
        return E_OK;
}

Std_Return MTWI_Master_Send_Stop()
{
    /* Send Stop condition */
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);

    return E_OK;
}

Std_Return MTWI_Master_Send_SlaveAddressWr(uint8 Slave_7bitAddress)
{    
    TWDR = Slave_7bitAddress << 1;
    
    TWCR = (1<<TWINT) | (1<<TWEN);
    
    /* Wait for the completion of the Stop condition */
    while (!(TWCR & (1<<TWINT)));
    
    if ((TWSR & 0xF8) != 0x18)
        return E_NOK;
    else
        return E_OK;
        
}

Std_Return MTWI_Master_Send_SlaveAddressRd(uint8 Slave_7bitAddress)
{    
    TWDR = Slave_7bitAddress << 1;
    SET_BIT(TWDR,0);
    
    TWCR = (1<<TWINT) | (1<<TWEN);
    
    /* Wait for the completion of the Stop condition */
    while(READ_BIT(TWCR,TWINT) ==0);
    
    if ((TWSR & 0xF8) != 0x40)
        return E_NOK;
    else
        return E_OK;
}

Std_Return MTWI_Master_Send_Byte(uint8 data)
{
    TWDR = data;
    
    TWCR = (1<<TWINT) | (1<<TWEN);
    
    /* Wait for the completion of the Stop condition */
    while(READ_BIT(TWCR,TWINT)==0); //wait to finish
    
    if ((TWSR & 0xF8) != 0x28)
        return E_NOK;
    else
        return E_OK;
}

Std_Return MTWI_Master_Read_Byte_ACK(uint8 *data)
{
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)));
    
    *data = TWDR;
    
    if ((TWSR & 0xF8) != 0x50)
        return E_NOK;
    else
        return E_OK;
}

Std_Return MTWI_Master_Read_Byte_NACK(uint8 *data)
{
    TWCR = (1 << TWEN) | (1 << TWINT);
    while (!(TWCR & (1 << TWINT)));
    
    *data = TWDR;
    
    if ((TWSR & 0xF8) != 0x50)
        return E_NOK;
    else
        return E_OK;
}

Std_Return MTWI_Slave_Send_Byte(uint8 data)
{
    TWDR = data;
    
    TWCR = (1<<TWINT) | (1<<TWEN)| (1 << TWEA);
    
    /* Wait for the completion of the Stop condition */
    while (!(TWCR & (1 << TWINT))); //wait to finish
    
    if ((TWSR & 0xF8) != 0x28)
        return E_NOK;
    else
        return E_OK;
}

Std_Return MTWI_Slave_Read_Byte(uint8 *data)
{
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
    while (!(TWCR & (1 << TWINT)));
    
    *data = TWDR;
    
    if ((TWSR & 0xF8) != 0x50)
        return E_NOK;
    else
        return E_OK;
}