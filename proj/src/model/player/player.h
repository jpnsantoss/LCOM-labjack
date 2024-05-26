#ifndef _LCOM_PLAYER_H_
#define _LCOM_PLAYER_H_

#include <lcom/lcf.h>
#include "../../data_structures/queue/queue.h"
#include "../player/player.h"
#include "../card/card.h"
#include "../font/font.h"

#define PLAYER_STARTING_COINS 100
#define PLAYER_MAX_DECK_SIZE 15

typedef struct {
	uint32_t coins;
	uint32_t bet;
	uint32_t  cards_value;

	queue_t *cards;
} player_t;

int		player_init(player_t *player);
void 	player_destroy(player_t *player);
void	player_draw(font_t *font, player_t *player);


#endif
