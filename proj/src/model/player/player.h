#ifndef _LCOM_PLAYER_H_
#define _LCOM_PLAYER_H_

#include <lcom/lcf.h>
#include "../../data_structures/queue.h"

typedef struct {
	uint32_t coins;
	queue_t *cards;
} player_t;

#endif
