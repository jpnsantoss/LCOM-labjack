#ifndef _LCOM_DRIVER_GRAPHICS_H_
#define _LCOM_DRIVER_GRAPHICS_H_

#include <lcom/lcf.h>
#include "iVBE.h"

typedef enum {
	indexed,
	direct,
	unknown
} colormode_t;

typedef struct {
	uint8_t *frame_buffer[3];
	bool needs_redraw;
	int selectedNum;

	unsigned x_res;
	unsigned y_res;
	unsigned bits_per_pixel;
	unsigned bytes_per_pixel;

	unsigned red_mask_size;
	unsigned red_field_pos;
	unsigned green_mask_size;
	unsigned green_field_pos;
	unsigned blue_mask_size;
	unsigned blue_field_pos;

	bool direct_color;
} gph_t;

int	vg_init_mode();
int	vg_enter_graphic_mode(uint16_t mode);
int	vg_map_memory(uint16_t mode);
int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, 
					uint16_t height, uint32_t color);
int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
int(vg_draw_vline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
int vg_draw_border(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color, uint8_t thickness);

gph_t vg_get_info();
int (vg_flip)();
unsigned vg_get_width();
unsigned vg_get_height();
void vg_set_redraw();
int vg_has_redraw();

#endif
