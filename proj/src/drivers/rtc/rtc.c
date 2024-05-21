#include "rtc.h"

datetime_info time_info;
int rtc_hook_id = 5; 
uint8_t bin_mode;        

int is_bin_rtc() {
    uint8_t ts;
    if (output_rtc(COUNT_REG, &ts)) return 1;
	return ISBIN & ts;
}

int update_time_rtc() {
    
    if (rtc_is_updating() != 0) return 1;
    uint8_t output;

    if (output_rtc(Y, &output) != 0) return 1;
    time_info.year = bin_mode ? output : to_binary(output);

    if (output_rtc(M, &output) != 0) return 1;
    time_info.month = bin_mode ? output : to_binary(output);   

    if (output_rtc(D, &output) != 0) return 1;
    time_info.day = bin_mode ? output : to_binary(output);

    if (output_rtc(H, &output) != 0) return 1;
    time_info.hours = bin_mode ? output : to_binary(output);

    if (output_rtc(M, &output) != 0) return 1;
    time_info.minutes = bin_mode ? output : to_binary(output);

    if (output_rtc(S, &output) != 0) return 1;
    time_info.seconds = bin_mode ? output : to_bin(output);

    return 0;
}

void setup_rtc() {
    bin_mode = rtc_is_bin();
    update_time_rtc();
}

int unsubscribe_int_rtc() {
    return sys_irqsetpolicy(RTC_IRQ_LINE, IRQ_REENABLE, &rtc_hook_id);
}

int subscribe_int_rtc() {
    return sys_irqrmpolicy(&rtc_hook_id);
}

int output_rtc(uint8_t cmd, uint8_t *output) {
    if (sys_outb(INPUT_REG, cmd) != 0) return 1;
	if (util_sys_inb(OUTPUT_REG, output) != 0) return 1;
    return 0;
}

int updating_rtc(){
    uint8_t ts;
    if (output_rtc(UPDATE_REG, &ts)) return 1;
	return ISUPDATING & ts;
}



uint8_t to_bin(uint8_t bcd_number) {
    return ((bcd_number >> 4) * 10) + (bcd_number & 0xF);
}

