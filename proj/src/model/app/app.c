#include "app.h"
#include "../../assets/cursor.xpm"
#include "../../assets/background.xpm"
#include "../../assets/start.xpm"
#include "../../assets/exit.xpm"

app_t *app_init()
{
	app_t *app = (app_t *) malloc(sizeof(app_t));
	if (app == NULL) return NULL;

  app->cursor = sprite_create((xpm_map_t) cursor_xpm, vg_get_width() / 2, vg_get_height() / 2);
	app->background = sprite_create((xpm_map_t) background_xpm, 0, 0);
  app->play_button = sprite_create((xpm_map_t) start_xpm, (vg_get_width() / 2) - 55, 720);
  app->exit_button = sprite_create((xpm_map_t) exit_xpm, (vg_get_width() / 2) + 35, 720);

  return app;
}

void updateCursorPos(app_t *app, mouse_info_t *mouse_info) {
    int new_x = app->cursor->x + mouse_info->delta_x;
    int new_y = app->cursor->y - mouse_info->delta_y;

    sprite_move(app->cursor, new_x, new_y);
}
