#include "ev_listener.h"

extern uint8_t scancode;
extern int timer_counter;
int state_changed = 0;
uint32_t last = 0;
uint8_t uart_response = 0xff;

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
			break;
		case MOUSE:
			mouse_ih();

			if (mouse_read_packet())
			{
				mouse_info_t *info = mouse_get_info();
				if (info == NULL) return;
				
				uint32_t new_x = app->cursor.x + info->delta_x;
  			uint32_t new_y = app->cursor.y - info->delta_y;

				cursor_move(&app->cursor, new_x, new_y);
				app->cursor.state = POINTER;
				
				vg_set_redraw();
			}
			break;
		case UART:
			if (uart_ih())
			{
				if (uart_get_byte(&uart_response)) uart_response = 0xff;
			}
			break;
		case TIMER:
			draw_screen(app);
			animation_run(app->card_loop);
			break;
		case RTC:
			rtc_ih();
			break;
	}
}

void handle_main_menu(app_t *app, interrupt_type_t interrupt)
{
	switch (interrupt)
	{
		case KEYBOARD:
			if (scancode == KB_0)
			{
				uart_send_byte(1);
			}
			if (scancode == KB_ESC) app->state = EXIT;
			return;

		case MOUSE:
			if (cursor_sprite_colides(&app->cursor, queue_at(app->buttons_main_menu, 0)))
			{
				app->state = GAME_BET;
			
				if (game_init(&app->game))
				{
					app->state = EXIT;
					game_destroy(&app->game);
					return;
				} 

				vg_set_redraw();
				return;
			}

			if (cursor_sprite_colides(&app->cursor, queue_at(app->buttons_main_menu, 1)))
			{
				app->state = EXIT;
				game_destroy(&app->game);
				return;
			}
			break;
		case UART:
			if (uart_response == 1)
			{
				uart_response = 0xff;
				cursor_move(&app->cursor, app->cursor.x + 10, app->cursor.y);
				vg_set_redraw();
			}
			break;
		default:
			return;
	}	
}

void handle_game_playing(app_t *app, interrupt_type_t interrupt)
{
	if (interrupt == KEYBOARD)
	{
		if (scancode == KB_ESC)
		{
			app->state = MAIN_MENU;
			vg_set_redraw();
		}
	}

	if (interrupt == MOUSE)
	{
		if (cursor_sprite_colides(&app->cursor, queue_at(app->buttons_game_playing, 0)))
		{
			
		}

		if (cursor_sprite_colides(&app->cursor, queue_at(app->buttons_game_playing, 1)))
		{
			
		}

		if (cursor_sprite_colides(&app->cursor, queue_at(app->buttons_game_playing, 2)))
		{
			
		}

		if (cursor_sprite_colides(&app->cursor, queue_at(app->buttons_game_playing, 3)))
		{
			
		}
  }
}


// Function to handle the interrupts in the game start
void handle_game_betting(app_t *app, interrupt_type_t interrupt)
{
	mouse_info_t *info = mouse_get_info();
	if (interrupt == KEYBOARD)
	{
		vg_set_redraw();
		
		if (app->game.input_select) handle_bet_value(app, interrupt);
		
		if (scancode == KB_ESC)
		{
			if (!app->game.input_select)
			{
				app->state = MAIN_MENU;
				game_destroy(&app->game);
				return;
			}
			app->game.input_select = false;
		}

		if (scancode == KB_ENTER) app->game.input_select = true;
  }

	if (interrupt == MOUSE)
	{
		if (info == NULL) return;
    
		if (!app->game.input_select && 
			cursor_box_colides(&app->cursor, 420, 785, 600, 840))
		{
    	app->game.input_select = true;
      
			vg_set_redraw();
		}
		else 
		{
			handle_bet_value(app, interrupt);
		}
	}
}

// Function to handle the interrupts in the game start
void handle_game_over(app_t *app, interrupt_type_t interrupt)
{
	if (interrupt == KEYBOARD)
	{
		if (scancode == KB_ESC)
		{
			app->state = MAIN_MENU;
			game_destroy(&app->game);
			vg_set_redraw();
		}
	}

	if (interrupt == MOUSE)
	{
		// Handle the interrupt here
  }
}

#include "../assets/font/font.h"
void handle_bet_value(app_t *app, interrupt_type_t interrupt)
{
	const xpm_map_t number_xpm[10] = {
		number_1_xpm, number_2_xpm, number_3_xpm,
		number_4_xpm, number_5_xpm, number_6_xpm, number_7_xpm,
		number_8_xpm, number_9_xpm, number_0_xpm
	};

  switch (interrupt)
	{
    case KEYBOARD:
			if (scancode >= KB_1 && scancode <= KB_0)
			{
				sprite_t *sprite = sprite_create(number_xpm[scancode - KB_1]);
        if (sprite == NULL) return;

        stack_push(app->xpms_numbers, sprite);
				last = scancode == KB_0 ? 0 : scancode - KB_1 + 1;

				app->game.main_player.bet = app->game.main_player.bet * 10 + last;
				vg_set_redraw();
			}

			if (scancode == KB_BACKSPC)
			{
				sprite_t *sprite = stack_pop(app->xpms_numbers);
				if (sprite != NULL) sprite_destroy(sprite);

				if(app->game.main_player.bet > 0)
				{
					app->game.main_player.bet = (app->game.main_player.bet - last) / 10;
				}

				vg_set_redraw();
			}

	  	if (scancode == KB_ENTER)
			{
				handle_bet_value_check(app);
      }

			return;
    case MOUSE:
			if (cursor_sprite_colides(&app->cursor, app->button_bet))
			{
				handle_bet_value_check(app);
			}
			return;
    default:
      return;
  }
}

void handle_bet_value_check(app_t *app)
{
	stack_destroy(&app->xpms_numbers, sprite_queue_destroy);
	app->xpms_numbers = stack_create(6);
	vg_set_redraw();

	if (app->game.main_player.bet == 0) return;
	
	if (app->game.main_player.bet > app->game.main_player.coins)
	{
		app->game.main_player.bet = 0;
		return;
	}
				
	app->game.main_player.coins -= app->game.main_player.bet;
	app->state = GAME_PLAY;
	app->game.input_select = false;

	game_give_card(app->game.cards, app->game.dealer);
	game_give_card(app->game.cards, app->game.dealer);

	game_give_card(app->game.cards, app->game.main_player.cards);
	game_give_card(app->game.cards, app->game.main_player.cards);
}
