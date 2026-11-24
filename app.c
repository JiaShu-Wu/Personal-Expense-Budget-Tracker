#include "app.h"

#include <stddef.h>

#include "ui.h"

static bool is_feature_state(AppState state)
{
    return state >= APP_STATE_ADD_TRANSACTION &&
           state <= APP_STATE_BUDGET_DASHBOARD;
}

void app_run(App *app)
{
    if (app == NULL) {
        return;
    }

    ui_print_welcome();

    /* The persistent loop ends only when the FSM reaches APP_STATE_EXIT. */
    while (app->current_state != APP_STATE_EXIT) {
        switch (app->current_state) {
            case APP_STATE_MAIN_MENU: {
                int choice = -1;
                AppState next_state;

                ui_print_main_menu();
                if (!ui_read_menu_choice(&choice)) {
                    /* End-of-file (for example, Ctrl-D) exits safely. */
                    app->current_state = APP_STATE_EXIT;
                    break;
                }

                next_state = app_state_from_menu_choice(choice);
                if (next_state == APP_STATE_MAIN_MENU) {
                    ui_print_invalid_menu_choice();
                }
                app->current_state = next_state;
                break;
            }

            case APP_STATE_EXIT_CONFIRMATION: {
                bool confirmed = false;

                if (!ui_confirm_exit(&confirmed)) {
                    app->current_state = APP_STATE_EXIT;
                } else {
                    app->current_state =
                        app_state_after_exit_confirmation(confirmed);
                }
                break;
            }

            default:
                if (is_feature_state(app->current_state)) {
                    ui_print_feature_placeholder(app->current_state);
                    if (ui_wait_for_enter()) {
                        app->current_state = APP_STATE_MAIN_MENU;
                    } else {
                        app->current_state = APP_STATE_EXIT;
                    }
                } else {
                    /* Recover safely if an unexpected state is encountered. */
                    app->current_state = APP_STATE_MAIN_MENU;
                }
                break;
        }
    }

    ui_print_goodbye();
}
