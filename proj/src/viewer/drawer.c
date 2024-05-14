#include "../labjack.h"
#include <lcom/pixmap.h>
#include "../sprites/cursor.h"

int cursor_draw(int x, int y)
{
	return vg_print_xpm(pic1, x, y);
}

int draw_screen(int x, int y)
{
	vg_clear_screen();

	if (cursor_draw(x, y)) return 1;

	return vg_flush_buffer();
}
