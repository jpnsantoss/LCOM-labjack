#include "state.h"

static app_state_t curr_state = MAIN_MENU;

int set_state(app_state_t new_state)
{
  curr_state = new_state;
  return 0;
}

app_state_t get_state()
{
  return curr_state;
}
