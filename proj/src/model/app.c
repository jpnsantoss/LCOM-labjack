#include "app.h"
#include "../assets/cursor.xpm"

app_t app;

app_t *app_init() {
    app.cursor = sprite_create((xpm_map_t) cursor_xpm, vg_get_width() / 2, vg_get_height() / 2);
    return &app;
}
