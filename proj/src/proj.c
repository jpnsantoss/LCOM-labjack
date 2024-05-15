#include <lcom/lcf.h>
#include "labjack.h"
#include "ev_listener.h"

int counter = 0;
extern uint8_t scancode;

typedef struct {
  uint8_t kb;
  uint8_t mouse;
  uint8_t uart;
  uint8_t timer;
  uint8_t rtc;
} bit_no_t;

// Any header files included below this line should have been created by you

int main(int argc, char *argv[])
{
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/src/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/src/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

interrupt_type_t get_interrupt_type(message msg, bit_no_t bit_no) {
  if (msg.m_notify.interrupts & BIT(bit_no.kb)) {
    return KEYBOARD;
  } else if (msg.m_notify.interrupts & BIT(bit_no.mouse)) {
    return MOUSE;
  } else if (msg.m_notify.interrupts & BIT(bit_no.uart)) {
    return UART;
  } else if (msg.m_notify.interrupts & BIT(bit_no.timer)) {
    return TIMER;
  } else if (msg.m_notify.interrupts & BIT(bit_no.rtc)) {
    return RTC;
  } else {
    return -1; // Invalid interrupt type
  }
}

//chamado pela lcom_run
int (proj_main_loop)(int argc, char **argv)
{

  app_state_t app_state = MAIN_MENU;
  bit_no_t bit_no;

  if (vg_map_memory(0x105)) return 1;

	if (vg_enter_graphic_mode(0x105)) return 1;

	if (kbc_write(MOUSE_DATA_REPORT_ENABLE, true)) return 1;
	
	if (kbd_subscribe_int(&bit_no.kb)) return 1;

	if (timer_subscribe_int(&bit_no.timer)) return 1;

	if (mouse_subscribe_int(&bit_no.mouse)) return 1;

	int ipc_status;
	message msg;
	
	counter = 0;

	while (scancode != KEYBOARD_ESC)
	{
    if (driver_receive(ANY, &msg, &ipc_status)) continue;

    if (!is_ipc_notify(ipc_status)) continue;

		if (_ENDPOINT_P(msg.m_source) != HARDWARE) continue;
    
    interrupt_type_t interrupt = get_interrupt_type(msg, bit_no);

    ev_listener_t listener = { app_state, interrupt };

    handle_interrupt(listener);
	}

  if (mouse_unsubscribe_int()) return 1;

	if (kbd_unsubscribe_int()) return 1;
	
	if (kbc_write(MOUSE_DATA_REPORT_DISABLE, true)) return 1;

	if (timer_unsubscribe_int()) return 1;

	return vg_clean();
}
