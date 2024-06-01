#ifndef _LCOM_COM_MANAGER_
#define _LCOM_COM_MANAGER_

#include <lcom/lcf.h>
#include "../../drivers/drivers.h"
#include "../app/app.h"

#define PROTO_START	0xFE
#define PROTO_END		0xFF

typedef enum {
	PROTO_NOTIFY_NONE,
	PROTO_NOTIFY_WIN,
	PROTO_NOTIFY_LOSS,
	PROTO_NOTIFY_DRAW,
	PROTO_NOTIFY_SURRENDER
} com_msg_t;

typedef struct {
	com_msg_t type;
	uint32_t data;
} com_packet_t;

int com_add_byte(uint8_t byte);
int	com_send_msg(com_msg_t type, uint32_t content);
void com_handle_packet(app_t *app);

#endif
