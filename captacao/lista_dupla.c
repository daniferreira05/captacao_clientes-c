#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_dupla.h"

/* ------------------------------------------------------------------ */
void lista_inicializar(ListaDupla *lista) {
    lista->inicio   = NULL;
    lista->fim      = NULL;
    lista->tamanho  = 0;
}

/* ------------------------------------------------------------------ */
void lista_inserir_fim(ListaDupla *lista, DadosContato contato) {
    NoDuplo *novo = (NoDuplo *)malloc(sizeof(NoDuplo));
    if (novo == NULL) {
        fprintf(stderr, "Erro: sem memoria para novo cliente.\n");
        return;
    }
    novo->contato = contato;
    novo->prox    = NULL;
    novo->ant     = lista->fim;

    if (lista->fim != NULL)
        lista->fim->prox = novo;
    else
        lista->inicio = novo;

    lista->fim = novo;
    lista->tamanho++;
}

/* ------------------------------------------------------------------ */
void lista_remover_no(ListaDupla *lista, NoDuplo *no) {
    if (no == NULL) return;

    if (no->ant != NULL)
        no->ant->prox = no->prox;
    else
        lista->inicio = no->prox;

    if (no->prox != NULL)
        no->prox->ant = no->ant;
    else
        lista->fim = no->ant;

    free(no);
    lista->tamanho--;
}

/* ------------------------------------------------------------------ */
NoDuplo *lista_buscar_nome(ListaDupla *lista, const char *nome) {
    NoDuplo *atual = lista->inicio;
    while (atual != NULL) {
        if (strcmp(atual->contato.nome, nome) == 0)
            return atual;
        atual = atual->prox;
    }
    return NULL;
}

/* ------------------------------------------------------------------ */
void lista_destruir(ListaDupla *lista) {
    NoDuplo *atual = lista->inicio;
    while (atual != NULL) {
        NoDuplo *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    lista->inicio  = NULL;
    lista->fim     = NULL;
    lista->tamanho = 0;
}
