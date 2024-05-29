#ifndef _LCOM_PLAYER_H_
#define _LCOM_PLAYER_H_

#include <lcom/lcf.h>
#include "../../data_structures/queue/queue.h"
#include "../player/player.h"
#include "../card/card.h"
#include "../font/font.h"

#define PLAYER_STARTING_COINS 100
#define PLAYER_MAX_DECK_SIZE 15

typedef enum {
	NOT_ENDED,
	PLAYER_WIN,
	PLAYER_LOSS,
	PLAYER_DRAW
} game_over_state_t;

typedef struct {
	uint32_t coins;
	uint32_t bet;
	uint32_t cards_value;

	uint32_t won_coins;
	game_over_state_t game_over_state;

	queue_t *cards;
} player_t;

int		player_init(player_t *player);
void 	player_destroy(player_t *player);
void	player_draw(player_t *player);


#endif
