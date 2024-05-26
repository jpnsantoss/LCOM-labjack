#ifndef _LCOM_COM_MANAGER_H_
#define _LCOM_COM_MANAGER_H_

#include <lcom/lcf.h>
#include "../../drivers/drivers.h"

typedef enum {
	WAITING,
	RECEIVING,
} com_status_t;

typedef enum {
	NO_EVENT,
	PING,
	SEED,
	GAME_HIT,
	GAME_BET,

} com_event_t;

typedef struct {
	com_status_t status;

	com_event_t current_ev;
} com_manager_t;

#endif
