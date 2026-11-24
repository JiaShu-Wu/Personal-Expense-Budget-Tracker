#include "app.h"

int main(void)
{
    App application;

    app_init(&application);
    app_run(&application);

    return 0;
}
