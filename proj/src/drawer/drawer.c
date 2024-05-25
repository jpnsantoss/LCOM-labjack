#include "drawer.h"
#include "../model/app/app.h"
#include "../assets/charxpms/0.xpm"
#include "../assets/charxpms/1.xpm"
#include "../assets/charxpms/2.xpm"
#include "../assets/charxpms/3.xpm"
#include "../assets/charxpms/5.xpm"
#include "../assets/charxpms/6.xpm"
#include "../assets/charxpms/7.xpm"
#include "../assets/charxpms/8.xpm"
#include "../assets/charxpms/9.xpm"


#include "../assets/charxpms/s.xpm"
#include "../assets/charxpms/a.xpm"
#include "../assets/charxpms/d.xpm"
#include "../assets/charxpms/l.xpm"
#include "../assets/charxpms/o.xpm"

void draw_state(app_t *app)
{
	if (app == NULL) return;

	if (app->state != MAIN_MENU && app->state != GAME_OVER)
	{
		player_draw(&app->game.main_player);

		// TODO: Draw player info if multiplayer.
		
		game_draw_deck(&app->game);
		game_draw_dealer(&app->game);
	}

	switch(app->state)
	{
		case MAIN_MENU:
			draw_button_set(app->buttons_main_menu);
			animation_draw(app->card_loop);
			break;
		case GAME_BET:
			sprite_draw(app->button_bet);
			vg_draw_border(420, 785, 180, 55,
				app->game.input_select ? 0xe69f58 : 0xffffff, 4);
			draw_number(app->xpms_numbers);
			break;
		case GAME_PLAY:
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

void draw_number(my_stack_t *xpms_numbers)
{
	if (xpms_numbers == NULL) return;
	
	uint32_t pos = (vg_get_width() / 2) - 150;
	for (size_t i = xpms_numbers->curr_size; i > 0; i--)
	{
		size_t index = i - 1;
		sprite_t *sprite = stack_at(xpms_numbers, index);
		if (sprite == NULL) return;
		
		sprite_move(sprite, pos, 793);
		if (sprite_draw(sprite)) return;

		pos += 27;
	}
}
