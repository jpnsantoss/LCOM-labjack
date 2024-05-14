#include "../labjack.h"
#include <lcom/pixmap.h>
#include "../sprites/cursor.h"

int cursor_draw(int x, int y)
{
	vg_clear_screen();
	printf("%d, %d\n", x, y);
	return vg_print_xpm(pic1, x, y);
}
