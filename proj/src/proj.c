#include <lcom/lcf.h>
#include "labjack.h"

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

int counter = 0;
extern uint8_t scancode;

//chamado pela lcom_run
int (proj_main_loop)(int argc, char **argv)
{
	uint8_t bit_no_kb = 0, bit_no_uart = 1;
	int ipc_status;
	message msg;
	
	counter = 0;

	if (kbd_subscribe_int(&bit_no_kb)) return 1;
	
	if (uart_setup(UART_DEFAULT_BIT_RATE)) return 1;

	if (uart_subscribe_int(&bit_no_uart)) return 1;

	while (scancode != KEYBOARD_ESC)
	{
    	if (driver_receive(ANY, &msg, &ipc_status))
      		continue;

    	if (!is_ipc_notify(ipc_status))
			continue;

		if (_ENDPOINT_P(msg.m_source) != HARDWARE)
			continue;

    	if (msg.m_notify.interrupts & bit_no_kb) {
			kbc_ih();
			if (scancode & MAKECODE_BIT)
			{
				uart_write_msg(1, 1);
			}
		}

		if (msg.m_notify.interrupts & bit_no_uart)
		{
			uart_ih();
		}
			
	}

	if (uart_unsubscribe_int()) return 1;
	
	return kbd_unsubscribe_int();
}
