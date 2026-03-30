#ifndef APP_H
#define APP_H

#include "tipos.h"
#include "lista_dupla.h"
#include "fila.h"
#include "pilha.h"

/* Estado global da aplicação */
typedef struct {
    ListaDupla aguardando;   /* potenciais clientes em espera */
    Fila       compradores;  /* clientes que compraram (FIFO) */
    Pilha      arquivados;   /* clientes arquivados (LIFO)    */
} App;

/* Inicializa todas as estruturas */
void app_inicializar(App *app);

/* Libera toda a memória */
void app_destruir(App *app);

/* Menus */
void menu_principal(App *app);
void menu_cadastrar(App *app);
void menu_realizar_contato(App *app);
void menu_relatorios(App *app);

/* Submenu finalizar atendimento; recebe nó atual */
void finalizar_atendimento(App *app, NoDuplo *no);

/* Coleta dados adicionais de comprador */
DadosAdicionais coletar_dados_adicionais(void);

/* Coleta endereço */
Endereco coletar_endereco(void);

/* Exibe dados de contato formatados */
void exibir_contato(const DadosContato *c, int posicao, int total);

#endif /* APP_H */
