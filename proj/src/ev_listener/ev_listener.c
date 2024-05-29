#include "ev_listener.h"

uint8_t uart_response = 0xff;
extern uint8_t scancode;
extern int timer_counter;
int state_changed = 0;

handler listeners[] = {
  handle_main_menu,
  handle_game_betting,
  handle_game_playing,
  handle_game_over,
  handle_dealer_turn,
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
      timer_int_handler();
      draw_screen(app);
      break;
    case RTC:
      rtc_ih();
      break;
  }
}
