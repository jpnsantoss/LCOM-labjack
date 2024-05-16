#include "ev_listener.h"

state_handler_t listeners[] = {
  { MAIN_MENU, handle_main_menu },
  { GAME_BETTING, handle_game_betting },
};

void handle_interrupt(app_t *app, ev_listener_t listener)
{
	listeners[listener.state].handle(app, listener.interrupt);
	handle_general(app, listener.interrupt);
}

#include "../assets/cursor.xpm"
#include <lcom/pixmap.h>
#include "../sprite/sprite.h"
void handle_general(app_t *app, interrupt_type_t interrupt)
{
	t_gph gph = vg_get_info();
	mouse_info_t info;

	switch (interrupt)
	{
		case KEYBOARD:
			kbc_ih();
			break;
		case MOUSE:
			mouse_ih();
				// vg_clear_screen();
				// sprite_t *sprite = sprite_create(cursor, app->x, app->y);
				// sprite_draw(sprite);
				// sprite_delete(sprite);
				// vg_flush_buffer();
			break;
		case UART:
			uart_ih();
			break;
		case TIMER:
			break;
		case RTC:
			break;
	}
}

void handle_main_menu(app_t *app, interrupt_type_t interrupt)
{
  if (interrupt == TIMER) {
    // Handle the interrupt here
  }
}

// Function to handle the interrupts in the game start
void handle_game_betting(app_t *app, interrupt_type_t interrupt)
{
  if (interrupt == MOUSE) {
    // Handle the interrupt here
  }
}
