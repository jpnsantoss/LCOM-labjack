#include "drawer.h"
#include "../model/app/app.h"

void draw_state(app_t *app)
{
	if (app == NULL) return;

	if (app->state != MAIN_MENU && app->state != GAME_OVER)
	{
		player_draw(&app->font, &app->game.main_player);

		// TODO: Draw player info if multiplayer.
		
		game_draw_deck(&app->game);
		game_draw_dealer(&app->game);
	}

	switch(app->state)
	{
		case MAIN_MENU:
			draw_button_set(app->buttons_main_menu);
			break;
		case GAME_BET:
			sprite_draw(app->button_bet);
			vg_draw_border(460, 785, 140, 55,
				app->game.input_select ? 0xe69f58 : 0xffffff, 4);
			if (app->game.input_select) font_print_number(&app->font, (uint16_t) app->game.main_player.bet, (
				vg_get_width() / 2) - 100, 795);
			break;
		case GAME_PLAY:
			font_print_number(&app->font, app->game.main_player.bet, 10, 760);
			font_print_number(&app->font, (uint16_t) &app->game.main_player.cards_value, 10, 725);
			draw_button_set(app->buttons_game_playing);
			break;
		case GAME_OVER:
			draw_button_set(app->buttons_game_over);
			break;
		default:
			break;
	}
}

void draw_screen(app_t *app)
{
	if (!vg_has_redraw() || app == NULL) return;

	sprite_draw(app->background);
	draw_state(app);
  cursor_draw(&app->cursor);

	vg_flip();
}

void draw_button_set(queue_t *buttons)
{
	if (buttons == NULL) return;
	
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
