#if 0

#include "TWI_Interface.h"

/* Slave */

    MTWI_SlaveInit(0b0011011);
    
    /* Read two bytes from master */
    uint8 x,y;
    MTWI_Slave_Read_Byte(&x);
    MTWI_Slave_Read_Byte(&y);
    
    /* Send two bytes to master */
    MTWI_Slave_Send_Byte(0x22);
    MTWI_Slave_Send_Byte(0x11);

    /************************** to use this ISR ***************************
    1- enable ISR_interrupt
    2- set global vars and modify your main
             volatile uint8_t data_to_send[2] = {0, 0};
             volatile uint8_t data_index = 0;
             volatile uint8_t data_ready = 0;
     *********************************************************************/
    ISR(TWI_vect)
    {
        switch (TWI_STATUS)
        {
            case TWI_SR_SLA_ACK: // Own SLA+W has been received; ACK has been returned
            case TWI_SR_DATA_ACK: // Data has been received; ACK has been returned
                received_data = TWDR; // Read received data
                data_ready = 1; // Prepare to receive next byte
                TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA) | (1 << TWIE);
                break;

            case TWI_SR_STOP_RESTART: // A STOP or repeated START condition has been received while still addressed as Slave
                TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA) | (1 << TWIE);// Prepare to receive next address call
                break;

            case 0xA8: // Own SLA+R has been received; ACK has been returned
            case 0xB8: // Data byte in TWDR has been transmitted; ACK has been received
                if (data_index < sizeof(data_to_send))// Send next byte
                {
                    TWDR = data_to_send[data_index++];
                    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA) | (1 << TWIE);
                } 
                else 
                {
                    // No more data to send, prepare for next request
                    data_index = 0;
                    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA) | (1 << TWIE);
                }
                break;

            case 0xC0: // Data byte in TWDR has been transmitted; NACK has been received
            case 0xC8: // Last data byte in TWDR has been transmitted (TWEA = "0"); ACK has been received
                // Reset for next transmission
                data_index = 0;
                TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA) | (1 << TWIE);
                break;

            default:// Prepare to receive next byte/address call
                TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA) | (1 << TWIE);
                break;
        }
    }
/* Master */
    
    MTWI_MasterInit(100000,0b1010101);
    
    /* Send two byte to slave */
    MTWI_Master_Send_Start();
    MTWI_Master_Send_SlaveAddressWr(0b0011011);
    
    MTWI_Master_Send_Byte(0x22);
    MTWI_Master_Send_Byte(0x33);
    
    MTWI_Master_Send_Stop();
    
    uint8 x,y;
    
    /* Read two byte from slave */
    MTWI_Master_Send_Start();
    MTWI_Master_Send_SlaveAddressRd(0b0011011);
    MTWI_Master_Read_Byte_ACK(&x);
    MTWI_Master_Read_Byte_NACK(&y);
    MTWI_Master_Send_Stop();
    
#endif















