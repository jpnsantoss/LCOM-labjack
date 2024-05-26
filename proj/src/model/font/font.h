#ifndef _LCOM_FONT_H_
#define _LCOM_FONT_H_

#include "../../data_structures/queue.h"
#include "../../assets/charxpms/chars.h"
#include "../sprite/sprite.h"

typedef struct {
	queue_t		*to_draw;
	
	// all
  queue_t 	*xpms_numbers;
  queue_t 	*xpms_letters;

} font_t;

int font_init(font_t *font);
int font_print_char(font_t *font, char c, uint32_t x, uint32_t y);
int font_print_str(font_t *font, char *str, uint32_t x, uint32_t y);
int font_print_number(font_t *font, long num, uint32_t x, uint32_t y);
int	font_draw(font_t *font);
void font_destroy(font_t *font);

#endif