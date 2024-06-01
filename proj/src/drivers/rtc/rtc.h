#ifndef _LCOM_DRIVERS_RTC_H_
#define _LCOM_DRIVERS_RTC_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>

/**
 * @defgroup rtc RTC
 * @ingroup drivers
 * @{
*/

/** 
 * @defgroup irtc iRTC
 * @ingroup rtc
 * @{
 */

#define RTC_IRQ      					8
#define RTC_DELAY							20000
#define RTC_IS_UPDATING 			BIT(7)

#define RTC_DONT_CARE   			(BIT(7) | BIT(6))
#define RTC_REG_A							10
#define RTC_REG_A_UPDATE	  	BIT(7)
#define RTC_REG_B             11
#define RTC_REG_B_IS_BIN      BIT(2)
#define RTC_REG_B_ALARM       BIT(5)
#define RTC_REG_B_DONT_UPDATE BIT(7)
#define RTC_REG_C             12
#define RTC_REG_C_ALARM_FLAG  BIT(5)
#define RTC_REG_C_UPDATE_FLAG BIT(4)
#define RTC_INPUT_REG         0x70
#define RTC_OUTPUT_REG        0x71
#define RTC_REG_B_PERIODIC    BIT(6) 

#define RTC_H             4
#define RTC_H_ALARM       5
#define RTC_MIN           2
#define RTC_MIN_ALARM     3
#define RTC_S             0
#define RTC_S_ALARM       1
#define RTC_Y             9
#define RTC_M             8
#define RTC_D             7

/** @} */

typedef struct {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint8_t year;
    uint8_t month;
    uint8_t day;
} datetime_t;

int (rtc_subscribe_int)(uint8_t* bit_no);
int (rtc_unsubscribe_int)();

int rtc_setup();

uint8_t rtc_to_bin(uint8_t inbcd);
int rtc_get_time();

int rtc_set_alarm();

int rtc_read(uint8_t cmd, uint8_t *output);
int rtc_write(uint8_t cmd, uint8_t content);
void rtc_wait();

int (rtc_ih)();

int rtc_set_periodic_int(bool enable);
int rtc_set_update_int(bool enable);
int rtc_set_alarm_int(bool enable);

/** @} */

#endif
