#ifndef _LCOM_DRIVERS_RTC_H_
#define _LCOM_DRIVERS_RTC_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>

/**
 * @defgroup rtc RTC
 * @ingroup drivers
 * @{
*/

#define ISUPDATING 				BIT(7)
#define ISBIN           	BIT(2)

#define RTC_DONT_CARE   	BIT(7) | BIT(6) 
#define REGA              10
#define REGA_UPDATE       BIT(7)
#define REGB              11
#define REGB_ALARM        BIT(5)
#define REGB_DONT_UPDATE  BIT(7)
#define REGC              12
#define REGC_ALARMFLAG    BIT(5)
#define REGC_UPDATEFLAG   BIT(4)
#define INPUT_REG         0x70
#define OUTPUT_REG        0x71
#define RTC_IRQ_LINE      8
#define REGB_PERIODIC     BIT(6) 

#define H                 4
#define RTC_H_ALARM       5
#define MNT               2
#define RTC_MIN_ALARM     3
#define S                 0
#define RTC_S_ALARM       1
#define Y                 9
#define M                 8
#define D                 7

uint8_t (rtc_to_bin)(uint8_t inbcd);
int (rtc_get_time)();
int (rtc_set_alarm)();
int (rtc_unset_alarm)();
int (rtc_setup)();
int (rtc_subscribe_int)(uint8_t* bit_no);
int (rtc_unsubscribe_int)();
int (rtc_read_output)(uint8_t cmd, uint8_t *output);
int (rtc_updating)();
int (rtc_input)(uint8_t cmd, uint8_t content);
void (rtc_wait)();
int (rtc_ih)();
int (rtc_alarm_handler)();
int (rtc_update_int)();
int (rtc_disable_update_int)();
int (rtc_alarm_int)();
int (rtc_disable_alarm_int)();
int (rtc_disable_periodic_int)();

typedef struct {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint8_t year;
    uint8_t month;
    uint8_t day;
} datetime_t;

/** @} */

#endif
