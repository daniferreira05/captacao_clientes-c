#ifndef TIPOS_H
#define TIPOS_H

/* ============================================================
   tipos.h — Definições de estruturas de dados
   ============================================================ */

/* ---------- Data ---------- */
typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

/* ---------- Endereço ---------- */
typedef struct {
    char rua[100];
    char numero[10];
    char bairro[60];
    char cidade[60];
    char estado[3];   /* sigla UF + '\0' */
    char cep[10];     /* 00000-000 + '\0' */
} Endereco;

/* ---------- Dados básicos (todo potencial cliente) ---------- */
typedef struct {
    char nome[100];
    char telefone[20];
    char email[100];
    Data  data_captacao;
} DadosContato;

/* ---------- Dados adicionais (só compradores) ---------- */
typedef struct {
    Data     data_nascimento;
    Endereco endereco;
    char     cpf[15];   /* 000.000.000-00 + '\0' */
} DadosAdicionais;

/* ============================================================
   Nó da Lista Duplamente Encadeada (aguardando contato)
   Justificativa: permite navegação bidirecional (próximo /
   anterior) exigida pela funcionalidade "Realizar Contato",
   além de remoção O(1) dado o ponteiro do nó.
   ============================================================ */
typedef struct NoDuplo {
    DadosContato     contato;
    struct NoDuplo  *ant;
    struct NoDuplo  *prox;
} NoDuplo;

typedef struct {
    NoDuplo *inicio;
    NoDuplo *fim;
    int      tamanho;
} ListaDupla;

/* ============================================================
   Nó da Fila (compradores — FIFO: primeiro a comprar,
   primeiro a ter pedido processado para envio)
   Justificativa: a especificação diz explicitamente que
   "cliente que compra primeiro tem seu pedido processado
   primeiro", o que é exatamente a semântica de uma fila.
   ============================================================ */
typedef struct NoFila {
    DadosContato    contato;
    DadosAdicionais adicionais;
    struct NoFila  *prox;
} NoFila;

typedef struct {
    NoFila *frente;
    NoFila *tras;
    int     tamanho;
} Fila;

/* ============================================================
   Nó da Pilha (arquivados — LIFO)
   Justificativa: clientes arquivados são consultados de forma
   oportunista; o mais recente costuma ser o mais relevante
   para um futuro contato (memória de curto prazo da equipe).
   Uma pilha reflete esse comportamento naturalmente.
   ============================================================ */
typedef struct NoPilha {
    DadosContato    contato;
    struct NoPilha *prox;
} NoPilha;

typedef struct {
    NoPilha *topo;
    int      tamanho;
} Pilha;

#endif /* TIPOS_H */
