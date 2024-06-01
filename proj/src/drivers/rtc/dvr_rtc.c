#include "../drivers.h"

datetime_t curr_time;
int rtc_hook_id = 5; 
uint8_t bin_mode;   

uint8_t (rtc_to_bin)(uint8_t inbcd)
{
    uint8_t units = inbcd & 0x0F;
    uint8_t tens = (inbcd >> 4) * 10;
    return units + tens;
}

int (rtc_get_time)()
{
    uint8_t out;

    printf("Checking if RTC is updating...\n");
    rtc_wait();

    printf("Reading year...\n");
    if (rtc_read_output(Y, &out)) return 1;

    curr_time.year = bin_mode ? out : rtc_to_bin(out);
    printf("Year: %d\n", curr_time.year);

    printf("Reading month...\n");
    if (rtc_read_output(M, &out)) return 1;

    curr_time.month = bin_mode ? out : rtc_to_bin(out);
    printf("Month: %d\n", curr_time.month);

    printf("Reading day...\n");
    if (rtc_read_output(D, &out)) return 1;

    curr_time.day = bin_mode ? out : rtc_to_bin(out);
    printf("Day: %d\n", curr_time.day);

    printf("Reading hours...\n");
    if (rtc_read_output(H, &out)) return 1;

    curr_time.hours = bin_mode ? out : rtc_to_bin(out);
    printf("Hours: %d\n", curr_time.hours);

    printf("Reading minutes...\n");
    if (rtc_read_output(MNT, &out)) return 1;

    curr_time.minutes = bin_mode ? out : rtc_to_bin(out);
    printf("Minutes: %d\n", curr_time.minutes);

    printf("Reading seconds...\n");
    if (rtc_read_output(S, &out) != 0) return 1;

    curr_time.seconds = bin_mode ? out : rtc_to_bin(out);
    printf("Seconds: %d\n", curr_time.seconds);

    return 0;
}
int rtc_set_alarm()
{
    //fires at 18 o'clock
    rtc_wait();

    if (rtc_disable_update_int()) return 1;
    printf("Setting alarm...\n");

    uint8_t current_minutes;
    if (rtc_read_output(M, &current_minutes)) return 1;
    unsigned long alarm_minutes = (current_minutes + 5) % 60;

    rtc_wait();
    if (rtc_disable_update_int()) return 1;
    if (rtc_input(RTC_H_ALARM, RTC_DONT_CARE)) return 1;
    if (rtc_input(RTC_MIN_ALARM, alarm_minutes)) return 1;
    if (rtc_input(RTC_S_ALARM, RTC_DONT_CARE)) return 1;

    return rtc_update_int();
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
/*int(rtc_set_alarm)() {
    printf("Setting alarm...\n");
    
    rtc_wait();
    if(rtc_disable_update_int()!= 0) return 1;
    if(rtc_input(RTC_H_ALARM, RTC_DONT_CARE) != 0) return 1;
    if(rtc_input(RTC_MIN_ALARM, RTC_DONT_CARE) != 0) return 1;
    if(rtc_input(RTC_S_ALARM, RTC_DONT_CARE) != 0) return 1;
    if(rtc_update_int() != 0) return 1;
    return 0;
}*/
int (rtc_setup)() {
    uint8_t status;

    printf("Setting up RTC...\n");

    if (rtc_read_output(REGB, &status)) return 1;

    if (ISBIN & status) bin_mode = 1;

    if (rtc_get_time()) return 0;

    if (rtc_disable_alarm_int()) return 1;
    if (rtc_disable_update_int()) return 1;

    return rtc_alarm_int();
}

int (rtc_subscribe_int)(uint8_t* bit_no)
{
    uint8_t val = 0;

    if (rtc_read_output(REGC, &val)) return 1;
    
    if (bit_no == NULL) return 1;
		
    *bit_no = BIT(rtc_hook_id);

    if (sys_irqsetpolicy(RTC_IRQ_LINE, IRQ_REENABLE, &rtc_hook_id)) return 1;

    return rtc_update_int();
}

int (rtc_unsubscribe_int)()
{
  if (rtc_disable_alarm_int()) return 1;
  if (rtc_disable_update_int()) return 1;
  
	return sys_irqrmpolicy(&rtc_hook_id);
}

void (rtc_wait)()
{
  while (rtc_updating())
	{
    tickdelay(micros_to_ticks(20000));
  }
}


int (rtc_read_output)(uint8_t cmd, uint8_t *output)
{
  if (output == NULL) return 1;

  if (sys_outb(INPUT_REG, cmd)) return 1;
    
  return util_sys_inb(OUTPUT_REG, output);
}

int (rtc_input)(uint8_t cmd, uint8_t content)
{
  if (sys_outb(INPUT_REG, cmd)) return 1;

  return sys_outb(OUTPUT_REG, content);
}

int (rtc_updating)()
{
  uint8_t status;
    
	if (rtc_read_output(REGA, &status)) return 1;

  return ISUPDATING & status;
}

int (rtc_ih)()
{
  uint8_t value = 0;
  if (rtc_read_output(REGC, &value) != 0) return 1;

  if (value & REGC_ALARMFLAG)
	{
    if (rtc_alarm_handler()) return 1;
  }

  if (value & REGC_UPDATEFLAG)
	{
    if (rtc_get_time()) return 1;
  }

  return 0;
}

int (rtc_alarm_handler)()
{
    if (rtc_get_time()) return 1;

    curr_time.minutes++;
    if (curr_time.minutes >= 60)
		{
        curr_time.minutes -= 60;
        curr_time.hours++;
    }

    return rtc_set_alarm();
}

int (rtc_update_int)()
{
  uint8_t val;

  if (rtc_read_output(REGB, &val)) return 1; 
  val &= ~REGB_DONT_UPDATE;

  return rtc_input(REGB, val);
}

int (rtc_disable_update_int)()
{
  uint8_t val;
  
	if (rtc_read_output(REGB, &val)) return 1; 
  val |= REGB_DONT_UPDATE;

	return rtc_input(REGB, val);  
}

int (rtc_alarm_int)()
{
    uint8_t val = 0;

    if (rtc_read_output(REGB, &val)) return 1;
    val |= REGB_ALARM;

    if (rtc_input(REGB, val)) return 1;
		
    return 0;
}

int (rtc_disable_alarm_int)()
{
	uint8_t val = 0;

  if (rtc_read_output(REGB, &val)) return 1;
  val |= ~REGB_ALARM;
  
	return rtc_input(REGB, val);
}
