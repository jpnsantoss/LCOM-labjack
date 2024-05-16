#include "sprite.h"
#include "../drivers/drivers.h"

sprite_t *sprite_create(xpm_map_t map, uint32_t x, uint32_t y)
{
	sprite_t *sprite = (sprite_t *) malloc(sizeof(sprite_t));
	if (sprite == NULL) return NULL;

	(void)xpm_load(map,  XPM_8_8_8_8, &sprite->img);
	if (sprite->img.bytes == NULL)
	{
		free(sprite);
		return NULL;
	}

	sprite->x = x;
	sprite->y = y;

	return sprite;
}

void sprite_delete(sprite_t *sprite)
{
	free(sprite->img.bytes);
	sprite->img.bytes = NULL;
}

int	sprite_draw(sprite_t *sprite)
{
	uint8_t *map = sprite->img.bytes;

	for (int j = 0; j < sprite->img.height; j++)
	{
		for (int i = 0; i < sprite->img.width; i++)
		{
			if (*map == xpm_transparency_color(sprite->img.type))
			{
				map++;
				continue;
			} 

			if (vg_draw_pixel(sprite->x + i, sprite->y + j, *map)) return 1;
			map++;
		}
	}
	return 0;
}

int sprite_move(sprite_t *sprite, int x, int y)
{
	if (x == 0 && y == 0) return 1;

	x += sprite->x;
	y += sprite->y;

	vbe_mode_info_t* mode_info = get_mode_info();

	if (x < 0 || y < 0 || x + sprite->img.width >= mode_info->XResolution || y + sprite->img.height >= mode_info->YResolution) return 1;

	sprite->x = x;
	sprite->y = y;

	return 0;
}
