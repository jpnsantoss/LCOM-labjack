#include "font.h"

int font_init(font_t *font)
{
	if (font == NULL) return 1;

  const xpm_map_t letters_xpm[26] = {
    letter_a_xpm , /*letter_b_xpm, letter_c_xpm,
     letter_d_xpm, letter_e_xpm, letter_f_xpm,
     letter_g_xpm, letter_h_xpm, letter_i_xpm,
     letter_j_xpm, letter_k_xpm, letter_l_xpm,
     letter_m_xpm, letter_n_xpm, letter_o_xpm,
     letter_p_xpm, letter_q_xpm, letter_r_xpm,
     letter_s_xpm, letter_t_xpm, letter_u_xpm,
     letter_v_xpm, letter_w_xpm, letter_x_xpm,
     letter_y_xpm, letter_z_xpm*/
  };

  const xpm_map_t numbers_xpm[10] = {
    number_0_xpm, number_1_xpm, number_2_xpm,
    number_3_xpm, number_4_xpm, number_5_xpm,
    number_6_xpm, number_7_xpm, number_8_xpm,
    number_9_xpm};

  font->xpms_letters = queue_create(26);
  if (font->xpms_letters == NULL) return 1;

  for (int letter = 0; letter < 1; letter++)
	{
    sprite_t *sprite = sprite_create(letters_xpm[letter]);
    if (sprite == NULL)
		{
      queue_destroy(&font->xpms_letters, sprite_queue_destroy);
      return 1;
    }

    queue_push(font->xpms_letters, sprite);
  }

  font->xpms_numbers = queue_create(10);
  if (font->xpms_numbers == NULL)
	{
    queue_destroy(&font->xpms_letters, sprite_queue_destroy);
    return 1;
  }

  for (int n = 0; n <= 9; n++)
	{
    sprite_t *sprite = sprite_create(numbers_xpm[n]);
    if (sprite == NULL)
		{
      queue_destroy(&font->xpms_letters, sprite_queue_destroy);
      queue_destroy(&font->xpms_numbers, sprite_queue_destroy);
      return 1;
    }

    queue_push(font->xpms_numbers, sprite);
  }
  return 0;
}

void font_print_char(font_t *font, char c, uint32_t x, uint32_t y)
{
  sprite_t *sprite = NULL;

  if (c >= 'a' && c <= 'z')
	{
    sprite = queue_at(font->xpms_letters, c - 'a');
  }
  else if (c >= 'A' && c <= 'Z')
	{
    sprite = queue_at(font->xpms_letters, c - 'A');
  }
  else if (c >= '0' && c <= '9')
	{
    sprite = queue_at(font->xpms_numbers, c - '0');
  }

  if (sprite == NULL) return;

  sprite_move(sprite, x, y);
	sprite_draw(sprite);
}

void font_print_str(font_t *font, char *str, uint32_t x, uint32_t y)
{
	for (size_t i = 0; i < strlen(str); i++)
	{
		font_print_char(font, str[i], x, y);

		x += 24;
	}
}

void font_print_number(font_t *font, uint32_t num, uint32_t x, uint32_t y)
{
  char str[16];
  sprintf(str, "%u", num);

  font_print_str(font, str, x, y);
}

void font_destroy(font_t *font)
{
	if (font == NULL) return;

	queue_destroy(&font->xpms_letters, sprite_queue_destroy);
	queue_destroy(&font->xpms_numbers, sprite_queue_destroy);
}
