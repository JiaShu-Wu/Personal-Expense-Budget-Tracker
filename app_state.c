#include "app.h"

#include <stddef.h>

void app_init(App *app)
{
    if (app != NULL) {
        app->current_state = APP_STATE_MAIN_MENU;
    }
}

AppState app_state_from_menu_choice(int choice)
{
    switch (choice) {
        case 1: return APP_STATE_ADD_TRANSACTION;
        case 2: return APP_STATE_VIEW_TRANSACTIONS;
        case 3: return APP_STATE_EDIT_TRANSACTION;
        case 4: return APP_STATE_DELETE_TRANSACTION;
        case 5: return APP_STATE_FILTER_TRANSACTIONS;
        case 6: return APP_STATE_MONTHLY_REPORT;
        case 7: return APP_STATE_SET_BUDGET;
        case 8: return APP_STATE_BUDGET_DASHBOARD;
        case 9: return APP_STATE_EXIT_CONFIRMATION;
        default: return APP_STATE_MAIN_MENU;
    }
}

AppState app_state_after_exit_confirmation(bool confirmed)
{
    return confirmed ? APP_STATE_EXIT : APP_STATE_MAIN_MENU;
}

const char *app_state_name(AppState state)
{
    switch (state) {
        case APP_STATE_MAIN_MENU: return "MAIN_MENU";
        case APP_STATE_ADD_TRANSACTION: return "ADD_TRANSACTION";
        case APP_STATE_VIEW_TRANSACTIONS: return "VIEW_TRANSACTIONS";
        case APP_STATE_EDIT_TRANSACTION: return "EDIT_TRANSACTION";
        case APP_STATE_DELETE_TRANSACTION: return "DELETE_TRANSACTION";
        case APP_STATE_FILTER_TRANSACTIONS: return "FILTER_TRANSACTIONS";
        case APP_STATE_MONTHLY_REPORT: return "MONTHLY_REPORT";
        case APP_STATE_SET_BUDGET: return "SET_BUDGET";
        case APP_STATE_BUDGET_DASHBOARD: return "BUDGET_DASHBOARD";
        case APP_STATE_EXIT_CONFIRMATION: return "EXIT_CONFIRMATION";
        case APP_STATE_EXIT: return "EXIT";
        default: return "UNKNOWN_STATE";
    }
}
