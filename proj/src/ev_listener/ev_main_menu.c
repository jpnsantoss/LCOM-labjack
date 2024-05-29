#include "ev_listener.h"

extern uint8_t scancode;
extern uint8_t uart_response;

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
      if (uart_response == PROTO_QUERY_GAME)
      {
        uart_response = PROTO_NONE;
        uart_send_byte(PROTO_YES);

				app->state = GAME_BET;

        if (game_init(&app->game))
				{
          app->state = EXIT;
          game_destroy(&app->game);
          return;
        }

        vg_set_redraw();
      }
			if (uart_response == PROTO_YES)
			{
				app->state = GAME_BET;

        if (game_init(&app->game))
				{
          app->state = EXIT;
          game_destroy(&app->game);
          return;
        }

        vg_set_redraw();
			}
      break;
    default:
      return;
  }
}
