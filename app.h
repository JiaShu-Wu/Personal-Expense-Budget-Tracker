#ifndef APP_H
#define APP_H

#include <stdbool.h>
#include "app_types.h"

/* Initialise and run the menu-driven application. */
void app_init(App *app);
void app_run(App *app);

/* Non-interactive FSM helpers, also callable from the test executable. */
AppState app_state_from_menu_choice(int choice);
AppState app_state_after_exit_confirmation(bool confirmed);
const char *app_state_name(AppState state);

#endif
