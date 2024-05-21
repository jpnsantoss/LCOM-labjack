#ifndef _LCOM_DRIVERS_H_
#define _LCOM_DRIVERS_H_

#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "input/i8042.h"
#include "timer/i8254.h"
#include "graphics/iVBE.h"
#include "serial_port/iUART.h"
#include "serial_port/serial_proto.h"
#include "../data_structures/queue.h"
#include <stdbool.h>
#include "../state/state.h"

#define min(a,b) (((a) < (b)) ? (a) : (b))
#define MAX_TRIES 10

typedef enum s_colormode {
	indexed,
	direct,
	unknown
} t_colormode;

typedef struct s_gph {
	uint8_t *video_mem;
	uint8_t *frame_buffer;

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
} t_gph;

typedef struct packet mouse_info_t;

// timer
int (timer_subscribe_int)(uint8_t *bit_no);
int (timer_unsubscribe_int)();
void (timer_int_handler)();

int (timer_get_conf)(uint8_t timer, uint8_t *st);
int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field);
int (timer_set_frequency)(uint8_t timer, uint32_t freq);

// mouse
int mouse_subscribe_int(uint8_t *bit_no);
int mouse_unsubscribe_int();
void (mouse_ih)();
int mouse_init(uint8_t *bit_no);

void mouse_fill_packet(uint8_t *bytes, struct packet *pp);
int mouse_read_packet(mouse_info_t *info);

// keyboard
int kbd_subscribe_int(uint8_t *bit_no);
int kbd_unsubscribe_int();
void (kbc_ih)();

// kbc
int kbc_write_input(uint8_t port, uint8_t input);
int kbc_read_output(uint8_t port, uint8_t *output, bool mouse);
int kbc_write(uint8_t intent, bool mouse);

// graphics
int	vg_init_mode();
int	vg_enter_graphic_mode(uint16_t mode);
int	vg_map_memory(uint16_t mode);
int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, 
					uint16_t height, uint32_t color);
int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
int	vg_print_xpm(xpm_map_t xpm, uint16_t x, uint16_t y);
t_gph vg_get_info();
void vg_clear_screen();
int (vg_clean)();
int (vg_flush_buffer)();
unsigned vg_get_width();
unsigned vg_get_height();

uint32_t direct_color(t_gph gph, int x, int y, uint32_t first, uint32_t step);

// uart
int (uart_setup)(int bit_rate);
int (uart_subscribe_int)(uint8_t *bit_no);
int (uart_unsubscribe_int)();
void (uart_ih)();
int	(uart_set_bit_rate)(int com_num, int rate);
int (uart_write_msg)(int com_num, uint8_t msg);
int (uart_disable)();
int (uart_reset)(int base_addr);

// utils
int (util_get_LSB)(uint16_t val, uint8_t *lsb);
int (util_get_MSB)(uint16_t val, uint8_t *msb);
int (util_sys_inb)(int port, uint8_t *value);

#endif
