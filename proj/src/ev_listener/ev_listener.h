#ifndef _LCOM_EV_LISTENER_H_
#define _LCOM_EV_LISTENER_H_

#include "../drivers/drivers.h"
#include "../model/game.h"
#include "../model/app.h"

typedef struct {
  app_state_t state;
  void(*handle)(app_t *app, interrupt_type_t interrupt);
} state_handler_t;

void handle_interrupt(app_t *app, ev_listener_t listener);
void handle_general(app_t *app, interrupt_type_t interrupt);
void handle_main_menu(app_t *app, interrupt_type_t interrupt);
void handle_game_betting(app_t *app, interrupt_type_t interrupt);

extern state_handler_t listeners[];

#endif
