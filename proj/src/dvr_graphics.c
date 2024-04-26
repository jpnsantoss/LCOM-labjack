#include <lcom/lcf.h>
#include "dvr_graphics.h"
#include <math.h>

int (set_graphic_mode)(uint16_t submode){
    reg86_t reg86;
    memset(&reg86, 0, sizeof(reg86));
    reg86.intno=0x10;
    reg86.ah=0x4F;
    reg86.al=0x02;
    reg86.bx = submode | BIT(14);
    int r = sys_int86(&reg86);
    if(r!=OK){
        printf("set graphic mode error");
        return 1;
    }
    return 0;
}


int (set_frame_buffer)(uint16_t mode){
   memset(&mode_info, 0 , sizeof(mode_info));
  int r=vbe_get_mode_info(mode, &mode_info);
  if(r!=OK){return r;}

  unsigned int bytes_per_pixel = (mode_info.BitsPerPixel +7)/8;
  unsigned int frame_size = bytes_per_pixel * mode_info.XResolution * mode_info.YResolution;

  struct minix_mem_range physic_addresses;
  physic_addresses.mr_base = mode_info.PhysBasePtr; 
  physic_addresses.mr_limit = physic_addresses.mr_base + frame_size; 

  if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &physic_addresses)) {
    printf("Physical memory allocation error\n");
    return 1;
  }

  frame_buffer = vm_map_phys(SELF, (void*) physic_addresses.mr_base, frame_size);
  if (frame_buffer == NULL) {
    printf("Virtual memory allocation error\n");
    return 1;
  }

return 0;
}

int (print_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {

  xpm_image_t img;

  uint8_t *colors = xpm_load(xpm, XPM_INDEXED, &img);

  for (int j = 0 ; j < img.height ; j++) {
    for (int i = 0 ; i < img.width ; i++) {
      if (vg_draw_pixel(x + i, y + j, *colors) != 0) return 1;
      colors++;
    }
  }
  return 0;
}

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {

  if(x > mode_info.XResolution || y > mode_info.YResolution) return 1;
  
  unsigned BytesPerPixel = (mode_info.BitsPerPixel + 7) / 8;

  unsigned int index = (mode_info.XResolution * y + x) * BytesPerPixel;

  if (memcpy(&frame_buffer[index], &color, BytesPerPixel) == NULL) return 1;

  return 0;
}
