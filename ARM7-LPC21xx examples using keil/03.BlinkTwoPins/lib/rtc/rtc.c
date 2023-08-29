#include "system.h"
#include "rtc.h"

void rtc_init( void )
{
    PREINT = ((Fpclk / 32768) - 1);
    PREFRAC = (Fpclk - ((PREINT + 1) * 32768));
    CCR = CCR_CLKEN; 
    return;
}

void rtc_set_time( RTCTime LocalTime ) 
{
		SEC		=	LocalTime.RTC_Sec;
    MIN		=	LocalTime.RTC_Min ;
    HOUR	=	LocalTime.RTC_Hour;
    DOM		=	LocalTime.RTC_Mday ;
    DOW		=	LocalTime.RTC_Wday;
    DOY		=	LocalTime.RTC_Yday;
    MONTH	=	LocalTime.RTC_Mon ;
    YEAR	=	LocalTime.RTC_Year;

}
RTCTime rtc_get_time( void ) 
{
    RTCTime LocalTime;
    
    LocalTime.RTC_Sec = SEC;
    LocalTime.RTC_Min = MIN;
    LocalTime.RTC_Hour = HOUR;
    LocalTime.RTC_Mday = DOM;
    LocalTime.RTC_Wday = DOW;
    LocalTime.RTC_Yday = DOY;
    LocalTime.RTC_Mon = MONTH;
    LocalTime.RTC_Year = YEAR;
    return LocalTime;    
}

