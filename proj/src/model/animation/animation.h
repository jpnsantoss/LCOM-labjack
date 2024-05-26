#ifndef _LCOM_ANIMATION_H_
#define _LCOM_ANIMATION_H_

#include <lcom/lcf.h>
#include "../../data_structures/queue/queue.h"
#include "../sprite/sprite.h"

typedef struct {
	queue_t		*frames;
	queue_t		*x;
	queue_t 	*y;

	uint8_t 	loop;
	uint32_t	frame_rate;
	uint32_t	frame_counter;
	uint32_t	frame_index;
} animation_t;

animation_t	*animation_create(uint8_t loop, uint32_t frame_rate, uint32_t frame_amount);
int					animation_add_frame(animation_t *animation, sprite_t *sprite, uint32_t x, uint32_t y);
int					animation_draw(animation_t *animation);
void				animation_run(animation_t *animation);
void				animation_destroy(animation_t *animation);

#endif
