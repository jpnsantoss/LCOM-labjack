#include "com_manager.h"

static com_packet_t curr_packet;
static uint8_t bytes[7];
static int idx = 0;
static int full_packet = 0;

int com_add_byte(uint8_t byte)
{
	printf("idx: %d, byte:%d\n", idx, byte);
	full_packet = 0;
	if (idx == 0 && byte == PROTO_START)
	{
		bytes[idx] = byte;
		idx++;
		return 0;
	}

	if (idx > 0 && idx < 6)
	{
		bytes[idx] = byte;
		idx++;
		return 0;
	}

	if (idx == 6 && byte == PROTO_END)
	{
		bytes[idx] = byte;
		idx = 0;
		curr_packet.type = bytes[1];
		curr_packet.data = bytes[5] << 24 | bytes[4] << 16 | bytes[3] << 8 | bytes[2];
		full_packet = 1;
		return 1;
	}

	idx = 0;
	return 0;
}

int	com_send_msg(com_msg_t type, uint32_t content)
{
	if (uart_send_byte(PROTO_START)) return 1;
	if (uart_send_byte(type)) return 1;
	if (uart_send_byte((uint8_t) content)) return 1;
	if (uart_send_byte((uint8_t) (content >> 8))) return 1;
	if (uart_send_byte((uint8_t) (content >> 16))) return 1;
	if (uart_send_byte((uint8_t) (content >> 24))) return 1;
	if (uart_send_byte(PROTO_END)) return 1;

	printf("type %d\ncontent: %d\nbytes: %d, %d, %d, %d\nall sent!\n\n", type, content, (uint8_t)content, (content >> 8) & 0xFF, 
		(content >> 16) & 0xFF, (content >> 24) & 0xFF);
	return 0;
}

void com_handle_packet(app_t *app)
{
	if (full_packet == 0) return;

	char buff[35];

	switch (curr_packet.type) {
    case PROTO_NOTIFY_WIN:
    	snprintf(buff, 30, "A player has won ~%zu", curr_packet.data);
      break;
    case PROTO_NOTIFY_LOSS:
			strncpy(buff, "A player has lost", 18);
      break;
    case PROTO_NOTIFY_DRAW:
			strncpy(buff, "A player tied against the dealer", 33);
      break;
    default:
			strncpy(buff, "Unrecognized notification", 26);
      break;
  }

	//strcpy(buff, "sprintf is ass");
	//printf("msg: %s\ntype: %d\ndata: %d\n", buff, curr_packet.type, curr_packet.data);
	banner_set_message(&app->banner, buff, 120);
}
