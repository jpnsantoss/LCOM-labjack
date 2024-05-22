#include "app.h"
#include "../assets/cursor.xpm"
#include "../assets/background.xpm"
#include "../assets/start.xpm"
#include "../assets/exit.xpm"

app_t app;

app_t *app_init() {
    app.cursor = sprite_create((xpm_map_t) cursor_xpm, vg_get_width() / 2, vg_get_height() / 2);
		app.background = sprite_create((xpm_map_t) background_xpm, 0, 0);
        app.play_button = sprite_create((xpm_map_t) start_xpm, (vg_get_width() / 2) - 55, 720);
        app.exit_button = sprite_create((xpm_map_t) exit_xpm, (vg_get_width() / 2) + 35, 720);
    //app.exit_button = sprite_create((xpm_map_t) exit_xpm, (vg_get_width() / 2) + 35, 720);

    return &app;
}

void updateCursorPos(mouse_info_t *mouse_info) {
    int new_x = app.cursor->x + mouse_info->delta_x;
    int new_y = app.cursor->y - mouse_info->delta_y;

    /*if(new_x < 0 || mouse_info->x_ov) {
        new_x = 0;
    }
    else if(new_x > 800 || mouse_info->x_ov) {
        new_x = 800;
    }

    if(new_y < 0 || mouse_info->y_ov) {
        new_y = 0;
    }
    else if(new_y > 600 || mouse_info->y_ov) {
        new_y = 600;
    }*/

    sprite_move(app.cursor, new_x, new_y);
}
