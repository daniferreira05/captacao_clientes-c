#ifndef FILA_H
#define FILA_H

#include "tipos.h"

/* Inicializa a fila */
void fila_inicializar(Fila *fila);

/* Enfileira um comprador */
void fila_enfileirar(Fila *fila, DadosContato contato, DadosAdicionais adicionais);

/* Desenfileira (remove da frente) */
NoFila *fila_desenfileirar(Fila *fila);

/* Libera toda a fila */
void fila_destruir(Fila *fila);

#endif /* FILA_H */
