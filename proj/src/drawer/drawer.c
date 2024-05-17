#include "drawer.h"
#include "../state/state.h"
int draw_state() {
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

int draw_screen() {
	vg_clear_screen();
	vg_draw_state();

  vg_print_xpm(cursor, mouse_get_x(), mouse_get_y());

	vg_flush_buffer();
}