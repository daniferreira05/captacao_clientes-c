#ifndef PILHA_H
#define PILHA_H

#include "tipos.h"

/* Inicializa a pilha */
void pilha_inicializar(Pilha *pilha);

/* Empilha um cliente arquivado */
void pilha_empilhar(Pilha *pilha, DadosContato contato);

/* Desempilha (retorna ponteiro; chamador libera) */
NoPilha *pilha_desempilhar(Pilha *pilha);

/* Libera toda a pilha */
void pilha_destruir(Pilha *pilha);

#endif /* PILHA_H */
