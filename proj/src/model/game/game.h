#ifndef _LCOM_GAME_H_
#define _LCOM_GAME_H_

#include <lcom/lcf.h>
#include "../../data_structures/queue.h"
#include "../player/player.h"
#include "../card/card.h"

#define GAME_DECK_SIZE 52
#define GAME_DECK_AMOUNT 4

typedef struct {
	queue_t 	*cards;

	uint32_t 	current_bet;
	uint32_t	round_count;
	uint32_t	card_played_count;
	uint32_t	extra_deck_count;
	uint8_t		playing_id;
	uint8_t		is_multiplayer;

	player_t 	main_player;
	player_t 	other_player;
} game_t;

int		game_init(game_t *game);
void	game_destroy(game_t *game);

#endif
