/* 
 * File:   STD_LIB.C
 * Author: Yousef.Khalefa
 * 
 * Created on February 16, 2024, 11:00 PM
 */

#include "STD_LIB.h"

Std_Return LIB_uint8_to_string(uint8 source, uint8* dist)
{
    Std_Return ret = E_OK;
    if(NULL == dist)
    {
        ret = E_NOK;
    }
    else
    {    
        memset((char*)dist, ' ', 4);
        dist[3]='\0';
        sprintf((char*)dist, "%i", source);
    }
    return ret;
}

Std_Return LIB_uint16_to_string(uint16 source, uint8* dist)
{
    Std_Return ret = E_OK;
    uint8 Temp_String[6] = {0};
    uint8 DataCounter = 0;
    if(NULL == dist)
    {
        ret = E_NOK;
    }
    else
    {    
        memset(dist, ' ', 5);
        dist[5] = '\0';
        sprintf((char *)Temp_String, "%i", source);
        while(Temp_String[DataCounter] != '\0')
        {
            dist[DataCounter] = Temp_String[DataCounter]; 
            DataCounter++;
        }
    }
    return ret;
}

Std_Return LIB_uint32_to_string(uint32 source, uint8* dist)
{
    Std_Return ret = E_OK;
    if(NULL == dist)
    {
        ret = E_NOK;
    }
    else
    {    
        memset((char *)dist, ' ', 11);
        dist[10]='\0';
        sprintf((char *)dist, "%li", source);
    }
    return ret;
}

Std_Return LIB_uint16_to_float_5v(uint16 source, float32* dist)
{
    Std_Return ret = E_OK;
    if(NULL == dist)
    {
        ret = E_NOK;
    }
    else
    {    
        *dist = ((float32)5/1023)*source;
    }
    return ret;
}

Std_Return LIB_uint16_to_float_2_56v(uint16 source, float32* dist)
{
    Std_Return ret = E_OK;
    if(NULL == dist)
    {
        ret = E_NOK;
    }
    else
    {    
        *dist = ((float32)2.56/1023)*source;
    }
    return ret;
}

