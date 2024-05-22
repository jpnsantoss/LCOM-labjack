#include "player.h"

int player_init(player_t *player)
{
	if (player == NULL) return 1;

	player->coins = PLAYER_STARTING_COINS;
	player->cards = queue_create(PLAYER_MAX_DECK_SIZE);

	return player->cards == NULL;
}

void player_destroy(player_t *player)
{
	if (player == NULL) return;
	if (player->cards == NULL) return;
	
	queue_destroy(&player->cards, card_queue_destroy);
}
