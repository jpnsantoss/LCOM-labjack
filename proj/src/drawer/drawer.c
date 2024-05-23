#include "drawer.h"
#include "../model/app/app.h"

void draw_state(app_t *app)
{
	if (app == NULL) return;

	switch(app->state)
	{
		case MAIN_MENU:
			draw_button_set(app->buttons_main_menu);
			break;
		case GAME_BETTING:
			player_draw(&app->game.main_player);
			game_draw_deck(&app->game);
			break;
		case GAME_PLAYING:
			player_draw(&app->game.main_player);
			game_draw_deck(&app->game);
			draw_button_set(app->buttons_game_playing);
			break;
		case GAME_OVER:
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
  sprite_draw(app->cursor);

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
		
		sprite_move(sprite, pos, vg_get_height() - 85);
		if (sprite_draw(sprite)) return;

		pos += (64 + 30);
	}
}
