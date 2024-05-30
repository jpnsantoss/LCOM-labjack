#ifndef _LCOM_GAME_H_
#define _LCOM_GAME_H_

#include <lcom/lcf.h>

#include "../../data_structures/queue/queue.h"
#include "../player/player.h"
#include "../card/card.h"
#include "../../assets/cards/back_red_1.xpm"
#include "../animation/animation.h"

#define GAME_DECK_SIZE 52
#define GAME_DECK_AMOUNT 2
#define GAME_DECK_DRAW_AMOUNT 4
#define GAME_DECK_DRAW_X 650
#define GAME_DECK_DRAW_Y 250

typedef struct {
	sprite_t	*card_back;

	queue_t 	*cards;
	queue_t		*dealer;

	animation_t *curr_anim;

	uint32_t	dealer_value;
	
	uint32_t	round_count;
	uint32_t	card_played_count;
	uint32_t	extra_deck_count;

	uint8_t		playing_id;
	uint8_t		multiplayer;
	uint8_t		card_theme;

	uint8_t		input_select;
	uint8_t		dealer_turn;

	player_t 	main_player;
	player_t 	other_player;
} game_t;

int				game_init(game_t *game);
void			game_destroy(game_t *game);
int 			game_add_deck(queue_t *cards, bool shuffle);

int 			game_draw_deck(game_t *game);
int				game_draw_dealer(game_t *game, font_t *font);
int				game_give_card(queue_t *deck, queue_t *receiver);
uint32_t	game_get_cards_value(queue_t *cards);

#endif
