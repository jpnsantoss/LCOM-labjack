#ifndef _LCOM_CURSOR_H_
#define _LCOM_CURSOR_H_

#include <lcom/lcf.h>

#include "../../drivers/drivers.h"
#include "../sprite/sprite.h"
#include "../../assets/cursor.xpm"
#include "../../assets/hand.xpm"

typedef enum {
	POINTER,
	HAND	
} cursor_state_t;

typedef struct {
	uint32_t				x;
	uint32_t				y;
	sprite_t 				*pointer;
	sprite_t 				*hand;

	cursor_state_t	state;
} cursor_t;

int		cursor_init(cursor_t *cursor);
int		cursor_move(cursor_t *cursor, uint32_t x, uint32_t y);
int		cursor_draw(cursor_t *cursor);
int		cursor_collision(cursor_t *cursor, sprite_t *sprite);
void	cursor_destroy(cursor_t *cursor);

#endif
