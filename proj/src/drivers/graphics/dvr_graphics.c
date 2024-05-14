#include "../drivers.h"

static t_gph gph;

t_gph vg_get_info()
{
	return gph;
}

int	vg_map_memory(uint16_t mode)
{
	struct minix_mem_range mr;
	vbe_mode_info_t mode_info;

	memset(&mode_info, 0, sizeof(vbe_mode_info_t));
	memset(&gph, 0, sizeof(t_gph));

	if (vbe_get_mode_info(mode, &mode_info))
		return 1;
	
	gph.x_res = mode_info.XResolution;
	gph.y_res = mode_info.YResolution;
	gph.bits_per_pixel = mode_info.BitsPerPixel;
	gph.bytes_per_pixel = (gph.bits_per_pixel + 7) / 8;

	gph.direct_color = mode_info.MemoryModel == DIRECT_COLOR;

	gph.red_mask_size = mode_info.RedMaskSize;
	gph.red_field_pos = mode_info.RedFieldPosition;
	gph.green_mask_size = mode_info.GreenMaskSize;
	gph.green_field_pos = mode_info.GreenFieldPosition;
	gph.blue_mask_size = mode_info.BlueMaskSize;
	gph.blue_field_pos = mode_info.BlueFieldPosition;

	unsigned int screen_size = gph.x_res * gph.y_res * gph.bytes_per_pixel;
	
	mr.mr_base = (phys_bytes) mode_info.PhysBasePtr;
	mr.mr_limit = mr.mr_base + screen_size;

	if(sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))
		return 1;
	
	gph.video_mem = vm_map_phys(SELF, (void *)mr.mr_base, screen_size);
	gph.frame_buffer = (uint8_t *) malloc(screen_size);

   	return gph.video_mem == MAP_FAILED;
}

int (vg_flush_buffer)()
{
	memcpy(gph.video_mem, gph.frame_buffer, gph.x_res * gph.y_res * gph.bytes_per_pixel);
	return 0;
}

int (vg_clean)()
{
	free(gph.frame_buffer);
	return vg_exit();
}

int	vg_enter_graphic_mode(uint16_t mode)
{
	reg86_t r;
	memset(&r, 0, sizeof(reg86_t));
	r.intno = 0x10;
	r.ah = 0x4F;
	r.al = 0x02;
	r.bx = BIT(14) | mode;

	return sys_int86(&r);
}

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color)
{	
	if (x >= gph.x_res || y >= gph.y_res)
		return 1;
	
	uint64_t pos = (gph.x_res * y + x) * gph.bytes_per_pixel;

	return memcpy(gph.frame_buffer + pos, &color, gph.bytes_per_pixel) == 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color)
{
	for (uint16_t i = 0; i < len; i++)
			if (vg_draw_pixel(x + i, y, color))
				return 1;
	return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, 
					uint16_t height, uint32_t color)
{
	for (uint16_t i = 0; i < height; i++)
	{
		if (vg_draw_hline(x, y + i, width, color))
			return 1;
	}

	return 0;
}

int	vg_print_xpm(xpm_map_t xpm, uint16_t x, uint16_t y)
{
	xpm_image_t img;

	uint8_t *sprite = xpm_load(xpm, XPM_INDEXED, &img);
	for (int j = 0; j < img.height; j++)
	{
		for (int i = 0; i < img.width; i++)
		{
			if (vg_draw_pixel(x + i, y + j, *sprite))
				return 1;
			sprite++;
		}
	}
	return 0;
}

// Pattern auxiliary method 
uint32_t direct_aux(uint32_t first, uint32_t mask_size, uint32_t field_pos)
{
	return ((1 << mask_size) - 1) & (first >> field_pos);
}

// Pattern auxiliary method 
uint32_t direct_color(t_gph gph, int x, int y, uint32_t first, uint32_t step)
{
	uint32_t red = direct_aux(first, gph.red_mask_size, gph.red_field_pos);
	red += y * step;
	red %= 1 << gph.red_mask_size;

	uint32_t green = direct_aux(first, gph.green_mask_size, gph.green_field_pos);
	green += x * step;
	green %= 1 << gph.green_mask_size;

	uint32_t blue = direct_aux(first, gph.blue_mask_size, gph.blue_field_pos);
	blue += (x + y) * step;
	blue %= 1 << gph.blue_mask_size;

	return red << gph.red_field_pos | green << gph.green_field_pos | blue << gph.blue_field_pos;
}

void vg_clear_screen()
{
    uint32_t color = 0x000000; // Cor preta (ou qualquer outra cor desejada)

    // Iterar sobre todos os pixels do frame buffer e definir sua cor como a cor de fundo
    for (uint32_t y = 0; y < gph.y_res; y++) {
        for (uint32_t x = 0; x < gph.x_res; x++) {
            // Calcular o índice do pixel no frame buffer
            vg_draw_pixel(x, y, color); 
        }
    }
}
