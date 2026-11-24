#ifndef UI_H
#define UI_H

#include <stdbool.h>
#include "app_types.h"

void ui_print_welcome(void);
void ui_print_main_menu(void);
void ui_print_invalid_menu_choice(void);
void ui_print_feature_placeholder(AppState state);
void ui_print_goodbye(void);

/* Return false only when input reaches EOF. Invalid lines set choice to -1. */
bool ui_read_menu_choice(int *choice);

/* Return false on EOF; otherwise write the user's yes/no answer. */
bool ui_confirm_exit(bool *confirmed);
bool ui_wait_for_enter(void);

#endif
