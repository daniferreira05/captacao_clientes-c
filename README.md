# Sistema de Captação de Clientes

Aplicação de linha de comando em **C** para gerenciamento do fluxo de captação de clientes, desenvolvida como trabalho acadêmico da disciplina de Estruturas de Dados.

---
## Sobre o Projeto

O sistema acompanha o ciclo de vida de um potencial cliente desde o primeiro contato até a conclusão do atendimento, distribuindo-o entre três estruturas de dados distintas conforme o resultado da abordagem comercial.
 
```
Cadastro → Aguardando Contato → [ Comprou? ]
                                     ├── Sim → Fila de Envio (Compradores)
                                     └── Não → Arquivar (Pilha) ou Excluir
```
 
---

## Estruturas de Dados Utilizadas

### Lista Duplamente Encadeada — Clientes Aguardando Contato
Escolhida porque o menu de atendimento exige **navegação bidirecional** (próximo e anterior) e **remoção em O(1)** de qualquer nó, operações que só a lista dupla realiza de forma eficiente.
 
### Fila (FIFO) — Compradores
O enunciado determina que *"quem compra primeiro tem o pedido processado primeiro"* — definição exata de FIFO. Novos compradores entram no fim (`enqueue`) e a logística retira do início (`dequeue`).
 
### Pilha (LIFO) — Clientes Arquivados
Clientes arquivados mais recentemente têm maior probabilidade de conversão num recontato futuro. A pilha coloca o mais recente no topo, refletindo esse comportamento naturalmente.
 
---

## Funcionalidades
 
- **Cadastrar cliente** — nome, telefone, e-mail e data de captação
- **Realizar contato** — navega pela fila de espera com as ações:
  - Ir para o próximo cliente
  - Voltar ao cliente anterior
  - Buscar cliente pelo nome (correspondência exata)
  - Finalizar atendimento (comprou / arquivar / excluir)
- **Relatórios**
  - Quantidade de clientes aguardando contato
  - Lista completa com número de dias desde a captação
 
---

## Como Compilar e Executar
 
### Pré-requisitos
- GCC (ou qualquer compilador C99 compatível)
- `make` (opcional)
 
### Com Makefile
```bash
make
./captacao
```
 
### Sem Makefile
```bash
cd captacao

gcc -Wall -Wextra -pedantic -std=c99 \
    main.c app.c lista_dupla.c fila.c pilha.c utils.c \
    -o captacao
 
./captacao
```
 
> O projeto compila **sem nenhum warning** com `-Wall -Wextra -pedantic -std=c99`.
 
---

## 👥 Integrantes do Grupo
 
| Nome | Matricula |
|---|---|
| Danielle G. Ferreira | 202414081 |
| Gustavo Caetano M. | 202414293 |
| Ana Julia Flores C. V. | 202413900 |
| Werisder de S. Bertoli | 202311527 |
 
---


## Disciplina
 
> Estruturas de Dados — [Nome da Instituição]
