#include "ev_listener.h"
extern uint8_t scancode;
extern int timer_counter;

void handle_dealer_turn(app_t *app, interrupt_type_t interrupt)
{
  if (interrupt == KEYBOARD)
  {
    if (scancode == KB_ESC)
    {
      app->state = MAIN_MENU;
      vg_set_redraw();
    }
  }

  if (interrupt == TIMER)
  {
    if (timer_counter % 20 == 0)
    {
      app->game.dealer_value = game_get_cards_value(app->game.dealer);
      
      vg_set_redraw();
      
      if (app->game.dealer_value >= 17)
      {
        if (app->game.dealer_value > 21 
          || app->game.dealer_value < app->game.main_player.cards_value)
        {
          app->game.main_player.won_coins = app->game.main_player.bet * 2;
          app->game.main_player.game_over_state = PLAYER_WIN;
        }
        else if (app->game.dealer_value > app->game.main_player.cards_value)
        {
          app->game.main_player.won_coins = 0;
          app->game.main_player.game_over_state = PLAYER_LOSS;
        }
        else
        {
          app->game.main_player.won_coins = app->game.main_player.bet;
          app->game.main_player.game_over_state = PLAYER_DRAW;
        }

        app->game.main_player.coins += app->game.main_player.won_coins;
        app->state = GAME_OVER;
				uart_send_byte(app->game.main_player.game_over_state);
      } 
      else game_give_card(app->game.cards, app->game.dealer);
      
      timer_counter = 0;
    }
  }
}
