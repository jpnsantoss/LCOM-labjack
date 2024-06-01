#ifndef _LCOM_BANNER_H_
#define _LCOM_BANNER_H_

#include <lcom/lcf.h>
#include "../../drivers/drivers.h"
#include "../font/font.h"

typedef struct {
	char				*msg;

	uint32_t		timeout;
	uint32_t		current_timeout;
} banner_t;

int	banner_init(banner_t *banner);
int	banner_set_message(banner_t *banner, char *msg, uint32_t timeout);
int	banner_update_timeout(banner_t *banner);
int	banner_draw(banner_t *banner, font_t *font);

#endif
