#ifndef _LCOM_RTC_H_
#define _LCOM_RTC_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>

#define RTC_IS_UPDATING	BIT(7)
#define RTC_IS_BIN      BIT(2)

#define RTC_UPDATE_REG  0x10
#define RTC_COUNT_REG   0x11
#define RTC_INPUT_REG   0x70
#define RTC_OUTPUT_REG	0x71
#define IRQ_RTC      		8

#define RTC_H   4 
#define RTC_M   2
#define RTC_S   0  
#define RTC_Y   9
#define RTC_MIN 8
#define RTC_D   7

int rtc_setup();
int rtc_subscribe_int(uint8_t *bit_no);
int rtc_unsubscribe_int();

uint8_t rtc_to_bin(uint8_t bcd_number);
int rtc_output(uint8_t command, uint8_t *output);

int rtc_ih();
int rtc_updating();

typedef struct {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint8_t year;
    uint8_t month;
    uint8_t day;
} datetime;

#endif
