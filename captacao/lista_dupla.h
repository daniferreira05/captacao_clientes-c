#ifndef LISTA_DUPLA_H
#define LISTA_DUPLA_H

#include "tipos.h"

/* Inicializa a lista */
void lista_inicializar(ListaDupla *lista);

/* Insere no fim (novos clientes vão para o final) */
void lista_inserir_fim(ListaDupla *lista, DadosContato contato);

/* Remove um nó específico e libera memória */
void lista_remover_no(ListaDupla *lista, NoDuplo *no);

/* Busca por nome exato; retorna ponteiro ou NULL */
NoDuplo *lista_buscar_nome(ListaDupla *lista, const char *nome);

/* Libera toda a lista */
void lista_destruir(ListaDupla *lista);

#endif /* LISTA_DUPLA_H */
