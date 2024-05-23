#include "app.h"
#include "../../assets/cursor.xpm"
#include "../../assets/background.xpm"
#include "../../assets/start.xpm"
#include "../../assets/exit.xpm"

app_t *app_init()
{
	app_t *app = (app_t *) malloc(sizeof(app_t));
	if (app == NULL) return NULL;

	app->state = MAIN_MENU;
	app->game.cards = NULL;
	app->game.main_player.cards = NULL;
	app->game.other_player.cards = NULL;
	
	t_gph gph = vg_get_info();
	sprite_t *sprite = NULL;

  app->cursor = sprite_create((xpm_map_t) cursor_xpm, vg_get_width() / 2, vg_get_height() / 2);
	app->background = sprite_create((xpm_map_t) background_xpm, 0, 0);
	
	app->buttons_main_menu = queue_create(2);
	if (app->buttons_main_menu == NULL) return NULL;

  sprite = sprite_create((xpm_map_t) start_xpm, (gph.x_res / 2) - 75, gph.y_res - 50);
	if (sprite == NULL) return NULL;
	queue_push(app->buttons_main_menu, sprite);

  sprite = sprite_create((xpm_map_t) exit_xpm, (gph.x_res / 2) + 25, gph.y_res - 50);
	if (sprite == NULL) return NULL;
	queue_push(app->buttons_main_menu, sprite);

	app->buttons_game_betting = queue_create(4);
	if (app->buttons_game_betting == NULL) return NULL;

	app->buttons_game_over == queue_create(2);
	if (app->buttons_game_over == NULL) return NULL; 

  return app;
}

void app_update_cursor_pos(app_t *app, mouse_info_t *mouse_info)
{
	if (app == NULL || mouse_info == NULL) return;

  int new_x = app->cursor->x + mouse_info->delta_x;
  int new_y = app->cursor->y - mouse_info->delta_y;
  
	sprite_move(app->cursor, new_x, new_y);
}

void app_destroy(app_t *app)
{
	if (app == NULL) return;

	queue_destroy(&app->buttons_main_menu, sprite_queue_destroy);
	game_destroy(&app->game);
	free(app);
}
