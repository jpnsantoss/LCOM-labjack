#ifndef _LCOM_CARD_H_
#define _LCOM_CARD_H_

#include <lcom/lcf.h>

typedef enum {
	CLUBS,
	HEARTS,
	SPADES,
	DIAMONDS
} card_type_t;

typedef struct {
	char					*name;
	int						value;
	card_type_t 	type;
	xpm_image_t 	xpm;
} card_t;

#endif