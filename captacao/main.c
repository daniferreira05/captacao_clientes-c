#include <stdio.h>
#include "app.h"

int main(void) {
    App app;
    app_inicializar(&app);
    menu_principal(&app);
    app_destruir(&app);
    printf("\n  Sistema encerrado. Ate logo!\n\n");
    return 0;
}
