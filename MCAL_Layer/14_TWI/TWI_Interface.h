/* 
 * File:   TWI_Interface.h
 * Author: Yousef_Khalefa
 * Created on June 2, 2024, 6:00 PM
 */

#ifndef I2C_INTERFACE_H
#define	I2C_INTERFACE_H

/* ----------------- Includes -----------------*/
#include "TWI_Config.h"
#include "../00_Device_Config/Device_Config.h"
#include "../../LIB_Layer/STD_LIB.h"
#include "../04_INTI/INTI_Interface.h"

/* ----------------- Macro Declarations -----------------*/
#define TWI_ONLY_MASTER_MODE        255
/* TWI status codes */
#define TWI_START                0x08
#define TWI_REP_START            0x10
#define TWI_MT_SLA_ACK           0x18
#define TWI_MT_DATA_ACK          0x28
#define TWI_MR_SLA_ACK           0x40
#define TWI_MR_DATA_ACK          0x50
#define TWI_MR_DATA_NACK         0x58
#define TWI_SR_SLA_ACK           0x60
#define TWI_SR_DATA_ACK          0x80
#define TWI_SR_STOP_RESTART      0xA0
#define TWI_STATUS_MASK          0xF8

/* ----------------- Macro Functions Declarations -----------------*/
#define TWI_STATUS               (TWSR & TWI_STATUS_MASK)

/* ----------------- Data Type Declarations -----------------*/

/* ----------------- Software Interfaces Declarations -----------------*/
Std_Return MTWI_MasterInit(uint32 SCL_freq, uint8 Slave_7bitAddress);
Std_Return MTWI_SlaveInit(uint8 Slave_7bitAddress);
Std_Return MTWI_DeInit();

Std_Return MTWI_Master_Send_Start();
Std_Return MTWI_Master_Send_Stop();

Std_Return MTWI_Master_Send_SlaveAddressWr(uint8 Slave_7bitAddress);
Std_Return MTWI_Master_Send_SlaveAddressRd(uint8 Slave_7bitAddress);

Std_Return MTWI_Master_Send_Byte(uint8 data);
Std_Return MTWI_Master_Read_Byte_ACK(uint8 *data);
Std_Return MTWI_Master_Read_Byte_NACK(uint8 *data);

Std_Return MTWI_Slave_Send_Byte(uint8 data);
Std_Return MTWI_Slave_Read_Byte(uint8 *data);

#endif	/* I2C_INTERFACE_H */






