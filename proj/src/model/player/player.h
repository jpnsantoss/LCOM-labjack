#ifndef _LCOM_PLAYER_H_
#define _LCOM_PLAYER_H_

#include <lcom/lcf.h>
#include "../../data_structures/queue.h"
#include "../player/player.h"
#include "../card/card.h"

#define PLAYER_STARTING_COINS 100
#define PLAYER_MAX_DECK_SIZE 20
#define PLAYER_DRAW_DECK_Y_OFFSET 0.1
#define PLAYER_DRAW_DECK_X_OFFSET 0.5
#define PLAYER_DRAW_DECK_DOUBLE_X_OFFSET 5
#define PLAYER_DRAW_DECK_DOUBLE_Y_OFFSET 5

typedef struct {
	uint32_t coins;
	queue_t *cards;
} player_t;

int		player_init(player_t *player);
void 	player_destroy(player_t *player);
void	player_draw(player_t *player);
int		player_give_card(queue_t *deck, player_t *player, int is_double);

#endif
