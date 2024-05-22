#include "drawer.h"
#include "../model/app.h"

void draw_state(app_t *app)
{
	switch(app->state)
	{
		case MAIN_MENU:
			sprite_draw(app->play_button);
			sprite_draw(app->exit_button);
			break;
		case GAME_BETTING:
			break;
		case GAME_PLAYING:
			break;
		case GAME_OVER:
			break;
		default:
			break;
	}
}

void draw_screen(app_t *app)
{
	if (!vg_has_redraw()) return;

	sprite_draw(app->background);
	draw_state(app);
  sprite_draw(app->cursor);

	vg_flip();
}
