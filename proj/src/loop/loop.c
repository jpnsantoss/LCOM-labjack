#include "labjack.h"

int counter = 0;
extern uint8_t scancode;

int game_run(game_t *game)
{
	int16_t x = 600, y = 500;
	int ipc_status;
	message msg;
	
	counter = 0;

	while (scancode != KEYBOARD_ESC)
	{
    if (driver_receive(ANY, &msg, &ipc_status)) continue;

    if (!is_ipc_notify(ipc_status)) continue;

		if (_ENDPOINT_P(msg.m_source) != HARDWARE) continue;

    if (msg.m_notify.interrupts & game->bit_no_kb)
		{
			kbc_ih();
			/*if (scancode == 0xad) {
				uart_write_msg(1, 1);
				printf("KEY %x\n", scancode);
			}*/
		}

		if (msg.m_notify.interrupts & game->bit_no_mouse)
		{
			mouse_info_t info;
			mouse_ih();
			if (mouse_read_packet(&info))
			{
				x += info.delta_x;
				y += info.delta_y;
				cursor_draw(x, y);
			}
		}

		/*if (msg.m_notify.interrupts & game->bit_no_uart)
		{
			uart_ih();
			printf("%s", "uart");
		}*/
	}

	return 0;
}
