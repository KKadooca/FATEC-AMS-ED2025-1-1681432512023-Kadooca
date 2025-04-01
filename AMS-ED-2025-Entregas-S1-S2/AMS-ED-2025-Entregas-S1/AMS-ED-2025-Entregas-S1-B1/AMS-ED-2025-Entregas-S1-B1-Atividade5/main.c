
/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: Atividade B1-5                          */
/*             Objetivo: Transforma Lista Ligada em Pilha                           */
/*                                                                                  */
/*                                  Autor: Kauan A. Kadooca Bastos                  */
/*                                                                  Data:01/04/2025 */
/*----------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define maxS 100
#define MAX_PILHA 100

// Função para limpar a tela
void limparTela() {
#ifdef _WIN32
    system("cls");  // Limpar tela -> Windows
#else
    system("clear");  // Limpar tela -> Linux & MacOS
#endif
}

typedef enum {
    PENDENTE,
    EM_PREPARO,
    PRONTO,
    ENTREGUE
} StatusPedido;

typedef struct Pedido {
    int numero;
    char nomeCliente[maxS];
    char descricao[maxS];
    int quantidade;
    StatusPedido status;
} Pedido;

typedef struct Pilha {
    Pedido pedidos[MAX_PILHA];
    int topo;
} Pilha;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

const char* statusParaString(StatusPedido status) {
    switch (status) {
        case PENDENTE:
            return "Pendente";
        case EM_PREPARO:
            return "Em preparo";
        case PRONTO:
            return "Pronto";
        case ENTREGUE:
            return "Entregue";
        default:
            return "Desconhecido";
    }
}

void inicializarPilha(Pilha* pilha) {
    pilha->topo = -1;
}

int pilhaVazia(Pilha* pilha) {
    return pilha->topo == -1;
}

int pilhaCheia(Pilha* pilha) {
    return pilha->topo == MAX_PILHA - 1;
}

void push(Pilha* pilha, Pedido pedido) {
    if (pilhaCheia(pilha)) {
        printf("Erro: Pilha cheia!\n");
        return;
    }
    pilha->pedidos[++pilha->topo] = pedido;
}

Pedido* pop(Pilha* pilha) {
    if (pilhaVazia(pilha)) {
        printf("Erro: Pilha vazia!\n");
        return NULL;
    }
    return &pilha->pedidos[pilha->topo--];
}

Pedido* top(Pilha* pilha) {
    if (pilhaVazia(pilha)) {
        printf("Erro: Pilha vazia!\n");
        return NULL;
    }
    return &pilha->pedidos[pilha->topo];
}

Pilha* criarPilha() {
    Pilha* pilha = (Pilha*)malloc(sizeof(Pilha));
    if (pilha) {
        inicializarPilha(pilha);
    }
    return pilha;
}

void exibirPedido(Pedido* pedido) {
    if (pedido) {
        limparTela();
        printf("=======================\n");
        printf("Pedido #%d\nCliente: %s\nPrato: %s\nQuantidade: %d\nStatus: %s\n\n",
               pedido->numero, pedido->nomeCliente, pedido->descricao, pedido->quantidade, statusParaString(pedido->status));
        printf("=======================\n");
    } else {
        limparTela();
        printf("Pedido não encontrado!\n");
    }
}

void exibirTodosPedidos(Pilha* pilha) {
    if (pilhaVazia(pilha)) {
        limparTela();
        printf("Nenhum pedido na pilha.\n");
        return;
    }

    for (int i = pilha->topo; i >= 0; i--) {
        exibirPedido(&pilha->pedidos[i]);
    }
}

void menu(Pilha* pilha) {
    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Adicionar Pedido\n");
        printf("2. Buscar Pedido\n");
        printf("3. Atualizar Status de Pedido\n");
        printf("4. Remover Pedido\n");
        printf("5. Exibir Todos os Pedidos\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        int numero, quantidade, status;
        char nomeCliente[maxS], descricao[maxS];
        Pedido* pedido;

        switch (opcao) {
        case 1:
            limparTela();
            printf("Numero do Pedido: ");
            scanf("%d", &numero);
            limparBuffer();
            printf("Nome do Cliente: ");
            fgets(nomeCliente, maxS, stdin);
            strtok(nomeCliente, "\n");
            printf("Descricao do Prato: ");
            fgets(descricao, maxS, stdin);
            strtok(descricao, "\n");
            printf("Quantidade: ");
            scanf("%d", &quantidade);
            limparBuffer();

            Pedido novoPedido = {numero, "", "", quantidade, PENDENTE};
            strcpy(novoPedido.nomeCliente, nomeCliente);
            strcpy(novoPedido.descricao, descricao);
            push(pilha, novoPedido);
            break;

        case 2:
            printf("Numero do Pedido: ");
            scanf("%d", &numero);
            limparBuffer();
            pedido = top(pilha);
            if (pedido && pedido->numero == numero) {
                exibirPedido(pedido);
            } else {
                printf("Pedido não encontrado!\n");
            }
            break;

        case 3:
            limparTela();
            printf("Numero do Pedido: ");
            scanf("%d", &numero);
            limparBuffer();
            printf("Novo Status (0: PENDENTE, 1: EM_PREPARO, 2: PRONTO, 3: ENTREGUE): ");
            scanf("%d", &status);
            limparBuffer();
            pedido = top(pilha);
            if (pedido && pedido->numero == numero) {
                pedido->status = (StatusPedido)status;
                limparTela();
                printf("Status atualizado com sucesso!\n");
            } else {
                limparTela();
                printf("Pedido não encontrado!\n");
            }
            break;

        case 4:
            pedido = pop(pilha);
            if (pedido) {
                limparTela();
                printf("Pedido removido com sucesso!\n");
            } else {
                limparTela();
                printf("Erro ao remover pedido.\n");
            }
            break;

        case 5:
            limparTela();
            exibirTodosPedidos(pilha);
            break;

        case 6:
            limparTela();
            printf("Saindo...\n");
            break;

        default:
            limparTela();
            printf("Opcao invalida!\n");
        }
    } while (opcao != 6);
}

int main() {
    Pilha* pilhaPedidos = criarPilha();
    if (pilhaPedidos) {
        menu(pilhaPedidos);
        free(pilhaPedidos);
    } else {
        limparTela();
        printf("Erro ao criar a pilha.\n");
    }
    return 0;
}