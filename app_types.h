#ifndef APP_TYPES_H
#define APP_TYPES_H

/* Application modes controlled by the finite state machine. */
typedef enum {
    APP_STATE_MAIN_MENU = 0,
    APP_STATE_ADD_TRANSACTION,
    APP_STATE_VIEW_TRANSACTIONS,
    APP_STATE_EDIT_TRANSACTION,
    APP_STATE_DELETE_TRANSACTION,
    APP_STATE_FILTER_TRANSACTIONS,
    APP_STATE_MONTHLY_REPORT,
    APP_STATE_SET_BUDGET,
    APP_STATE_BUDGET_DASHBOARD,
    APP_STATE_EXIT_CONFIRMATION,
    APP_STATE_EXIT
} AppState;

typedef struct {
    AppState current_state;
} App;

#endif
