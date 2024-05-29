#include "ev_listener.h"

extern uint8_t scancode;

void handle_game_over_rebet(app_t *app, interrupt_type_t interrupt)
{
	app->game.main_player.bet = 0;
	app->game.main_player.cards_value = 0;
  queue_destroy(&app->game.main_player.cards, queue_destroy_nothing);
  app->game.main_player.cards = queue_create(PLAYER_MAX_DECK_SIZE);
	app->state = GAME_BET;
	vg_set_redraw();
}

void handle_game_over(app_t *app, interrupt_type_t interrupt)
{
  if (interrupt == KEYBOARD)
  {
		if (scancode == KB_1) handle_game_over_rebet(app, interrupt);
		
    if (scancode == KB_ESC || scancode == KB_2)
    {
      app->state = MAIN_MENU;
      game_destroy(&app->game);
      vg_set_redraw();
    }
  }

  if (interrupt == MOUSE)
  {
		if (cursor_sprite_colides(&app->cursor, queue_at(app->buttons_game_over, 0)))
    {
      app->game.dealer_turn = false;
			handle_game_over_rebet(app, interrupt);
    }

    if (cursor_sprite_colides(&app->cursor, queue_at(app->buttons_game_over, 1)))
    {
			app->state = MAIN_MENU;
      game_destroy(&app->game);
      vg_set_redraw();
    }
  }
}
