#include "labjack.h"

int counter = 0;
extern uint8_t scancode;

int game_loop()
{
	uint8_t bit_no_kb, bit_no_uart;
	int ipc_status;
	message msg;
	
	counter = 0;

	if (kbd_subscribe_int(&bit_no_kb)) return 1;

	if (uart_subscribe_int(&bit_no_uart)) return 1;

	if (uart_setup(UART_DEFAULT_BIT_RATE)) return 1;

	while (scancode != KEYBOARD_ESC)
	{
    	if (driver_receive(ANY, &msg, &ipc_status)) continue;

    	if (!is_ipc_notify(ipc_status)) continue;

		if (_ENDPOINT_P(msg.m_source) != HARDWARE) continue;

    	if (msg.m_notify.interrupts & bit_no_kb)
		{
			kbc_ih();
			/*if (scancode == 0xad) {
				uart_write_msg(1, 1);
				printf("KEY %x\n", scancode);
			}*/
		}

		if (msg.m_notify.interrupts & bit_no_uart)
		{
			uart_ih();
			printf("%d", IRQ_COM1);
		}
	}

	if (uart_disable()) return 1;
	if (uart_unsubscribe_int()) return 1;
	
	return kbd_unsubscribe_int();
}
