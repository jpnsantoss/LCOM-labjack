#ifndef _LCOM_SPRITE_H_
#define _LCOM_SPRITE_H_

#include <lcom/lcf.h>

typedef struct {
	uint32_t		x;
	uint32_t		y;
	xpm_image_t img;
	uint8_t			*map;
} sprite_t;

sprite_t *sprite_create(xpm_map_t map, uint32_t x, uint32_t y);
void			sprite_destroy(sprite_t *sprite);
int				sprite_draw(sprite_t *sprite);
int				sprite_draw_rotate(sprite_t *sprite);
int				sprite_move(sprite_t *sprite, uint32_t x, uint32_t y);
int				sprite_colides(sprite_t *sprite1, sprite_t *sprite2);

#endif
