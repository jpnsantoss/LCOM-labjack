#include "rtc.h"

datetime time_info;
int hook_id_rtc = 5;
uint8_t bin_mode;   

int rtc_subscribe_int(uint8_t *bit_no) 
{
	if (!bit_no) return 1;

  *bit_no = BIT(hook_id_rtc);

  return sys_irqsetpolicy(IRQ_RTC, IRQ_REENABLE, &hook_id_rtc);
}

int rtc_unsubscribe_int()
{
	if (hook_id_rtc < 0) return 1;

  return sys_irqrmpolicy(&hook_id_rtc);
}

uint8_t rtc_to_bin(uint8_t inbcd)
{
  uint8_t units = inbcd & 0x0F;
  uint8_t tens = (inbcd >> 4) * 10;

  return units + tens;
}

int rtc_output(uint8_t cmd, uint8_t *output)
{
	uint32_t bits32;

  if (output == NULL) return 1;
                     
  if (sys_inb(cmd, &bits32)) return 1;  
  
	*output = 0xFF & bits32;    
  
	if (sys_outb(RTC_INPUT_REG, cmd) != 0) return 1;

  return util_sys_inb(RTC_OUTPUT_REG, output);
}

int rtc_updating()
{
  uint8_t ts;
  
	if (rtc_output(RTC_UPDATE_REG, &ts)) return 1;
	
	return RTC_IS_UPDATING & ts;
}

int rtc_ih()
{
  uint8_t out;

  if (rtc_updating()) return 1;

  if (rtc_output(RTC_Y, &out)) return 1;

	time_info.year = bin_mode ? out : rtc_to_bin(out);

  if (rtc_output(RTC_M, &out)) return 1;

	time_info.month = bin_mode ? out : rtc_to_bin(out);

  if (rtc_output(RTC_D, &out)) return 1;

  time_info.day = bin_mode ? out : rtc_to_bin(out);

  if (rtc_output(RTC_H, &out)) return 1;

  time_info.hours = bin_mode ? out : rtc_to_bin(out);

  if (rtc_output(RTC_MIN, &out) != 0) return 1;

	time_info.minutes = bin_mode ? out : rtc_to_bin(out);

  if (rtc_output(RTC_S, &out) != 0) return 1;

  time_info.seconds = bin_mode ? out : rtc_to_bin(out);
    
  return 0;
}

int rtc_setup()
{
  uint8_t ts;

  if (rtc_output(RTC_COUNT_REG, &ts)) return 1;

	if (RTC_IS_BIN & ts) bin_mode = 1;
  
	rtc_ih();

	return 0;
}


