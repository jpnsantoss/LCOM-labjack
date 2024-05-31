#include "rtc.h"
#include <stdio.h>

datetime mytime;
int rtc_hook_id = 5; 
uint8_t bin_mode;   

uint8_t (rtc_to_bin)(uint8_t inbcd) {
    uint8_t units = inbcd & 0x0F;
    uint8_t tens = (inbcd >> 4) * 10;
    return units + tens;
}

int (rtc_get_time)() {
    uint8_t out;

    printf("Checking if RTC is updating...\n");
    if (rtc_updating() != 0) return 1;

    printf("Reading year...\n");
    if (rtc_read_output(Y, &out) != 0) return 1;

    if (bin_mode) {
        mytime.year = out;
    } else {
        mytime.year = rtc_to_bin(out);
    }
    printf("Year: %d\n", mytime.year);

    printf("Reading month...\n");
    if (rtc_read_output(M, &out) != 0) return 1;

    if (bin_mode) {
        mytime.month = out;
    } else {
        mytime.month = rtc_to_bin(out);
    }
    printf("Month: %d\n", mytime.month);

    printf("Reading day...\n");
    if (rtc_read_output(D, &out) != 0) return 1;

    if (bin_mode) {
        mytime.day = out;
    } else {
        mytime.day = rtc_to_bin(out);
    }
    printf("Day: %d\n", mytime.day);

    printf("Reading hours...\n");
    if (rtc_read_output(H, &out) != 0) return 1;

    if (bin_mode) {
        mytime.hours = out;
    } else {
        mytime.hours = rtc_to_bin(out);
    }
    printf("Hours: %d\n", mytime.hours);

    printf("Reading minutes...\n");
    if (rtc_read_output(MNT, &out) != 0) return 1;

    if (bin_mode) {
        mytime.minutes = out;
    } else {
        mytime.minutes = rtc_to_bin(out);
    }
    printf("Minutes: %d\n", mytime.minutes);

    printf("Reading seconds...\n");
    if (rtc_read_output(S, &out) != 0) return 1;

    if (bin_mode) {
        mytime.seconds = out;
    } else {
        mytime.seconds = rtc_to_bin(out);
    }
    printf("Seconds: %d\n", mytime.seconds);

    return 0;
}

int(rtc_set_alarm)() {
    printf("Setting alarm...\n");
    
    rtc_wait();
    if(rtc_disable_update_int()!= 0) return 1;
    if(rtc_input(RTC_H_ALARM, RTC_DONT_CARE) != 0) return 1;
    if(rtc_input(RTC_MIN_ALARM, RTC_DONT_CARE) != 0) return 1;
    if(rtc_input(RTC_S_ALARM, RTC_DONT_CARE) != 0) return 1;
    if(rtc_update_int() != 0) return 1;
    return 0;
}

/*
int (rtc_set_alarm)() {
    printf("Setting alarm...\n");
    rtc_wait();
    if(rtc_disable_update_int()!= 0) return 1;

    printf("Setting hours for alarm...\n");
    if (rtc_input(RTC_H_ALARM, mytime.hours) != 0) {
        return 1;
    }

    printf("Setting minutes for alarm...\n");
    if (rtc_input(RTC_MIN_ALARM, mytime.minutes) != 0) {
        return 1;
    }

    printf("Setting seconds for alarm to 'don't care'...\n");
    if (rtc_input(RTC_S_ALARM, RTC_DONT_CARE) != 0) {
        return 1;
    }

    rtc_update_int();
    return 0;
}*/

int (rtc_setup)() {
    uint8_t status;
    printf("Setting up RTC...\n");
    if (rtc_read_output(REGB, &status)) return 1;
    if (ISBIN & status) bin_mode = 1;
    if (rtc_get_time() != 0) return 0;
    printf("rtc setup");
    return 0;
}

int (rtc_subscribe_int)(uint8_t* bit_no) {
    if (!bit_no) return 1;
    *bit_no = BIT(rtc_hook_id);

    printf("Subscribing to RTC interrupts...\n");
    if (sys_irqsetpolicy(RTC_IRQ_LINE, IRQ_REENABLE, &(rtc_hook_id)) != 0) return 1;
    printf("Interrupts subscribed\n");

    if (rtc_update_int() != 0) return 1;
    printf("Update interrupts subscribed\n");

    return rtc_alarm_int();
}

int (rtc_unsubscribe_int)() {
    printf("Unsubscribing from RTC interrupts...\n");
    if (rtc_disable_alarm_int() != 0) return 1;
    if (rtc_disable_update_int() != 0) return 1;
    return sys_irqrmpolicy(&rtc_hook_id);
}

void (rtc_wait)() {
    uint8_t val;
    while (true) {
        val = 0;
        rtc_read_output(REGA, &val);
        if (!(val & REGA_UPDATE)) break;
        tickdelay(micros_to_ticks(20000));
    }
}

int (rtc_read_output)(uint8_t cmd, uint8_t *output) {
    if (output == NULL) return 1;   
    if (sys_outb(INPUT_REG, cmd) != 0) return 1;
    printf("Asked for output\n");
    return util_sys_inb(OUTPUT_REG, output);
}

int (rtc_input)(uint8_t cmd, uint8_t content) {
    if (sys_outb(INPUT_REG, cmd) != 0) return 1;
    return sys_outb(OUTPUT_REG, content);
}

int (rtc_updating)() {
    uint8_t status;
    if (rtc_read_output(REGA, &status)) return 1;
    return ISUPDATING & status;
}

int (rtc_ih)() {
    uint8_t value = 0;
    if (rtc_read_output(REGC, &value) != 0) {
        return 1;
    }

    if (value & REGC_ALARMFLAG) {
        printf("Alarm flag set, handling alarm...\n");
        if (rtc_alarm_handler() != 0) {
            return 1;
        }
    }

    if (value & REGC_UPDATEFLAG) {
        printf("Update flag set, updating time...\n");
        if (rtc_get_time() != 0) {
            return 1;
        }
    }

    return 0;
}

int (rtc_alarm_handler)() {
    printf("Alarm handler called!\n");
    if (rtc_get_time() != 0) {
        return 1;
    }

    mytime.minutes++;
    if (mytime.minutes >= 60) {
        mytime.minutes -= 60;
        mytime.hours++;
    }

    if (rtc_set_alarm() != 0) {
        return 1;
    }

    return 0;
}

int (rtc_update_int)() {
    uint8_t val;
    printf("Enabling update interrupts...\n");
    if (rtc_read_output(REGB, &val) != 0) 
        return 1; 
    val &= ~REGB_DONT_UPDATE;
    if (rtc_input(REGB, val) != 0) 
        return 1; 
    
    return 0; 
}

int (rtc_disable_update_int)() {
    printf("Disabling update interrupts...\n");
    uint8_t val;
    if (rtc_read_output(REGB, &val) != 0) return 1; 
    val |= REGB_DONT_UPDATE;
    if (rtc_input(REGB, val) != 0) return 1; 
    return 0; 
}

int (rtc_alarm_int)() {
    printf("Enabling alarm interrupts...\n");
    uint8_t val = 0;
    if (rtc_read_output(REGB, &val) != 0) return 1;
    val |= REGB_ALARM;
    printf("Necessary bits enabled!\n");
    if (rtc_input(REGB, val) != 0) return 1;
    return 0;
}

int (rtc_disable_alarm_int)() {
    printf("Disabling alarm interrupts...\n");
    uint8_t val = 0;
    if (rtc_read_output(REGB, &val) != 0) return 1;
    val |= ~REGB_ALARM;
    if (rtc_input(REGB, val) != 0) return 1;
    return 0;
}
