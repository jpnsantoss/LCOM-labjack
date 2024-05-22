#ifndef _LCOM_GAME_H_
#define _LCOM_GAME_H_

#include <lcom/lcf.h>
#include "../data_structures/queue.h"
#include "player.h"

typedef struct {
	queue_t *all_cards;
	queue_t *shuffle_cards;

	uint32_t current_bet;
	player_t player;
	
} game_t;

#endif
