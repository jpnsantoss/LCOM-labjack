#include "ev_listener.h"
#include "../drivers/drivers.h"
#include "../drawer/drawer.h"
#include "../sprite/sprite.h"

extern uint8_t scancode;
extern int timer_counter;

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

	hd(app, interrupt);
}

void handle_general(app_t *app, interrupt_type_t interrupt)
{
	switch (interrupt)
	{
		case KEYBOARD:
			kbc_ih();
			if (scancode == KEYBOARD_ESC) app->state = EXIT;

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
				if (info == NULL) return;
				
				updateCursorPos(app, info);
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

  if (interrupt == MOUSE && info != NULL)
	{
		if (sprite_colides(app->cursor, app->play_button) && info->lb)
		{
			app->state = GAME_BETTING;
		}
		else if (sprite_colides(app->cursor, app->exit_button) && info->lb)
		{
			app->state = EXIT;
		}
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
void handle_exit(app_t *app, interrupt_type_t interrupt)
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
