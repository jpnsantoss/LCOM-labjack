#include "game.h"

int game_init(game_t *game)
{
	game->current_bet = 0;
	game->cards = queue_create(GAME_DECK_AMOUNT * GAME_DECK_SIZE);
	if (card_init()) return 1;
	if (game->cards == NULL) return 1;

	for (int type = 0; type < 4; type++)
	{
		for (int value = 0; value < 13; value++)
		{
			card_t *card = card_create(value, type);
			if (card == NULL)
			{
				queue_delete(&game->cards);
				return 1;
			}

			if (queue_push(game->cards, card))
			{
				free(card);
				queue_delete(&game->cards);
				return 1;
			}
		}
	}

	queue_shuffle(game->cards);

	return 0;
}
