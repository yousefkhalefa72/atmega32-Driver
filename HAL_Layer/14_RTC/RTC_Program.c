/* 
 * File:   RTC_Program.c
 * Author: Yousef.Khalefa
 * Created on June 19, 2024, 6:34 PM
 */

#include "RTC_Interface.h"

RTC_t RTC={.seconds=0, .minutes=0, .hours=0, .date=1, .month=1, .year=0};

Std_Return HRTC_Set_Time(uint8 sec, uint8 min, uint8 hour)
{
    Std_Return ret = E_OK;
    if(sec < 60)
        sec = (((sec/10)<<4)&0x70) | ((sec%10)&0x0f);
    else
        sec = 0;
    
    if(min < 60)
    min = (((min/10)<<4)&0x70) | ((min%10)&0x0f);
    else
        min = 0;
    
    if(hour < 24)
    hour =(((hour/10)<<4)&0x30) | ((hour%10)&0x0f);
    else
        hour = 0;
    
    ret = MTWI_Master_Send_Start();
    
    ret &= MTWI_Master_Send_SlaveAddressWr(0b1101000); /* ds1307 address */
    
    ret &= MTWI_Master_Send_Byte(0); /* address of seconds */
    
    ret &= MTWI_Master_Send_Byte(sec);
    ret &= MTWI_Master_Send_Byte(min);
    ret &= MTWI_Master_Send_Byte(hour);
    
    ret &= MTWI_Master_Send_Stop();
    
    return ret;
}

Std_Return HRTC_Set_Date(uint8 data, uint8 month, uint8 year)
{
    Std_Return ret = E_OK;
    
    if(data < 32)
        data = (((data/10)<<4)&0x30) | ((data%10)&0x0f);
    else
        data = 1;
    
    if(month < 13)
        month = (((month/10)<<4)&0x10) | ((month%10)&0x0f);
    else
        month = 1;
    
    if(year < 100)
        year = (((year/10)<<4)&0xf0) | ((year%10)&0x0f);
    else
        year = 1;
    
    ret = MTWI_Master_Send_Start();
    
    ret &= MTWI_Master_Send_SlaveAddressWr(0b1101000); /* ds1307 address */
    
    ret &= MTWI_Master_Send_Byte(0x04); /* address of data */
    
    ret &= MTWI_Master_Send_Byte(data);
    ret &= MTWI_Master_Send_Byte(month);
    ret &= MTWI_Master_Send_Byte(year);
    
    ret &= MTWI_Master_Send_Stop();
    
    return ret;
}

Std_Return HRTC_Get_Time()
{
    Std_Return ret = E_OK;
    uint8 sec,min,hour;
    
    ret = MTWI_Master_Send_Start();
    ret &= MTWI_Master_Send_SlaveAddressWr(0b1101000); /* ds1307 address */
    ret &= MTWI_Master_Send_Byte(0); /* address of seconds */
    
    ret &= MTWI_Master_Send_Start();
    ret &= MTWI_Master_Send_SlaveAddressRd(0b1101000); /* ds1307 address */
    
    ret &= MTWI_Master_Read_Byte_ACK(&sec);
    ret &= MTWI_Master_Read_Byte_ACK(&min);
    ret &= MTWI_Master_Read_Byte_NACK(&hour);
    
    ret &= MTWI_Master_Send_Stop();
    
    RTC.seconds = (sec & 0x0f) + ((sec >> 4)&0x07)*10;
    RTC.minutes = (min & 0x0f) + ((min >> 4)&0x07)*10;
    RTC.hours = (hour & 0x0f) + ((hour >> 4)&0x03)*10;
    
    return ret;
}

Std_Return HRTC_Get_Date()
{
    Std_Return ret = E_OK;
    uint8 data,month,year;
    
    ret = MTWI_Master_Send_Start();
    ret &= MTWI_Master_Send_SlaveAddressWr(0b1101000); /* ds1307 address */
    ret &= MTWI_Master_Send_Byte(0x04); /* address of data */
    
    ret &= MTWI_Master_Send_Start();
    ret &= MTWI_Master_Send_SlaveAddressRd(0b1101000); /* ds1307 address */
    
    ret &= MTWI_Master_Read_Byte_ACK(&data);
    ret &= MTWI_Master_Read_Byte_ACK(&month);
    ret &= MTWI_Master_Read_Byte_NACK(&year);
    
    ret &= MTWI_Master_Send_Stop();
    
    RTC.date = (data & 0x0f) + ((data >> 4)&0x03)*10;
    RTC.month = (month & 0x0f) + ((month >> 4)&0x01)*10;
    RTC.year = (year & 0x0f) + ((year >> 4)&0x0f)*10;
    
    return ret;
}