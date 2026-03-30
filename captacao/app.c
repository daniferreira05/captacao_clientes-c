#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "app.h"
#include "utils.h"

/* ================================================================== */
/*  Inicialização / destruição                                         */
/* ================================================================== */

void app_inicializar(App *app) {
    lista_inicializar(&app->aguardando);
    fila_inicializar(&app->compradores);
    pilha_inicializar(&app->arquivados);
}

void app_destruir(App *app) {
    lista_destruir(&app->aguardando);
    fila_destruir(&app->compradores);
    pilha_destruir(&app->arquivados);
}

/* ================================================================== */
/*  Exibição de cliente                                                */
/* ================================================================== */

void exibir_contato(const DadosContato *c, int posicao, int total) {
    char buf[16];
    formatar_data(c->data_captacao, buf, sizeof(buf));
    printf("\n  +-------------------------------------------------+\n");
    printf("  | Cliente %d de %d\n", posicao, total);
    printf("  | Nome     : %s\n", c->nome);
    printf("  | Telefone : %s\n", c->telefone);
    printf("  | E-mail   : %s\n", c->email);
    printf("  | Captacao : %s  (%ld dias atras)\n",
           buf, dias_desde(c->data_captacao));
    printf("  +-------------------------------------------------+\n");
}

/* ================================================================== */
/*  Cadastrar cliente                                                  */
/* ================================================================== */

void menu_cadastrar(App *app) {
    limpar_tela();
    printf("\n  === CADASTRAR CLIENTE ===\n\n");

    DadosContato c;
    ler_string("  Nome     : ", c.nome,     sizeof(c.nome));
    ler_string("  Telefone : ", c.telefone, sizeof(c.telefone));
    ler_string("  E-mail   : ", c.email,    sizeof(c.email));
    c.data_captacao = ler_data("  Data de captacao");

    lista_inserir_fim(&app->aguardando, c);
    printf("\n  [OK] Cliente \"%s\" cadastrado com sucesso.\n", c.nome);
    pausar();
}

/* ================================================================== */
/*  Dados adicionais do comprador                                      */
/* ================================================================== */

Endereco coletar_endereco(void) {
    Endereco e;
    printf("\n  -- Endereco --\n");
    ler_string("  Rua    : ", e.rua,    sizeof(e.rua));
    ler_string("  Numero : ", e.numero, sizeof(e.numero));
    ler_string("  Bairro : ", e.bairro, sizeof(e.bairro));
    ler_string("  Cidade : ", e.cidade, sizeof(e.cidade));
    ler_string("  Estado (UF): ", e.estado, sizeof(e.estado));
    ler_string("  CEP (00000-000): ", e.cep, sizeof(e.cep));
    return e;
}

DadosAdicionais coletar_dados_adicionais(void) {
    DadosAdicionais d;
    printf("\n  -- Dados Adicionais --\n");
    d.data_nascimento = ler_data("  Data de nascimento");
    ler_string("  CPF (000.000.000-00): ", d.cpf, sizeof(d.cpf));
    d.endereco = coletar_endereco();
    return d;
}

/* ================================================================== */
/*  Finalizar atendimento                                              */
/* ================================================================== */

void finalizar_atendimento(App *app, NoDuplo *no) {
    printf("\n  O cliente comprou o produto? (1=Sim / 2=Nao): ");
    int resp = ler_int("");

    if (resp == 1) {
        /* Comprou → coleta dados e enfileira */
        DadosAdicionais adicionais = coletar_dados_adicionais();
        fila_enfileirar(&app->compradores, no->contato, adicionais);
        printf("\n  [OK] Cliente movido para fila de envio.\n");
        lista_remover_no(&app->aguardando, no);
    } else {
        printf("\n  Deseja arquivar os dados para contato futuro?\n");
        printf("  (1=Arquivar / 2=Excluir definitivamente): ");
        int arq = ler_int("");
        if (arq == 1) {
            pilha_empilhar(&app->arquivados, no->contato);
            printf("\n  [OK] Cliente arquivado.\n");
        } else {
            printf("\n  [OK] Cliente excluido definitivamente.\n");
        }
        lista_remover_no(&app->aguardando, no);
    }
    pausar();
}

/* ================================================================== */
/*  Realizar contato                                                   */
/* ================================================================== */

void menu_realizar_contato(App *app) {
    if (app->aguardando.tamanho == 0) {
        limpar_tela();
        printf("\n  Nenhum cliente aguardando contato.\n");
        pausar();
        return;
    }

    NoDuplo *atual = app->aguardando.inicio; /* mais antigo */
    int total = app->aguardando.tamanho;
    int posicao = 1;

    int continuar = 1;
    while (continuar) {
        limpar_tela();
        exibir_contato(&atual->contato, posicao, total);

        printf("\n  [1] Proximo cliente\n");
        printf("  [2] Cliente anterior\n");
        printf("  [3] Buscar pelo nome\n");
        printf("  [4] Finalizar atendimento\n");
        printf("  [0] Voltar ao menu principal\n");
        int op = ler_int("\n  Opcao: ");

        switch (op) {
            case 1:
                if (atual->prox != NULL) {
                    atual = atual->prox;
                    posicao++;
                } else {
                    printf("\n  [!] Ja esta no ultimo cliente.\n");
                    pausar();
                }
                break;

            case 2:
                if (atual->ant != NULL) {
                    atual = atual->ant;
                    posicao--;
                } else {
                    printf("\n  [!] Ja esta no primeiro cliente.\n");
                    pausar();
                }
                break;

            case 3: {
                char nome_busca[100];
                ler_string("\n  Nome exato para busca: ", nome_busca,
                           sizeof(nome_busca));
                NoDuplo *encontrado = lista_buscar_nome(&app->aguardando,
                                                        nome_busca);
                if (encontrado != NULL) {
                    atual = encontrado;
                    /* recalcula posição */
                    posicao = 1;
                    NoDuplo *tmp = app->aguardando.inicio;
                    while (tmp != NULL && tmp != atual) {
                        tmp = tmp->prox;
                        posicao++;
                    }
                    printf("\n  [OK] Cliente encontrado.\n");
                    pausar();
                } else {
                    printf("\n  [!] Cliente nao encontrado. Permanecendo no atual.\n");
                    pausar();
                }
                break;
            }

            case 4:
                finalizar_atendimento(app, atual);
                /* Após remover, reinicia no primeiro da lista */
                total = app->aguardando.tamanho;
                if (total == 0) {
                    continuar = 0;
                } else {
                    atual    = app->aguardando.inicio;
                    posicao  = 1;
                }
                break;

            case 0:
                continuar = 0;
                break;

            default:
                printf("\n  [!] Opcao invalida.\n");
                pausar();
                break;
        }
    }
}

/* ================================================================== */
/*  Relatórios                                                         */
/* ================================================================== */

static void relatorio_quantidade(App *app) {
    printf("\n  Clientes aguardando contato: %d\n", app->aguardando.tamanho);
    pausar();
}

static void relatorio_lista(App *app) {
    if (app->aguardando.tamanho == 0) {
        printf("\n  Nenhum cliente aguardando contato.\n");
        pausar();
        return;
    }

    printf("\n  %-5s %-30s %-15s %-25s %s\n",
           "Pos.", "Nome", "Telefone", "E-mail", "Dias aguardando");
    printf("  %s\n",
           "------------------------------------------------------------"
           "-----------------------------");

    NoDuplo *atual = app->aguardando.inicio;
    int pos = 1;
    while (atual != NULL) {
        long dias = dias_desde(atual->contato.data_captacao);
        printf("  %-5d %-30s %-15s %-25s %ld\n",
               pos,
               atual->contato.nome,
               atual->contato.telefone,
               atual->contato.email,
               dias);
        atual = atual->prox;
        pos++;
    }
    pausar();
}

void menu_relatorios(App *app) {
    int sair = 0;
    while (!sair) {
        limpar_tela();
        printf("\n  === RELATORIOS ===\n");
        printf("\n  [1] Numero de clientes aguardando contato\n");
        printf("  [2] Lista de clientes aguardando contato\n");
        printf("  [0] Voltar\n");
        int op = ler_int("\n  Opcao: ");

        switch (op) {
            case 1: relatorio_quantidade(app); break;
            case 2: relatorio_lista(app);      break;
            case 0: sair = 1;                  break;
            default:
                printf("\n  [!] Opcao invalida.\n");
                pausar();
        }
    }
}

/* ================================================================== */
/*  Menu principal                                                     */
/* ================================================================== */

void menu_principal(App *app) {
    int sair = 0;
    while (!sair) {
        limpar_tela();
        printf("\n  ╔══════════════════════════════════════╗\n");
        printf("  ║   SISTEMA DE CAPTACAO DE CLIENTES   ║\n");
        printf("  ╚══════════════════════════════════════╝\n");
        printf("\n  Aguardando contato : %d\n", app->aguardando.tamanho);
        printf("  Compradores        : %d\n",  app->compradores.tamanho);
        printf("  Arquivados         : %d\n",  app->arquivados.tamanho);
        printf("\n  [1] Cadastrar cliente\n");
        printf("  [2] Realizar contato\n");
        printf("  [3] Relatorios\n");
        printf("  [4] Sair\n");
        int op = ler_int("\n  Opcao: ");

        switch (op) {
            case 1: menu_cadastrar(app);          break;
            case 2: menu_realizar_contato(app);   break;
            case 3: menu_relatorios(app);          break;
            case 4: sair = 1;                      break;
            default:
                printf("\n  [!] Opcao invalida.\n");
                pausar();
        }
    }
}
