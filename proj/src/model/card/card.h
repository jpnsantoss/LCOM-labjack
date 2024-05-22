#ifndef _LCOM_CARD_H_
#define _LCOM_CARD_H_

#include <lcom/lcf.h>
#include "../../sprite/sprite.h"
#include "../../assets/cards/cards.h"

typedef enum {
	CLUBS,
	DIAMOND,
	HEARTS,
	SPADES,
} card_type_t;

typedef struct {
	int						value;
	card_type_t 	type;
	sprite_t 			*sprite_base;
} card_t;

sprite_t *card_sprites[4][13];

int card_init();
card_t *card_create(int value, card_type_t type);

#endif
