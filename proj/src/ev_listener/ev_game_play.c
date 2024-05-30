#include "ev_listener.h"

extern uint8_t scancode;
extern int timer_counter;

void handle_hit(app_t *app, interrupt_type_t interrupt)
{
  player_t *player = &app->game.main_player;

  /*while(timer_counter/20 != 3){
    if(interrupt == TIMER){
      timer_int_handler();
      if(timer_counter % 20 == 0){
        app->game.dealer_value = timer_counter/20;
        vg_set_redraw();
      } 
    }
  }*/

  animation_t *move_card = animation_create(0, 20, 10);
  for(size_t i = 0; i<=100; i+=10){
    if (animation_add_frame(move_card, app->game.card_back, GAME_DECK_DRAW_X + game->card_back->img.width * 0.02, GAME_DECK_DRAW_Y - (game->card_back->img.height * 0.1 + i))) printf("ERROR");
  }
  app->game.curr_anim = move_card;
  animation_run(move_card);

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
    app->game.dealer_turn = 1;
    app->state = GAME_DEALER_TURN;
  }

  vg_set_redraw();
}

void handle_double(app_t *app)
{
  player_t *player = &app->game.main_player;

  player->bet *= 2;
  
  app->state = GAME_DEALER_TURN;
  app->game.dealer_turn = 1;
	game_give_card(app->game.dealer, player->cards);

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
    app->game.dealer_turn = 1;
    app->state = GAME_DEALER_TURN;
  }

	vg_set_redraw();
}

void handle_game_playing(app_t *app, interrupt_type_t interrupt)
{
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
        handle_hit(app, interrupt);
        break;
      // Stand
      case KB_2:
        timer_counter = 0;
        app->state = GAME_DEALER_TURN;
        app->game.dealer_turn = 1;
        vg_set_redraw();
        break;
      // Double
      case KB_3:
        if (app->game.main_player.cards->curr_size != 2) break;
        handle_double(app);
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
      handle_hit(app, interrupt);
    }

    // Stand
    if (cursor_sprite_colides(&app->cursor, queue_at(app->buttons_game_playing, 1)))
    {
      timer_counter = 0;
      app->game.dealer_turn = 1;
      app->state = GAME_DEALER_TURN;
      vg_set_redraw();
      return;
    }

    // Double
    if (app->game.main_player.cards->curr_size == 2 &&
      cursor_sprite_colides(&app->cursor, queue_at(app->buttons_game_playing, 2)))
    {
			handle_double(app);
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
