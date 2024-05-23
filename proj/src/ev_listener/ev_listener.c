#include "ev_listener.h"

extern uint8_t scancode;
extern int timer_counter;
int state_changed = 0;

handler listeners[] = {
  handle_main_menu,
  handle_game_betting,
	handle_game_playing,
	handle_game_over,
	NULL
};

void handle_interrupt(app_t *app, interrupt_type_t interrupt)
{
	handle_general(app, interrupt);
	handler hd = listeners[app->state];
	if (hd == NULL) return;
	if (state_changed) 
	{
		state_changed = 0;
		return;
	}

	hd(app, interrupt);
}

void handle_general(app_t *app, interrupt_type_t interrupt)
{
	switch (interrupt)
	{
		case KEYBOARD:
			kbc_ih();
			if (scancode == KB_ESC && app->state != MAIN_MENU)
			{
				app->state = MAIN_MENU;
				state_changed = 1;
				vg_set_redraw();
			}

			if (scancode == KB_X || scancode == KB_C)
			{
				player_give_card(app->game.cards, &app->game.main_player,
					scancode == KB_C);
				vg_set_redraw();
			}

			if (scancode == KB_Y)
			{
				uart_write_msg(1, 1);
			}

			break;
		case MOUSE:
			mouse_ih();
			// mouseSync();
			if (mouse_read_packet())
			{
				mouse_info_t *info = mouse_get_info();
				if (info == NULL) return;
				
				app_update_cursor_pos(app, info);
				vg_set_redraw();
			}
			break;
		case UART:
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

	switch (interrupt)
	{
		case KEYBOARD:
			if (scancode == KB_ESC) app->state = EXIT;
			return;
	
		case MOUSE:
			if (info == NULL) return;

			if (sprite_colides(app->cursor, queue_at(app->buttons_main_menu, 0)) && info->lb)
			{
				app->state = GAME_BETTING;
			
				if (game_init(&app->game))
				{
					app->state = EXIT;
					game_destroy(&app->game);
					return;
				} 

				vg_set_redraw();
				return;
			}

			if (sprite_colides(app->cursor, queue_at(app->buttons_main_menu, 1)) && info->lb)
			{
				app->state = EXIT;
				return;
			}
			return;
		default:
			return;
	}	
}

void handle_game_playing(app_t *app, interrupt_type_t interrupt)
{
	if (interrupt == MOUSE)
	{
		// Handle the interrupt here
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

// Function to handle the interrupts in the game start
void handle_game_over(app_t *app, interrupt_type_t interrupt)
{
	if (interrupt == MOUSE)
	{
		// Handle the interrupt here
  }
}
