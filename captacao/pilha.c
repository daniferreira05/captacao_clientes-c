#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

/* ------------------------------------------------------------------ */
void pilha_inicializar(Pilha *pilha) {
    pilha->topo     = NULL;
    pilha->tamanho  = 0;
}

/* ------------------------------------------------------------------ */
void pilha_empilhar(Pilha *pilha, DadosContato contato) {
    NoPilha *novo = (NoPilha *)malloc(sizeof(NoPilha));
    if (novo == NULL) {
        fprintf(stderr, "Erro: sem memoria para cliente arquivado.\n");
        return;
    }
    novo->contato = contato;
    novo->prox    = pilha->topo;
    pilha->topo   = novo;
    pilha->tamanho++;
}

/* ------------------------------------------------------------------ */
NoPilha *pilha_desempilhar(Pilha *pilha) {
    if (pilha->topo == NULL) return NULL;

    NoPilha *no  = pilha->topo;
    pilha->topo  = no->prox;
    no->prox     = NULL;
    pilha->tamanho--;
    return no; /* chamador deve liberar */
}

/* ------------------------------------------------------------------ */
void pilha_destruir(Pilha *pilha) {
    NoPilha *atual = pilha->topo;
    while (atual != NULL) {
        NoPilha *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    pilha->topo    = NULL;
    pilha->tamanho = 0;
}
