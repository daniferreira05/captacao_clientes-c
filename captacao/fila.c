#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

/* ------------------------------------------------------------------ */
void fila_inicializar(Fila *fila) {
    fila->frente   = NULL;
    fila->tras     = NULL;
    fila->tamanho  = 0;
}

/* ------------------------------------------------------------------ */
void fila_enfileirar(Fila *fila, DadosContato contato, DadosAdicionais adicionais) {
    NoFila *novo = (NoFila *)malloc(sizeof(NoFila));
    if (novo == NULL) {
        fprintf(stderr, "Erro: sem memoria para comprador.\n");
        return;
    }
    novo->contato    = contato;
    novo->adicionais = adicionais;
    novo->prox       = NULL;

    if (fila->tras != NULL)
        fila->tras->prox = novo;
    else
        fila->frente = novo;

    fila->tras = novo;
    fila->tamanho++;
}

/* ------------------------------------------------------------------ */
NoFila *fila_desenfileirar(Fila *fila) {
    if (fila->frente == NULL) return NULL;

    NoFila *no    = fila->frente;
    fila->frente  = no->prox;
    if (fila->frente == NULL)
        fila->tras = NULL;

    no->prox = NULL;
    fila->tamanho--;
    return no; /* chamador deve liberar */
}

/* ------------------------------------------------------------------ */
void fila_destruir(Fila *fila) {
    NoFila *atual = fila->frente;
    while (atual != NULL) {
        NoFila *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    fila->frente   = NULL;
    fila->tras     = NULL;
    fila->tamanho  = 0;
}
