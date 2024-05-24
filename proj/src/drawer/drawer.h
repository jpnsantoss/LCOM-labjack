#ifndef DRAWER_H
#define DRAWER_H

#include "../drivers/drivers.h"
#include "../model/app/app.h"

void draw_state(app_t *app);
void draw_screen(app_t *app);
void draw_button_set(queue_t *buttons);
void draw_number(queue_t *xpms_numbers);

#endif
