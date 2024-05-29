#include "drawer.h"
#include "../model/app/app.h"

void draw_state(app_t *app)
{
	uint32_t x, y;

  if (app == NULL)
    return;

  if (app->state != MAIN_MENU && app->state != GAME_BET)
	{
    player_draw(&app->game.main_player);
		font_print_number(&app->font, app->game.main_player.coins, 92, 805);

    // TODO: Draw player info if multiplayer.

    game_draw_dealer(&app->game, &app->font);
    game_draw_deck(&app->game);

		font_print_char(&app->font, 'B', 10, 760);
    font_print_char(&app->font, 'e', 34, 765);
    font_print_char(&app->font, 't', 53, 765);
    font_print_char(&app->font, ':', 68, 765);

    font_print_number(&app->font, app->game.main_player.bet, 92, 760);
    font_print_number(&app->font, app->game.main_player.cards_value, 505, 575);
  }

  switch (app->state) {
    case MAIN_MENU:
      draw_button_set(app->buttons_main_menu);
      break;
    case GAME_BET:
      sprite_draw(app->button_bet);
      vg_draw_border(460, 785, 140, 55, app->game.input_select ? 0xe69f58 : 0xffffff, 4);
      if (app->game.main_player.bet != 0)
			{
        font_print_number(&app->font, app->game.main_player.bet, (vg_get_width() / 2) - 100, 795);
      }
			font_print_number(&app->font, app->game.main_player.coins, 92, 805);
      break;
    case GAME_PLAY:
      draw_button_set(app->buttons_game_playing);
      break;
    case GAME_OVER:
			x = vg_get_width() / 2 - 66;
			y = vg_get_height() / 2 - 42;
			switch (app->game.main_player.game_over_state)
			{
				case PLAYER_WIN:
					font_print_str(&app->font, "YOU WIN", x, y);
					break;
				case PLAYER_LOSS:
					font_print_str(&app->font, "YOU LOSE", x, y);
					break;
				case PLAYER_DRAW:
					font_print_str(&app->font, "DRAW", x, y);
					break;
				default:
					font_print_str(&app->font, "GAME ENDED?", x, y);
					break;
			}

			font_print_number(&app->font, app->game.main_player.won_coins, 
				vg_get_width() / 2 - 10, vg_get_height() / 2);

      draw_button_set(app->buttons_game_over);
      break;
    case GAME_DEALER_TURN:
      break;
    default:
      break;
  }
}

void draw_screen(app_t *app) {
  if (!vg_has_redraw() || app == NULL)
    return;

  sprite_draw(app->background);
  draw_state(app);
  cursor_draw(&app->cursor);

  vg_flip();
}

void draw_button_set(queue_t *buttons)
{
  if (buttons == NULL)
    return;

  uint32_t pos = vg_get_width() / 2 - buttons->curr_size * 0.5 * (64 + 30);
  for (size_t i = 0; i < buttons->curr_size; i++)
	{
    sprite_t *sprite = queue_at(buttons, i);
    if (sprite == NULL) return;

    sprite_move(sprite, pos, vg_get_height() - 93);
    if (sprite_draw(sprite)) return;

    pos += (64 + 30);
  }
}
