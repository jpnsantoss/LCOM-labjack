#ifndef _LCOM_RTC_H_
#define _LCOM_RTC_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>

#define ISUPDATING 0x10000000
#define ISBIN           0x100

#define UPDATE_REG       10
#define COUNT_REG        11
#define INPUT_REG      0x70
#define OUTPUT_REG     0x71
#define RTC_IRQ_LINE      8

#define H   4 
#define M   2
#define S   0  
#define Y   9
#define MIN 8
#define D   7

uint8_t to_bin(uint8_t bcd_number);
int update_time_rtc();
void setup_rtc();
int subscribe_int_rtc();
int unsubscribe_int_rtc();
int output_rtc(uint8_t command, uint8_t *output);
int updating_rtc();

typedef struct {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint8_t year;
    uint8_t month;
    uint8_t day;
} datetime;

#endif