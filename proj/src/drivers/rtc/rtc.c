#include "rtc.h"

datetime time_info;
int rtc_hook_id = 5; 
uint8_t bin_mode;   


uint8_t to_bin(uint8_t inbcd) {
    uint8_t units = inbcd & 0x0F;
    uint8_t tens = (inbcd >> 4) * 10;
    return units + tens;
}

int update_time_rtc() {

    uint8_t out;

    if (updating_rtc() != 0) return 1;

    if (output_rtc(Y, &out) != 0) return 1;

    if (bin_mode) {
        time_info.year = out;
    } else {
        time_info.year = to_bin(out);
    }

    if (output_rtc(M, &out) != 0) return 1;

    if (bin_mode) {
        time_info.month = out;
    } else {
        time_info.month = to_bin(out);
    }  

    if (output_rtc(D, &out) != 0) return 1;

    if (bin_mode) {
        time_info.day = out;
    } else {
        time_info.day = to_bin(out);
    }

    if (output_rtc(H, &out) != 0) return 1;

    if (bin_mode) {
        time_info.hours = out;
    } else {
        time_info.hours = to_bin(out);
    }

    if (output_rtc(MIN, &out) != 0) return 1;

    if (bin_mode) {
        time_info.minutes = out;
    } else {
        time_info.minutes = to_bin(out);
    }

    if (output_rtc(S, &out) != 0) return 1;

    if (bin_mode) {
        time_info.seconds = out;
    } else {
        time_info.seconds = to_bin(out);
    }
    
    return 0;

}

void setup_rtc() {
    uint8_t ts;
    if (output_rtc(COUNT_REG, &ts)) return 1;
	if(ISBIN & ts)
        bin_mode = 1;
    update_time_rtc();
}

int subscribe_int_rtc() {
    return sys_irqsetpolicy(RTC_IRQ_LINE, IRQ_REENABLE, &rtc_hook_id);
}

int unsubscribe_int_rtc() {
    return sys_irqrmpolicy(&rtc_hook_id);
}

int output_rtc(uint8_t cmd, uint8_t *output) {
        if (output == NULL) return 1;
        uint32_t bits32;                   
        if(sys_inb(cmd, &bits32)!=0) return 1;  
        *output = 0xFF & bits32;    
        if (sys_outb(INPUT_REG, cmd) != 0) return 1;
        return (util_sys_inb(OUTPUT_REG, output) != 0);
}

int updating_rtc(){
    uint8_t ts;
    if (output_rtc(UPDATE_REG, &ts)) return 1;
	return ISUPDATING & ts;
}


