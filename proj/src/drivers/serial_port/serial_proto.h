#ifndef _LCOM_SERIAL_PROTO_H_
#define _LCOM_SERIAL_PROTO_H_

#include <lcom/lcf.h>

#define SPROTO_BEGIN		0x55
#define SPROTO_END			0x88
#define SPROTO_MSG_SIZE 1
#define SPROTO_SIZE			3

#define SPROTO_OK				0xFA
#define SPROTO_KO				0xFC
#define SPROTO_ERR			0xFF

#endif /* _LCOM_SERIAL_PROTO_H */
