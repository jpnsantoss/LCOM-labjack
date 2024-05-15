#ifndef _LCOM_GAME_H_
#define _LCOM_GAME_H_

#include <lcom/lcf.h>
#include "../data_structures/queue.h"

typedef struct game_s {
	queue_t *cards;
} game_t;

#endif
