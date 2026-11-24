#include "ui.h"
#include "app.h"

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    LINE_READ_OK,
    LINE_READ_EOF,
    LINE_READ_TOO_LONG
} LineReadStatus;

static LineReadStatus read_line(char *buffer, size_t capacity)
{
    size_t length;

    if (buffer == NULL || capacity < 2U) {
        return LINE_READ_TOO_LONG;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return LINE_READ_EOF;
    }

    length = strlen(buffer);
    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[length - 1U] = '\0';
        return LINE_READ_OK;
    }

    if (feof(stdin)) {
        return LINE_READ_OK;
    }

    /* Discard the rest of an overlong line so it cannot affect the next read. */
    {
        int ch;
        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);
    }

    return LINE_READ_TOO_LONG;
}

static bool parse_integer(const char *text, int *value)
{
    char *end = NULL;
    long parsed;

    if (text == NULL || value == NULL) {
        return false;
    }

    errno = 0;
    parsed = strtol(text, &end, 10);
    if (text == end || errno == ERANGE || parsed < INT_MIN || parsed > INT_MAX) {
        return false;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return false;
    }

    *value = (int)parsed;
    return true;
}

void ui_print_welcome(void)
{
    puts("\n===============================================");
    puts("       PERSONAL EXPENSE & BUDGET TRACKER");
    puts("===============================================");
}

void ui_print_main_menu(void)
{
    puts("\n--------------- MAIN MENU --------------------");
    puts("1. Add Transaction");
    puts("2. View Transactions");
    puts("3. Edit Transaction");
    puts("4. Delete Transaction");
    puts("5. Search / Filter Transactions");
    puts("6. Monthly Financial Report");
    puts("7. Set Monthly Budget");
    puts("8. Budget Health Dashboard");
    puts("9. Exit");
    puts("-----------------------------------------------");
    printf("Enter your choice: ");
    fflush(stdout);
}

void ui_print_invalid_menu_choice(void)
{
    puts("Invalid menu choice. Please enter a number from 1 to 9.");
}

void ui_print_feature_placeholder(AppState state)
{
    printf("\n[%s]\n", app_state_name(state));
    puts("This feature is scheduled for a later development stage.");
    puts("The FSM navigation for this application mode is working.");
}

void ui_print_goodbye(void)
{
    puts("\nApplication closed. Thank you for using the tracker.");
}

bool ui_read_menu_choice(int *choice)
{
    char buffer[64];
    LineReadStatus status;

    if (choice == NULL) {
        return false;
    }

    status = read_line(buffer, sizeof(buffer));
    if (status == LINE_READ_EOF) {
        return false;
    }

    if (status == LINE_READ_TOO_LONG || !parse_integer(buffer, choice)) {
        *choice = -1;
    }

    return true;
}

bool ui_confirm_exit(bool *confirmed)
{
    char buffer[32];
    LineReadStatus status;
    char *cursor;
    int answer;

    if (confirmed == NULL) {
        return false;
    }

    for (;;) {
        printf("Are you sure you want to exit? (y/n): ");
        fflush(stdout);
        status = read_line(buffer, sizeof(buffer));
        if (status == LINE_READ_EOF) {
            return false;
        }

        if (status == LINE_READ_TOO_LONG) {
            puts("Please enter y or n.");
            continue;
        }

        cursor = buffer;
        while (*cursor != '\0' && isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        answer = (*cursor == '\0') ? 0 : toupper((unsigned char)*cursor);
        if (answer == 'Y' || answer == 'N') {
            ++cursor;
            while (*cursor != '\0' && isspace((unsigned char)*cursor)) {
                ++cursor;
            }
            if (*cursor == '\0') {
                *confirmed = (answer == 'Y');
                return true;
            }
        }

        puts("Invalid response. Please enter y or n.");
    }
}

bool ui_wait_for_enter(void)
{
    char buffer[8];

    puts("\nPress Enter to return to the main menu...");
    return read_line(buffer, sizeof(buffer)) != LINE_READ_EOF;
}
