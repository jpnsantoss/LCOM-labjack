#ifndef _LCOM_COM_MANAGER_H_
#define _LCOM_COM_MANAGER_H_

#include <lcom/lcf.h>
#include "../../drivers/drivers.h"
#include "../app/app.h"

typedef enum {
	WAITING,
	RECEIVING,
} com_status_t;

typedef struct {
	uint8_t 	msg;
	uint32_t 	timeout;

	uint32_t 	current_timeout;
	int				executed;
	void 			(*onTimeout)(uint8_t, app_t *)
} com_query_t;

typedef enum {
	NO_EVENT,
	PING,
	SEED
} com_event_t;

typedef struct {
	com_status_t	status;

	com_event_t 	current_ev;
	queue_t 			*queries;
	app_t					*app;
} com_manager_t;

com_manager_t *manager;

#endif
