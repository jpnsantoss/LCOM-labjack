#include "ev_listener.h"
#include "../assets/charxpms/0.xpm"
#include "../assets/charxpms/1.xpm"
#include "../assets/charxpms/2.xpm"
#include "../assets/charxpms/3.xpm"
#include "../assets/charxpms/4.xpm"
#include "../assets/charxpms/5.xpm"
#include "../assets/charxpms/6.xpm"
#include "../assets/charxpms/7.xpm"
#include "../assets/charxpms/8.xpm"
#include "../assets/charxpms/9.xpm"


extern uint8_t scancode;
extern int timer_counter;
int state_changed = 0;
uint32_t last = 0;

handler listeners[] = {
  handle_main_menu,
  handle_game_betting,
	handle_game_playing,
	handle_game_over,
	handle_bet_value,
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
			uart_ih();
			break;
		case TIMER:
			draw_screen(app);
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
			if (scancode == KB_ESC) app->state = EXIT;
			return;

		case MOUSE:
			if (cursor_sprite_colides(&app->cursor, queue_at(app->buttons_main_menu, 0)))
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

			if (cursor_sprite_colides(&app->cursor, queue_at(app->buttons_main_menu, 1)))
			{
				app->state = EXIT;
				return;
			}
			break;
		default:
			return;
	}	
}

void handle_game_playing(app_t *app, interrupt_type_t interrupt)
{
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
		if (scancode == KB_ENTER)
		{
			if (app->game.main_player.bet > app->game.main_player.coins) return;

			app->game.main_player.coins -= app->game.main_player.bet;
			app->state = GAME_PLAYING;
			vg_set_redraw();
		}
  }

	if(interrupt == MOUSE)
	{
		if (info == NULL) return;
    
		if (cursor_box_colides(&app->cursor, 470, 785, 690, 840))
		{
			app->state = GAME_BET_VALUE;
      
			vg_set_redraw();
		}
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
			if (scancode >= 0x82 && scancode <= 0x8b)
			{
				sprite_t *sprite = sprite_create(number_xpm[scancode - 0x82]);
        if (sprite == NULL) return;
        stack_push(app->xpms_numbers, sprite);
				last = scancode - 0x82;
				app->game.main_player.bet = app->game.main_player.bet * 10 + (scancode - 0x82);
				vg_set_redraw();
			}

			else if(scancode == 0x0E){
				stack_pop(app->xpms_numbers);
				if(app->game.main_player.bet>0){
					app->game.main_player.bet = (app->game.main_player.bet - last)/10;
				}
				vg_set_redraw();
			}

	  	else if (scancode == 0x9c) // enter
			{ 
        while (!stack_empty(app->xpms_numbers)) stack_pop(app->xpms_numbers);
        app->state = GAME_PLAYING;

        vg_set_redraw();
      }

			return;
    case MOUSE:

    default:
      return;
  }
}
