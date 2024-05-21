#include "drawer.h"
#include "../state/state.h"
#include "../model/app.h"
void draw_state() {
	switch(get_state()) {
		case MAIN_MENU:
		
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

void draw_screen(app_t *app) {
	vg_clear_screen();
	draw_state();

  sprite_draw(app->cursor);
	vg_draw_rectangle(10, 10, 200, 200, 0xffffff);

	vg_flush_buffer();
}
