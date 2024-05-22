#ifndef _LCOM_PLAYER_H_
#define _LCOM_PLAYER_H_

#include <lcom/lcf.h>
#include "../../data_structures/queue.h"
#include "../card/card.h"

#define PLAYER_STARTING_COINS 100
#define PLAYER_MAX_DECK_SIZE 20

typedef struct {
	uint32_t coins;
	queue_t *cards;
} player_t;

int		player_init(player_t *player);
void 	player_destroy(player_t *player);

#endif
