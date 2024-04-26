#ifndef _LCOM_GRAPHICS_H_
#define _LCOM_GRAPHICS_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>  

//#include "VBE.h"

vbe_mode_info_t mode_info;
uint8_t* frame_buffer;
int (set_graphic_mode)(uint16_t submode);
int (set_frame_buffer)(uint16_t mode);
int (print_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y);
int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

#endif
