#ifndef UTILS_H
#define UTILS_H

#include "tipos.h"

/* Leitura segura de string (substitui fgets + trim) */
void ler_string(const char *prompt, char *dest, int tamanho);

/* Leitura de inteiro com validação simples */
int ler_int(const char *prompt);

/* Leitura e validação de Data no formato DD/MM/AAAA */
Data ler_data(const char *prompt);

/* Formata Data em string "DD/MM/AAAA" no buffer fornecido */
void formatar_data(Data d, char *buf, int tam);

/* Retorna diferença em dias entre hoje e a data fornecida (>= 0) */
long dias_desde(Data d);

/* Limpa o buffer de entrada */
void limpar_buffer(void);

/* Pausa aguardando Enter */
void pausar(void);

/* Limpa a tela (portável) */
void limpar_tela(void);

#endif /* UTILS_H */
