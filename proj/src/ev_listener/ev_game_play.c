#include "ev_listener.h"

extern uint8_t scancode;

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
      game_give_card(app->game.cards, app->game.main_player.cards);
      app->game.main_player.cards_value = game_get_cards_value(app->game.main_player.cards);
      
			if (app->game.main_player.cards_value > 21)
      {
        app->state = GAME_OVER;
      }
			else if (app->game.main_player.cards_value == 21)
      {
				app->game.main_player.coins += app->game.main_player.bet * 2;
				app->state = GAME_OVER;
			}

      vg_set_redraw();
    }

    if (cursor_sprite_colides(&app->cursor, queue_at(app->buttons_game_playing, 1)))
    {
        app->state = GAME_DEALER_TURN;
        vg_set_redraw();
    }

    if (cursor_sprite_colides(&app->cursor, queue_at(app->buttons_game_playing, 2)))
    {
			app->state = GAME_DEALER_TURN;
			game_give_card(app->game.dealer, app->game.main_player.cards);
			vg_set_redraw();
    }

    if (cursor_sprite_colides(&app->cursor, queue_at(app->buttons_game_playing, 3)))
    {

    }
  }
}
