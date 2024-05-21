#include "sprite.h"
#include "../drivers/drivers.h"

sprite_t *sprite_create(xpm_map_t map, uint32_t x, uint32_t y)
{
	sprite_t *sprite = (sprite_t *) malloc(sizeof(sprite_t));
	if (sprite == NULL) return NULL;

	sprite->map = (uint8_t *) xpm_load(map,  XPM_8_8_8_8, &sprite->img);
	if (sprite->map == NULL)
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
	free(sprite->map);
	sprite->img.bytes = NULL;
}

int	sprite_draw(sprite_t *sprite)
{
	t_gph gph = vg_get_info();
	uint8_t *map = sprite->img.bytes;

	for (int j = 0; j < sprite->img.height; j++)
	{
		for (int i = 0; i < sprite->img.width; i++)
		{
			uint32_t color = 0;
      memcpy(&color, map, gph.bytes_per_pixel);

			if (color == xpm_transparency_color(sprite->img.type))
			{
				map += gph.bytes_per_pixel;
				continue;
			}

			if (vg_draw_pixel(sprite->x + i, sprite->y + j, color)) return 1;
			map += gph.bytes_per_pixel;
		}
	}
	return 0;
}

int sprite_move(sprite_t *sprite, uint32_t x, uint32_t y)
{
	t_gph gph = vg_get_info();

	if (x >= gph.x_res || y >= gph.y_res) return 1;

	sprite->x = x;
	sprite->y = y;

	return 0;
}
