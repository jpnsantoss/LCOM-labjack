#include "rtc.h"

datetime_info time_info;
int rtc_hook_id = 5; 
uint8_t bin_mode;   


uint8_t to_bin(uint8_t inbcd) {
    return ((inbcd & 0xF)+(inbcd >> 4) * 10);
}

int update_time_rtc() {
    
    if (updating_rtc() != 0) return 1;
    uint8_t output;
    if (output_rtc(Y, &output) != 0) return 1;
    time_info.year = bin_mode ? output : to_bin(output);
    if (output_rtc(M, &output) != 0) return 1;
    time_info.month = bin_mode ? output : to_bin(output);   
    if (output_rtc(D, &output) != 0) return 1;
    time_info.day = bin_mode ? output : to_bin(output);
    if (output_rtc(H, &output) != 0) return 1;
    time_info.hours = bin_mode ? output : to_bin(output);
    if (output_rtc(M, &output) != 0) return 1;
    time_info.minutes = bin_mode ? output : to_bin(output);
    if (output_rtc(S, &output) != 0) return 1;
    time_info.seconds = bin_mode ? output : to_bin(output);
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
        if (output == NULL){ printf("failed to read undefined value"); return 1; }
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


