#ifndef _LCOM_CARD_H_
#define _LCOM_CARD_H_

#include <lcom/lcf.h>
#include "../sprite/sprite.h"
#include "../../assets/cards/cards.h"
#include "../../data_structures/queue.h"

#define CARD_TYPE_NUM 4
#define CARD_VALUE_NUM 13

typedef enum {
	CLUBS,
	DIAMOND,
	HEARTS,
	SPADES,
} card_type_t;

typedef struct {
	int						value;
	int						is_double;
	card_type_t 	type;
	sprite_t 			*sprite_base;
} card_t;

sprite_t *card_sprites[CARD_TYPE_NUM][CARD_VALUE_NUM];

int			card_base_init();
void		card_base_destroy();
void		card_queue_destroy(void *card);
void		card_destroy(card_t *card);
card_t	*card_create(int value, card_type_t type);

#endif
