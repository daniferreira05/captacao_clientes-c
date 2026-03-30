#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

/* ------------------------------------------------------------------ */
void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/* ------------------------------------------------------------------ */
void ler_string(const char *prompt, char *dest, int tamanho) {
    printf("%s", prompt);
    if (fgets(dest, tamanho, stdin) != NULL) {
        /* Remove '\n' final */
        size_t len = strlen(dest);
        if (len > 0 && dest[len - 1] == '\n')
            dest[len - 1] = '\0';
    }
}

/* ------------------------------------------------------------------ */
int ler_int(const char *prompt) {
    int valor;
    char linha[32];
    while (1) {
        printf("%s", prompt);
        if (fgets(linha, sizeof(linha), stdin) != NULL) {
            if (sscanf(linha, "%d", &valor) == 1)
                return valor;
        }
        printf("  [!] Entrada invalida. Digite um numero inteiro.\n");
    }
}

/* ------------------------------------------------------------------ */
Data ler_data(const char *prompt) {
    Data d = {0, 0, 0};
    char linha[32];
    while (1) {
        printf("%s (DD/MM/AAAA): ", prompt);
        if (fgets(linha, sizeof(linha), stdin) != NULL) {
            if (sscanf(linha, "%d/%d/%d", &d.dia, &d.mes, &d.ano) == 3) {
                if (d.dia >= 1 && d.dia <= 31 &&
                    d.mes >= 1 && d.mes <= 12 &&
                    d.ano >= 1900 && d.ano <= 2100)
                    return d;
            }
        }
        printf("  [!] Data invalida. Use o formato DD/MM/AAAA.\n");
    }
}

/* ------------------------------------------------------------------ */
void formatar_data(Data d, char *buf, int tam) {
    snprintf(buf, (size_t)tam, "%02d/%02d/%04d", d.dia, d.mes, d.ano);
}

/* ------------------------------------------------------------------ */
long dias_desde(Data d) {
    struct tm t_ref = {0};
    t_ref.tm_mday = d.dia;
    t_ref.tm_mon  = d.mes - 1;
    t_ref.tm_year = d.ano - 1900;
    t_ref.tm_isdst = -1;

    time_t ref   = mktime(&t_ref);
    time_t agora = time(NULL);

    if (ref == (time_t)-1 || agora == (time_t)-1)
        return 0;

    double diff = difftime(agora, ref);
    long dias = (long)(diff / 86400.0);
    return dias < 0 ? 0 : dias;
}

/* ------------------------------------------------------------------ */
void pausar(void) {
    printf("\n  Pressione Enter para continuar...");
    limpar_buffer();
}

/* ------------------------------------------------------------------ */
void limpar_tela(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
