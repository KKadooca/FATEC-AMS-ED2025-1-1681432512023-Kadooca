#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 4

// Função para limpar a tela
void limparTela() {
#ifdef _WIN32
    system("cls");  // Limpar tela -> Windows
#else
    system("clear");  // Limpar tela -> Linux & MacOS
#endif
}

typedef struct {
    float dados[MAX];
    int topo;
} Pilha;

Pilha* Pilha_Criar() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->topo = -1;
    return p;
}

int Vazia(Pilha* p) {
    return p->topo == -1;
}

int Cheia(Pilha* p) {
    return p->topo == MAX - 1;
}

void Push(Pilha* p, float dado) {
    if (!Cheia(p)) {
        p->dados[++(p->topo)] = dado;
    } else {
        limparTela();
        printf("Erro: Pilha cheia!\n\n");
    }
}

float Pop(Pilha* p) {
    if (!Vazia(p)) {
        return p->dados[(p->topo)--];
    } else {
        limparTela();
        printf("Erro: Pilha vazia!\n\n");
        return 0;
    }
}

float Top(Pilha* p) {
    if (!Vazia(p)) {
        return p->dados[p->topo];
    } else {
        limparTela();
        printf("Erro: Pilha vazia!\n\n");
        return 0;
    }
}

int is_number(const char* str) {
    if (*str == '-') str++;
    if (!*str) return 0;
    while (*str) {
        if ((*str < '0' || *str > '9') && *str != '.') return 0;
        str++;
    }
    return 1;
}

float calcular_rpn(char* expressao, int* erro) {
    Pilha* p = Pilha_Criar();
    char* token = strtok(expressao, " ");
    float a, b;

    while (token) {
        if (is_number(token)) {
            Push(p, atof(token));
        } else {
            if (p->topo < 1) {
                printf("Erro: Expressão inválida!\n\n");
                *erro = 1;
                free(p);
                return 0;
            }
            b = Pop(p);
            a = Pop(p);
            switch (token[0]) {
                case '+': Push(p, a + b); break;
                case '-': Push(p, a - b); break;
                case '*': Push(p, a * b); break;
                case '/':
                    if (b != 0) Push(p, a / b);
                    else {
                        limparTela();
                        printf("Erro: Divisão por zero!\n\n");
                        *erro = 1;
                        free(p);
                        return 0;
                    }
                    break;
                default: 
                    limparTela();
                    printf("Erro: Operador inválido!\n\n");
                    *erro = 1;
                    free(p);
                    return 0;
            }
        }
        token = strtok(NULL, " ");
    }

    if (p->topo != 0) {
        limparTela();
        printf("Erro: Expressão inválida!\n");
        *erro = 1;
        free(p);
        return 0;
    }

    float resultado = Pop(p);
    free(p);
    return resultado;
}

int main() {
    char expressao[100];
    int erro;
    do {
        erro = 0;
        printf("Digite a expressão RPN: ");
        fgets(expressao, sizeof(expressao), stdin);
        expressao[strcspn(expressao, "\n")] = 0;
        
        if (strlen(expressao) == 0) {
            limparTela();
            printf("Encerrando o programa.\n");
            return 0;
        }

        float resultado = calcular_rpn(expressao, &erro);
        if (!erro) {
            printf("Resultado: %.2f\n", resultado);
        }
    } while (erro);

    return 0;
}
