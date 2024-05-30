#include "animation.h"

animation_t *animation_create(uint8_t loop, uint32_t frame_rate, uint32_t frame_amount)
{
	if (frame_rate < 1 && frame_rate > 30) return NULL;

	animation_t *anim = (animation_t *) malloc(sizeof(animation_t *));
	if (anim == NULL) return NULL;

	anim->frame_counter = 0;
	anim->frame_index = 0;
	anim->frame_rate = frame_rate;
	anim->loop = loop;

	anim->frames = queue_create(frame_amount);
	if (anim->frames == NULL) return NULL;

	anim->x = queue_create(frame_amount);
	if (anim->x == NULL)
	{
		queue_destroy(&anim->frames, queue_destroy_nothing);
		return NULL;
	}

	anim->y = queue_create(frame_amount);
	if (anim->y == NULL)
	{
		queue_destroy(&anim->frames, queue_destroy_nothing);
		queue_destroy(&anim->x, queue_destroy_nothing);
		return NULL;
	}

	return anim;
}

int animation_add_frame(animation_t *animation, sprite_t *sprite, uint32_t x, uint32_t y)
{
	if (animation == NULL || sprite == NULL) return 1;

	uint32_t *xp = malloc(sizeof(uint32_t));
	uint32_t *yp = malloc(sizeof(uint32_t));
	*xp = x;
	*yp = y;

	return queue_push(animation->frames, sprite) 
		|| queue_push(animation->x, xp)
		|| queue_push(animation->y, yp);
}

void animation_run(animation_t *animation)
{
	if (animation == NULL || animation->frames == NULL) return;

	animation->frame_counter += 1;

	uint8_t is_last_frame = animation->frame_index + 1 == animation->frames->curr_size;

	if (is_last_frame && !animation->loop) return;
	
	animation->frame_index = is_last_frame ? 0 : animation->frame_index + 1;

	vg_set_redraw();
}

/*int move_card(game_t *game, uint32_t pos){
	uint32_t x = 500 + game->card_back->img.width * 0.02;
	uint32_t y = 500 + (pos + 1) * game->card_back->img.height * 0.1;
	sprite_move(game->card_back, x, y);
	return sprite_draw(game->card_back);
}*/

int animation_draw(animation_t *animation)
{
	if (animation == NULL) return 1;

	uint32_t *x = queue_at(animation->x, animation->frame_index);
	uint32_t *y = queue_at(animation->y, animation->frame_index);
	sprite_t *sprite = queue_at(animation->frames, animation->frame_index);
	if (x == NULL || y == NULL || sprite == NULL) return 1;

	sprite_move(sprite, *x, *y);
	return sprite_draw(sprite);
}

void animation_destroy(animation_t *animation)
{
	if (animation == NULL) return;

	queue_destroy(&animation->frames, queue_destroy_nothing);
	queue_destroy(&animation->x, free);
	queue_destroy(&animation->y, free);
	free(animation);
}
