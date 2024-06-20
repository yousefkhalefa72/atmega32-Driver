#if 0 

#include "RTC_Interface.h"

MTWI_MasterInit(100000,TWI_ONLY_MASTER_MODE);

    
HRTC_Set_Time(20,10,14);
HRTC_Set_Date(4,1,3);

extern RTC_t RTC;

HRTC_Get_Time();
HRTC_Get_Date();

uint8 time[6]="time ";
HLCD_send_string(&lcd1,time);
HLCD_send_num(&lcd1,RTC.hours);
HLCD_send_char(&lcd1,':');
HLCD_send_num(&lcd1,RTC.minutes);
HLCD_send_char(&lcd1,':');
HLCD_send_num(&lcd1,RTC.seconds);

HLCD_set_cursor(&lcd1,row_2,colum_1);

uint8 data[6]="data ";
HLCD_send_string(&lcd1,data);
HLCD_send_num(&lcd1,RTC.date);
HLCD_send_char(&lcd1,'/');
HLCD_send_num(&lcd1,RTC.month);
HLCD_send_char(&lcd1,'/');
HLCD_send_num(&lcd1,2000 + RTC.year);

#endif
