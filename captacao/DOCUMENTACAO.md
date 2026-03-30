# Documentação — Sistema de Captação de Clientes

## 1. Visão Geral

Aplicação em C que controla o fluxo de captação de clientes em três estágios:
1. **Aguardando contato** — potenciais clientes recém-cadastrados.
2. **Compradores** — clientes que adquiriram o produto.
3. **Arquivados** — clientes que não compraram, mas autorizaram arquivamento.

---

## 2. Organização dos Arquivos

| Arquivo | Responsabilidade |
|---|---|
| `main.c` | Ponto de entrada; instancia `App` e chama o menu principal |
| `tipos.h` | Definição de todas as `struct` e `typedef` |
| `utils.h / utils.c` | Funções utilitárias (I/O segura, datas, tela) |
| `lista_dupla.h / lista_dupla.c` | Lista duplamente encadeada |
| `fila.h / fila.c` | Fila (FIFO) |
| `pilha.h / pilha.c` | Pilha (LIFO) |
| `app.h / app.c` | Lógica dos menus e regras de negócio |
| `Makefile` | Compilação automatizada |

---

## 3. Justificativa das Estruturas de Dados

### 3.1 Lista Duplamente Encadeada — Clientes Aguardando Contato

A funcionalidade **"Realizar Contato"** exige que o atendente navegue para o próximo
**e** para o cliente anterior, além de poder remover qualquer nó em O(1) assim que
o atendimento é finalizado.

- **Lista simplesmente encadeada** não permite navegação retroativa sem percurso linear.
- **Fila** ou **Pilha** só permitem acesso a uma extremidade.
- **Lista duplamente encadeada** resolve as três necessidades:
  - Navegação bidirecional (`proximo` / `anterior`) — ponteiros `prox` e `ant`.
  - Remoção O(1) de qualquer nó, dado seu endereço.
  - Inserção O(1) no fim (novos clientes).

### 3.2 Fila (FIFO) — Compradores

O enunciado diz explicitamente:

> *"Cliente que compra primeiro tem seu pedido processado para envio primeiro."*

Essa é exatamente a semântica de uma **fila FIFO** (`enqueue` na chegada, `dequeue`
no processamento logístico). Qualquer outra estrutura quebraria a ordem de chegada.

### 3.3 Pilha (LIFO) — Arquivados

Clientes arquivados são consultados de forma **oportunista**: quando a equipe retoma
contatos futuros, os mais recentes têm maior probabilidade de ainda se lembrarem da
empresa e de conversão. A **pilha LIFO** modela esse comportamento naturalmente —
o último arquivado é o primeiro a ser considerado num recontato.

---

## 4. Fluxo da Aplicação

```
Menu Principal
│
├── [1] Cadastrar cliente
│       └── Coleta: nome, telefone, e-mail, data de captação
│           Insere no FIM da Lista Duplamente Encadeada
│
├── [2] Realizar contato
│       └── Exibe o cliente mais antigo (início da lista)
│           Navegação: próximo ↔ anterior | busca por nome exato
│           Finalizar atendimento:
│             Comprou? → coleta dados adicionais → Fila de compradores
│             Não comprou:
│               Arquivar → Pilha de arquivados
│               Excluir  → free() imediato
│
├── [3] Relatórios
│       ├── Quantidade de clientes aguardando
│       └── Lista com dias aguardando (data atual − data captação)
│
└── [4] Sair → libera toda a memória
```

---

## 5. Gerenciamento de Memória

- Cada nó é alocado com `malloc` no momento da inserção.
- A remoção (transferência ou exclusão) chama `lista_remover_no`, que faz `free` imediato.
- As funções `*_destruir` percorrem cada estrutura liberando todos os nós restantes.
- `app_destruir` é chamada antes do programa encerrar, garantindo zero vazamentos.

---

## 6. Como Compilar e Executar

### Pré-requisitos
- GCC ≥ 4.8 (ou qualquer compilador C99 compatível)
- `make` (opcional)

### Com Makefile

```bash
make          # compila
./captacao    # executa
make clean    # remove objetos e executável
```

### Sem Makefile

```bash
gcc -Wall -Wextra -pedantic -std=c99 \
    main.c app.c lista_dupla.c fila.c pilha.c utils.c \
    -o captacao
./captacao
```

O projeto compila **sem nenhum warning** com `-Wall -Wextra -pedantic -std=c99`.

---

## 7. Decisões de Implementação Relevantes

| Aspecto | Decisão |
|---|---|
| Leitura de strings | `fgets` + remoção do `\n` — evita overflow e buffer residual |
| Leitura de inteiros | `fgets` + `sscanf` — não deixa lixo no stdin |
| Cálculo de dias | `mktime` + `difftime` da biblioteca padrão `<time.h>` |
| Busca por nome | Correspondência exata (`strcmp`) conforme especificação |
| Posição do cursor | Recalculada após busca percorrendo a lista desde o início |
| Transferência de nó | Copia `DadosContato` para a nova estrutura *antes* de remover o nó |
