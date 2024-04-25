#ifndef _LCOM_SERIAL_PROTO_H_
#define _LCOM_SERIAL_PROTO_H_

#include <lcom/lcf.h>

#define SPROTO_BEGIN	0xFA
#define SPROTO_END		0xFB
#define SPROTO_MSG_SIZE 3
#define SPROTO_SIZE		5

#define SPROTO_OK		0xFC
#define SPROTO_KO		0xFD
#define SPROTO_ERR		0xFE

#endif /* _LCOM_SERIAL_PROTO_H */
