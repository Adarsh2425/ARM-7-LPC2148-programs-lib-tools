#ifndef RTC_H_
#define RTC_H_

#define CCR_CLKEN	0x01

typedef struct {
    uint32_t RTC_Sec;     			/* Second value - [0,59] */
    uint32_t RTC_Min;     			/* Minute value - [0,59] */
    uint32_t RTC_Hour;    			/* Hour value - [0,23] */
    uint32_t RTC_Mday;    			/* Day of the month value - [1,31] */
    uint32_t RTC_Mon;     			/* Month value - [1,12] */
    uint32_t RTC_Year;   			/* Year value - [0,4095] */
    uint32_t RTC_Wday;    			/* Day of week value - [0,6] */
    uint32_t RTC_Yday;    			/* Day of year value - [1,365] */
} RTCTime;

void rtc_init( void );
RTCTime rtc_get_time( void );
void rtc_set_time( RTCTime LocalTime ) ;
#endif /* RTC_H_ */
