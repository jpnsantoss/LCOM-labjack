#include "ev_listener.h"
#include "../drivers/drivers.h"
#include "../drawer/drawer.h"
#include "../sprite/sprite.h"

extern uint8_t scancode;
extern int timer_counter;

state_handler_t listeners[] = {
  { MAIN_MENU, handle_main_menu },
  { GAME_BETTING, handle_game_betting },
};

void handle_interrupt(app_t *app, ev_listener_t listener)
{
	handle_general(app, listener.interrupt);
	listeners[listener.state].handle(app, listener.interrupt);
}

void handle_general(app_t *app, interrupt_type_t interrupt)
{
	switch (interrupt)
	{
		case KEYBOARD:
			kbc_ih();
			if (scancode == KEYBOARD_ESC) set_state(EXIT);
			if (scancode == 0xad)
			{
				uart_write_msg(1, 1);
				printf("X\n");
			}
			break;
		case MOUSE:
			mouse_ih();
			// mouseSync();
			if (mouse_read_packet())
			{
				mouse_info_t *info = mouse_get_info();
				if (info == NULL)
				{
					printf("null????\n");
					return;
				}
				//printf("dx: %d, dy: %d\n", info->delta_x, info->delta_y);
				//printf("rb: %d, mb: %d, lb: %d\n", info->rb, info->mb, info->lb);
				updateCursorPos(info);
			}
			break;
		case UART:
			printf("UART IH\n");
			uart_ih();
			break;
		case TIMER:
			draw_screen(app);
			break;
		case RTC:
			break;
	}
}

void handle_main_menu(app_t *app, interrupt_type_t interrupt)
{
	mouse_info_t *info = mouse_get_info();

  	if (interrupt == MOUSE && info != NULL)
	{
		if(sprite_colides(app->cursor, app->play_button) && info->lb)
		{
			set_state(GAME_BETTING);
		}		
		else if(sprite_colides(app->cursor, app->exit_button) && info->lb)
		{
			set_state(EXIT);
		}
	}
}

// Function to handle the interrupts in the game start
void handle_game_betting(app_t *app, interrupt_type_t interrupt)
{
	if (interrupt == MOUSE)
	{
		// Handle the interrupt here
  	}
}
