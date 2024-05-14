#include "../labjack.h"

int driver_init(game_t *game)
{
	if (vg_map_memory(0x105)) return 1;

	if (vg_enter_graphic_mode(0x105)) return 1;

	if (kbd_subscribe_int(&game->bit_no_kb)) return 1;

	if (kbc_write(MOUSE_DATA_REPORT_ENABLE, true)) return 1;

	if (timer_subscribe_int(&game->bit_no_timer)) return 1;

	if (mouse_subscribe_int(&game->bit_no_mouse)) return 1;

	if (uart_subscribe_int(&game->bit_no_uart)) return 1;
	
	if (uart_setup(UART_DEFAULT_BIT_RATE)) return 1;
}

int driver_dispose()
{
	if (uart_disable()) return 1;

	if (uart_unsubscribe_int()) return 1;
	
	if (kbc_write(MOUSE_DATA_REPORT_DISABLE, true)) return 1;

	if (kbd_unsubscribe_int()) return 1;

	return vg_exit();
}
