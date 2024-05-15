#ifndef _LCOM_EV_LISTENER_H_
#define _LCOM_EV_LISTENER_H_

#include "../drivers/drivers.h"
#include "../model/game.h"
#include "../model/app.h"

int	handle_interrupt(game_t *game, ev_listener_t event);

#endif
