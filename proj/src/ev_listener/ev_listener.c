#include "ev_listener.h"

int	handle_interrupt(game_t *game, ev_listener_t event)
{
	t_gph gph = vg_get_info();
	mouse_info_t info;

	switch (event.interrupt)
	{
		case KEYBOARD:
			kbc_ih();
			break;
		case MOUSE:
			mouse_ih();
			if (mouse_read_packet(&info))
			{
				game->x += info.delta_x;
				game->y -= info.delta_y;
				//printf("%d, %d ", x, y);

				if (game->x < 0) game->x = 0;
				if (game->x >= (int)gph.x_res) game->x = gph.x_res - 1;
				if (game->y < 0) game->y = 0;
				if (game->y >= (int)gph.y_res) game->y = gph.y_res - 1;

				//printf("to %d, %d\n", x, y);
				//draw_screen(game->x, game->y);
			}
			break;
		case UART:
			uart_ih();
			break;
		case TIMER:
			break;
		case RTC:
			break;
	}
	return 0;
}
