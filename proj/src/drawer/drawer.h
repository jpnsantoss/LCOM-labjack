#ifndef DRAWER_H
#define DRAWER_H

#include "../drivers/drivers.h"
#include "../assets/cursor.xpm"
#include "../model/app/app.h"

void draw_state(app_t *app);
void draw_screen(app_t *app);
void draw_button_set(queue_t *buttons);

#endif
