#include "ev_listener.h"

extern uint8_t scancode;
extern int timer_counter;

void handle_hit(void *ptr)
{
  if (ptr == NULL) return;

  app_t *app = (app_t *)ptr;
  player_t *player = &app->game.main_player;

  game_give_card(app->game.cards, player->cards);
  player->cards_value = game_get_cards_value(player->cards);
  
	if (player->cards_value > 21)
  {
    player->won_coins = 0;
    player->game_over_state = PLAYER_LOSS;
    app->state = GAME_OVER;
		uart_send_byte(app->game.main_player.game_over_state);
  }

  if (player->cards_value == 21)
  {
    add_dealer_single_animation(app);
  }

  vg_set_redraw();
}

void add_hit_animation(app_t *app)
{
  sprite_t *rotate_1 = sprite_create((xpm_map_t) rotate1_xpm);
  sprite_t *rotate_2 = sprite_create((xpm_map_t) rotate2_xpm);
  sprite_t *card_back = app->game.card_back;
  animation_t *move_card = animation_create(50, handle_hit);

  size_t card_pos = app->game.main_player.cards->curr_size;

  uint32_t x_i = GAME_DECK_DRAW_X + app->game.card_back->img.width * 0.02;
  uint32_t y_i = GAME_DECK_DRAW_Y - (app->game.card_back->img.height * 0.1);
  
  uint32_t x_f = 500 + card_pos * card_back->img.width * 0.5;
	uint32_t y_f = 500 - card_back->img.height * 0.09;
  
  double m = abs(y_i - y_f) / abs(x_i - x_f);

  double b = y_i - m * x_i;
  
  printf("%d, %d --> %d, %d | m %d | b %d\n", x_i, y_i, x_f, y_f, m, b);

  for (uint32_t i = x_i; i > x_f; i -= 10)
  {
    animation_add_frame(move_card, card_back, i, m * i + b, 0);
    printf("%d, %d\n", i, m * i + b);
  }

  animation_add_frame(move_card, card_back, x_f, y_f, 0);

  for(int i = 0; i < 4; i++)
  {
    animation_add_frame(move_card, rotate_1, x_f, y_f, 0);
  }

  for(int i = 0; i < 4; i++)
  {
   animation_add_frame(move_card, rotate_2, x_f, y_f, 0);
  }

  app->game.curr_anim = move_card;
}

void handle_double(void *ptr)
{
  if (ptr == NULL) return;
  
  app_t *app = (app_t *)ptr;

  player_t *player = &app->game.main_player;

  player->bet *= 2;
  
	game_give_card(app->game.cards, player->cards);

  card_t *card = queue_at(player->cards, player->cards->curr_size - 1);
  if (card != NULL) card->is_double = true;
      
  player->cards_value = game_get_cards_value(player->cards);
  
	if (player->cards_value > 21)
  {
    player->won_coins = 0;
    player->game_over_state = PLAYER_LOSS;
    app->state = GAME_OVER;
		uart_send_byte(app->game.main_player.game_over_state);
  }
	else
  {
    add_dealer_single_animation(app);
  }

	vg_set_redraw();
}

void add_double_animation(app_t *app)
{
  sprite_t *rotate_1 = sprite_create((xpm_map_t) rotate1_xpm);
  sprite_t *rotate_2 = sprite_create((xpm_map_t) rotate2_xpm);
  sprite_t *card_back = app->game.card_back;
  animation_t *move_card = animation_create(27, handle_double);
  
  for(size_t i = 0; i < 250; i += 10)
  {
    animation_add_frame(move_card, card_back, 
      GAME_DECK_DRAW_X + app->game.card_back->img.width * 0.02 - i/3,
      GAME_DECK_DRAW_Y - (app->game.card_back->img.height * 0.1 - i), 0
    );
  }

  size_t card_pos = app->game.main_player.cards->curr_size;

  uint32_t x = 500 + card_pos * card_back->img.width * 0.5;
	uint32_t y = 500 - card_back->img.height * 0.09;

  for(int i = 0; i < 4; i++)
  {
    animation_add_frame(move_card, rotate_1, x, y, 1);
  }

  for(int i = 0; i < 4; i++)
  {
   animation_add_frame(move_card, rotate_2, x, y, 1);
  }

  app->game.curr_anim = move_card;
}

void handle_game_playing(app_t *app, interrupt_type_t interrupt)
{
  if (animation_running(app->game.curr_anim)) return;

  if (interrupt == KEYBOARD)
  {
    switch (scancode)
    {
      case KB_ESC:
        app->state = MAIN_MENU;
        vg_set_redraw();
        break;
      // Hit
      case KB_1:
        add_hit_animation(app);
        break;
      // Stand
      case KB_2:
        timer_counter = 0;
        add_dealer_single_animation(app);
        vg_set_redraw();
        break;
      // Double
      case KB_3:
        if (app->game.main_player.cards->curr_size != 2) break;
        add_double_animation(app);
        break;
      // Surrender
      case KB_4:
        if (app->game.main_player.cards->curr_size != 2) break;
        app->game.main_player.won_coins = app->game.main_player.bet / 2;
        app->game.main_player.coins += app->game.main_player.won_coins;
        app->game.main_player.game_over_state = PLAYER_WIN;
        app->state = GAME_OVER;
				uart_send_byte(app->game.main_player.game_over_state);
        break;
      default:
        break;
    }
  }

  if (interrupt == MOUSE)
  {
    // Hit
    if (cursor_sprite_colides(&app->cursor, queue_at(app->buttons_game_playing, 0)))
    {
      add_hit_animation(app);
    }

    // Stand
    if (cursor_sprite_colides(&app->cursor, queue_at(app->buttons_game_playing, 1)))
    {
      timer_counter = 0;
      add_dealer_single_animation(app);
      vg_set_redraw();
      return;
    }

    // Double
    if (app->game.main_player.cards->curr_size == 2 &&
      cursor_sprite_colides(&app->cursor, queue_at(app->buttons_game_playing, 2)))
    {
			add_double_animation(app);
      return;
    }
    
    // Surrender
    if (app->game.main_player.cards->curr_size == 2 &&  cursor_sprite_colides(&app->cursor, queue_at(app->buttons_game_playing, 3)))
    {
      app->game.main_player.won_coins = app->game.main_player.bet / 2;
      app->game.main_player.coins += app->game.main_player.won_coins;
      app->game.main_player.game_over_state = PLAYER_WIN;
      app->state = GAME_OVER;
			uart_send_byte(app->game.main_player.game_over_state);
    }
  }
}
