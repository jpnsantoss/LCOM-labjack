#include "drawer.h"
#include "../model/app/app.h"

void draw_state(app_t *app)
{
	card_t *card;
	switch(app->state)
	{
		case MAIN_MENU:
			sprite_draw(app->play_button);
			sprite_draw(app->exit_button);
			break;
		case GAME_BETTING:
			card = (card_t *) queue_pop(app->game.cards);
			if (card == NULL) break;
			sprite_move(card->sprite_base, 200, 200);
			sprite_draw(card->sprite_base);
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
