#include "game.h"

int game_add_deck(queue_t *cards, bool shuffle)
{
	for (int type = 0; type < CARD_TYPE_NUM; type++)
	{
		for (int value = 0; value < CARD_VALUE_NUM; value++)
		{
			card_t *card = card_create(value, type);
			if (card == NULL) return 1;

			if (queue_push(cards, card))
			{
				free(card);
				return 1;
			}
		}
	}

	if (shuffle) queue_shuffle(cards);

	return 0;
}

int game_init(game_t *game)
{
	if (game == NULL) return 1;
	if (card_base_init())
	{
		game_destroy(game);
		return 1;
	}

	game->card_played_count = 0;
	game->extra_deck_count = 0;
	game->is_multiplayer = 0;
	game->playing_id = 0;
	game->card_theme = 0;

	game->cards = queue_create(GAME_DECK_AMOUNT * GAME_DECK_SIZE);
	if (game->cards == NULL) 
	{
		game_destroy(game);
		return 1;
	}

	for (int i = 0; i < GAME_DECK_AMOUNT; i++)
	{
		game_add_deck(game->cards, true);
	}

	if (player_init(&game->main_player) || player_init(&game->other_player))
	{
		game_destroy(game);
		return 1;
	}

	return 0;
}

void game_destroy(game_t *game)
{
	if (game == NULL) return;

	player_destroy(&game->main_player);
	player_destroy(&game->other_player);

	if (game->cards != NULL)
	{
		queue_destroy(&game->cards, card_queue_destroy);
	}
}

int game_draw_deck(game_t *game)
{
	if (game == NULL) return 1;

	sprite_t *back = sprite_create(game->card_theme ? back_blue_1_xpm : back_red_1_xpm);
	if (back == NULL) return 1;

	for (size_t i = 0; i < MIN(game->cards->curr_size, GAME_DECK_DRAW_AMOUNT); i++)
	{
		uint32_t x = GAME_DECK_DRAW_X + (i + 1) * back->img.width * 0.02;
		uint32_t y = GAME_DECK_DRAW_Y - (i + 1) * back->img.height * 0.1;
		sprite_move(back, x, y);
		if (sprite_draw(back)) return 1;
	}

	return 0;
}
