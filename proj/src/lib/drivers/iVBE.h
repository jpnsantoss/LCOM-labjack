#ifndef _LCOM_IVBE_H_
#define _LCOM_IVBE_H_

#include <lcom/lcf.h>

#define AH_FAIL 0x01
#define AH_NOSUPPORT 0x02
#define AH_INVALID 0x03

#define AH_PORT 0x4F
#define AL_TEXTMODE 0x03
#define AL_VBEMODE_SET 0x02
#define AL_VBEMODE_INFO 0x01
#define AL_VBECTRL_INFO 0x00

#define DIRECT_COLOR 0x06
#define INDEXED_COLOR 0x105

#endif /* _LCOM_IVBE_H */
