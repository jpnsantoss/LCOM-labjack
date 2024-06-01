#ifndef _LCOM_ANIMATION_H_
#define _LCOM_ANIMATION_H_

#include "../../data_structures/queue/queue.h"
#include "../sprite/sprite.h"
#include <lcom/lcf.h>

typedef struct {
  queue_t *frames;
  queue_t *rotate;
  queue_t *x;
  queue_t *y;

  uint32_t frame_index;

  void (*on_end)(void *);
} animation_t;

animation_t *animation_create(uint32_t frame_amount, void (*on_end)(void *));
int animation_add_frame(animation_t *animation, sprite_t *sprite, uint32_t x, uint32_t y, bool rotate);
int animation_draw(animation_t *animation);
void animation_run(animation_t **animation, void *ptr);
int  animation_running(animation_t *animation);
void animation_destroy(animation_t *animation);

#endif
