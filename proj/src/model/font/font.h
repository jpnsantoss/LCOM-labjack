#ifndef _LCOM_FONT_H_
#define _LCOM_FONT_H_

#include "../../data_structures/queue/queue.h"
#include "../../assets/font/font.h"
#include "../sprite/sprite.h"

typedef struct {
  queue_t     *xpms_numbers;
  queue_t     *xpms_letters;
	sprite_t		*two_dots;
	sprite_t		*euro;
} font_t;

int		font_init(font_t *font);
void	font_print_char(font_t *font, char c, uint32_t x, uint32_t y, uint32_t color);
void	font_print_str(font_t *font, char *str, uint32_t x, uint32_t y, uint32_t color);
void	font_print_number(font_t *font, uint32_t num, uint32_t x, uint32_t y, uint32_t color);
void	font_destroy(font_t *font);

#endif
