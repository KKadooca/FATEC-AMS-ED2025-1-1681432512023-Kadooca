#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME_CLIENTE 100
#define MAX_DESCRICAO_PRATO 200

// Função limpar tela
void limparTela() {
#ifdef _WIN32
    system("cls");  // Limpar tela -> Windows
#else
    system("clear");  // Limpar tela -> Linux & MacOS
#endif
}

// Status do pedido
typedef enum {
    PENDENTE,
    EM_PREPARO,
    PRONTO,
    ENTREGUE
} StatusPedido;

// Estrutura de um pedido (nó da lista ligada)
typedef struct Pedido {
    int numeroPedido;
    char nomeCliente[MAX_NOME_CLIENTE];
    char descricaoPrato[MAX_DESCRICAO_PRATO];
    int quantidade;
    StatusPedido status;
    struct Pedido* proximo;  // Ponteiro para o próximo pedido
} Pedido;

// Criar uma lista vazia (inicializa a lista como NULL)
Pedido* criarLista() {
    return NULL;
}

// Criar um novo pedido
Pedido* criarPedido(int numero, const char* nomeCliente, const char* descricaoPrato, int quantidade, StatusPedido status) {
    Pedido* novoPedido = (Pedido*)malloc(sizeof(Pedido));
    if (novoPedido == NULL) {
        limparTela();
        printf("Erro ao alocar memória para o novo pedido.\n");
        exit(1);
    }
    
    novoPedido->numeroPedido = numero;
    strncpy(novoPedido->nomeCliente, nomeCliente, MAX_NOME_CLIENTE);
    strncpy(novoPedido->descricaoPrato, descricaoPrato, MAX_DESCRICAO_PRATO);
    novoPedido->quantidade = quantidade;
    novoPedido->status = status;
    novoPedido->proximo = NULL;  // Inicializa o ponteiro para NULL
    
    return novoPedido;
}

// Inserir um pedido na lista ligada
void inserirPedido(Pedido** lista, Pedido* novoPedido) {
    if (*lista == NULL) {
        *lista = novoPedido;  // Se a lista estiver vazia, o novo pedido é o primeiro
    } else {
        Pedido* temp = *lista;
        while (temp->proximo != NULL) {  // Percorre até o final da lista
            temp = temp->proximo;
        }
        temp->proximo = novoPedido;  // Insere o novo pedido no final
    }
}

// Obter um pedido pela número de pedido
Pedido* obterPedido(Pedido* lista, int numeroPedido) {
    Pedido* temp = lista;
    while (temp != NULL) {
        if (temp->numeroPedido == numeroPedido) {
            return temp;  // Retorna o pedido se encontrado
        }
        temp = temp->proximo;
    }
    return NULL;  // Retorna NULL se o pedido não for encontrado
}

// Atualizar o status de um pedido
void atualizarStatus(Pedido* lista, int numeroPedido, StatusPedido novoStatus) {
    Pedido* pedido = obterPedido(lista, numeroPedido);
    if (pedido != NULL) {
        limparTela();
        pedido->status = novoStatus;
        printf("Status do pedido %d atualizado para %d.\n", numeroPedido, novoStatus);
    } else {
        limparTela();
        printf("Pedido não encontrado.\n");
    }
}

// Deletar um pedido da lista ligada
void deletarPedido(Pedido** lista, int numeroPedido) {
    Pedido* temp = *lista;
    Pedido* anterior = NULL;
    
    if (temp != NULL && temp->numeroPedido == numeroPedido) {
        *lista = temp->proximo;  // Se o pedido a ser deletado for o primeiro
        limparTela();
        free(temp);
        printf("Pedido %d deletado com sucesso.\n", numeroPedido);
        return;
    }
    
    while (temp != NULL && temp->numeroPedido != numeroPedido) {
        anterior = temp;
        temp = temp->proximo;  // Percorre a lista até encontrar o pedido
    }
    
    if (temp == NULL) {
        limparTela();
        printf("Pedido não encontrado.\n");
        return;
    }
    
    anterior->proximo = temp->proximo;  // Conecta o nó anterior com o próximo do deletado
    limparTela();
    free(temp);
    printf("Pedido %d deletado com sucesso.\n", numeroPedido);
}

// Liberar a memória de todos os pedidos
void liberarLista(Pedido* lista) {
    Pedido* temp;
    while (lista != NULL) {
        temp = lista;
        lista = lista->proximo;
        free(temp);  // Libera a memória de cada pedido
    }
    limparTela();
    printf("Memória liberada com sucesso.\n");
}

// Exibir os detalhes de um pedido
void exibirPedido(Pedido* pedido) {
    if (pedido != NULL) {
        limparTela();
        printf("Número do Pedido: %d\n", pedido->numeroPedido);
        printf("Nome do Cliente: %s\n", pedido->nomeCliente);
        printf("Descrição do Prato: %s\n", pedido->descricaoPrato);
        printf("Quantidade: %d\n", pedido->quantidade);
        printf("Status: %d\n", pedido->status);
    } else {
        limparTela();
        printf("Pedido não encontrado.\n");
    }
}

// Exibir o menu principal
int exibirMenu() {
    int opcao;
    printf("\nSistema de Gerenciamento de Pedidos\n");
    printf("1. Inserir Pedido\n");
    printf("2. Atualizar Status\n");
    printf("3. Obter Pedido\n");
    printf("4. Deletar Pedido Concluído\n");
    printf("5. Liberar Lista e Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    return opcao;
}

int main() {
    Pedido* listaPedidos = criarLista();
    int opcao, numeroPedido, quantidade;
    StatusPedido status;
    char nomeCliente[MAX_NOME_CLIENTE], descricaoPrato[MAX_DESCRICAO_PRATO];
    
    while (1) {
        opcao = exibirMenu();
        
        switch (opcao) {
            case 1:
                // Inserir Pedido
                limparTela();
                printf("Número do Pedido: ");
                scanf("%d", &numeroPedido);
                printf("Nome do Cliente: ");
                getchar();
                fgets(nomeCliente, MAX_NOME_CLIENTE, stdin);
                nomeCliente[strcspn(nomeCliente, "\n")] = 0;
                printf("Descrição do Prato: ");
                fgets(descricaoPrato, MAX_DESCRICAO_PRATO, stdin);
                descricaoPrato[strcspn(descricaoPrato, "\n")] = 0;
                printf("Quantidade: ");
                scanf("%d", &quantidade);
                printf("Status (0-PENDENTE, 1-EM PREPARO, 2-PRONTO, 3-ENTREGUE): ");
                scanf("%d", (int*)&status);
            
                inserirPedido(&listaPedidos, criarPedido(numeroPedido, nomeCliente, descricaoPrato, quantidade, status));
                limparTela();
                break;

            case 2:
                // Atualizar Status
                limparTela();
                printf("Número do Pedido para Atualizar: ");
                scanf("%d", &numeroPedido);
                printf("Novo Status (0-PENDENTE, 1-EM PREPARO, 2-PRONTO, 3-ENTREGUE): ");
                scanf("%d", (int*)&status);
                atualizarStatus(listaPedidos, numeroPedido, status);
                break;

                
            case 3:
                // Obter Pedido
                limparTela();
                printf("Número do Pedido para Exibir: ");
                scanf("%d", &numeroPedido);
                Pedido* pedido = obterPedido(listaPedidos, numeroPedido);
                exibirPedido(pedido);
                break;
                
            case 4:
                // Deletar Pedido Concluído
                limparTela();
                printf("Número do Pedido para Deletar: ");
                scanf("%d", &numeroPedido);
                deletarPedido(&listaPedidos, numeroPedido);
                break;
                
            case 5:
                // Liberar Lista e Sair
                limparTela();
                liberarLista(listaPedidos);
                printf("Sistema encerrado.\n");
                return 0;
                
            default:
                limparTela();
                printf("Opção inválida, tente novamente.\n");
        }
    }

    return 0;
}
