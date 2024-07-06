/* 
 * File:   PCA9685_Program.c
 * Author: Yousef.Khalefa
 * Created on June 28, 2024, 1:05 PM
 */

#include "PCA9685_Interface.h"

Std_Return HPCA9685_write(uint8 reg, uint8 data) 
{
    Std_Return ret = E_OK;
    ret = MTWI_Master_Send_Start();
    ret &= MTWI_Master_Send_SlaveAddressWr(PCA9685_ADDRESS);
    ret &= MTWI_Master_Send_Byte(reg);
    ret &= MTWI_Master_Send_Byte(data);
    ret &= MTWI_Master_Send_Stop();
    return ret;
}

Std_Return HPCA9685_init() 
{
    Std_Return ret = E_OK;
    ret = MTWI_MasterInit(50000,TWI_ONLY_MASTER_MODE);
    ret = HPCA9685_write(0x00, 0x10); // Set to sleep mode to change prescaler
    ret &= HPCA9685_write(0xFE, 0x79); // Set prescaler for 50Hz PWM frequency
    ret &= HPCA9685_write(0x00, 0x00); // Wake up PCA9685
    ret &= HPCA9685_write(0x00, 0x20); // Enable auto-increment mode
    return ret;
}

Std_Return HPCA9685_set_pwm(uint8 channel, uint16 on_12bit) 
{
    Std_Return ret = E_OK;
    if(channel > 15)
    {
        return E_NOK;
    }
    else
    {
        ret = HPCA9685_write(0x06 + 4 * channel, 0);
        ret &= HPCA9685_write(0x07 + 4 * channel, 0);
        ret &= HPCA9685_write(0x08 + 4 * channel, on_12bit & 0xFF);
        ret &= HPCA9685_write(0x09 + 4 * channel, on_12bit >> 8);
    }
    return ret;
}

Std_Return HPCA9685_set_servo_angle(uint8 channel, sint16 angle) 
{
    // valid range
    if(angle < -90)
        angle = -90;
    if(angle > 90)
        angle = 90;
    if(channel > 15)
        return E_NOK;
    // Calculate pulse width in microseconds
    uint16_t pulse_width = 2000 + ((sint32)(angle-90)*(2000-1000))/(90+90);
    pulse_width = (uint16)(((uint32)pulse_width * 4096)/20000);

    return HPCA9685_set_pwm(channel,pulse_width);
}
