#include "app.h"

#include "../../assets/background.xpm"
#include "../../assets/buttons/start.xpm"
#include "../../assets/buttons/exit.xpm"
#include "../../assets/buttons/hit.xpm"
#include "../../assets/buttons/double.xpm"
#include "../../assets/buttons/stand.xpm"
#include "../../assets/buttons/surrender.xpm"

app_t *app_init()
{
	app_t *app = (app_t *) malloc(sizeof(app_t));
	if (app == NULL) return NULL;

	app->state = MAIN_MENU;
	app->game.cards = NULL;
	app->game.main_player.cards = NULL;
	app->game.other_player.cards = NULL;

	if (cursor_init(&app->cursor)) return NULL;

	app->background = sprite_create((xpm_map_t) background_xpm);
	if (app->background == NULL) return NULL;

	if (app_buttons_main_menu_init(&app->buttons_main_menu)) return NULL;

	if (app_buttons_game_playing_init(&app->buttons_game_playing)) return NULL; 

	app->xpms_numbers = stack_create(6);
	if (app->xpms_numbers == NULL) return NULL;

	sprite_t *sprite = sprite_create(hand_xpm);
	app->card_loop = animation_create(true, 30, 600);
	if (app->card_loop == NULL) return NULL;

	for (int i = 0; i < 600; i++)
	{
		if (animation_add_frame(app->card_loop, sprite, 200 + i, 200)) exit(0);
	}
	
  return app;
}

int app_buttons_game_playing_init(queue_t** queue)
{	
	sprite_t *sprite = NULL;
	
	if (queue == NULL) return 1;
	*queue = queue_create(4);
	if (*queue == NULL) return 1;

	sprite = sprite_create((xpm_map_t) hit_xpm);
	if (sprite == NULL) return 1;
	queue_push(*queue, sprite);

	sprite = sprite_create((xpm_map_t) stand_xpm);
	if (sprite == NULL) return 1;
	queue_push(*queue, sprite);

	sprite = sprite_create((xpm_map_t) double_xpm);
	if (sprite == NULL) return 1;
	queue_push(*queue, sprite);
	
	sprite = sprite_create((xpm_map_t) surrender_xpm);
	if (sprite == NULL) return 1;
	queue_push(*queue, sprite);

	return 0;
}

int	app_buttons_main_menu_init(queue_t** queue)
{
	sprite_t *sprite = NULL;

	if (queue == NULL) return 1;
	*queue = queue_create(2);
	if (*queue == NULL) return 1;

  sprite = sprite_create((xpm_map_t) start_xpm);
	if (sprite == NULL) return 1;
	queue_push(*queue, sprite);

  sprite = sprite_create((xpm_map_t) exit_xpm);
	if (sprite == NULL) return 1;
	queue_push(*queue, sprite);

	return 0;
}

void app_destroy(app_t *app)
{
	if (app == NULL) return;

	queue_destroy(&app->buttons_main_menu, sprite_queue_destroy);
	queue_destroy(&app->buttons_game_playing, sprite_queue_destroy);
	stack_destroy(&app->xpms_numbers, sprite_queue_destroy);
	game_destroy(&app->game);
	cursor_destroy(&app->cursor);
	free(app);
}
