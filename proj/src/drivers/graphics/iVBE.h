#ifndef _LCOM_IVBE_H_
#define _LCOM_IVBE_H_

#include <lcom/lcf.h>

#define VG_MODE 0x14c

#define AH_FAIL 0x01
#define AH_NOSUPPORT 0x02
#define AH_INVALID 0x03

#define AH_PORT 0x4F
#define AL_TEXTMODE 0x03
#define AL_VBEMODE_SET 0x02
#define BX_LINEAR_FRAME_BUFF BIT(14)

#define AL_DISPLAY_START_CONTROL 0x07
#define BL_SET_DISPLAY_START 0x00

#define DIRECT_COLOR 0x06
#define INDEXED_COLOR 0x105

#endif /* _LCOM_IVBE_H */
