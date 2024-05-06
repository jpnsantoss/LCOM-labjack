#ifndef _LCOM_CARD_H_
#define _LCOM_CARD_H_

#include <lcom/lcf.h>

typedef enum card_type_e {
	CLUBS,
	HEARTS,
	SPADES,
	DIAMONDS
} card_type_t;

typedef struct card_s {
	char					*name;
	int						value;
	card_type_t 	type;
	xpm_image_t 	xpm;
} card_t;

#endif