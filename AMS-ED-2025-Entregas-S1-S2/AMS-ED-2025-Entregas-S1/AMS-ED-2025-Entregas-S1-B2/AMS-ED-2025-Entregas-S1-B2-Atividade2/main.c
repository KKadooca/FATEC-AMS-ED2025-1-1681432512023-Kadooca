/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B2-2                                 */
/*             Objetivo: <<  Aprender a utilizar o bubbleSort p/ linguagem C  >>    */
/*                                                                                  */
/*                                  Autor: Kauan A. K. Bastos                       */
/*                                                                                  */
/*                                                                  Data:06/05/2025 */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#define MAX 100

// Função para limpar a tela
void limparTela() {
#ifdef _WIN32
    system("cls");  // Limpar tela -> Windows
#else
    system("clear");  // Limpar tela -> Linux & MacOS
#endif
}

int menu() {
    int decisao;
    limparTela();
    printf("Inserir mais um número?\n0(não) / 1(sim): ");
    scanf("%d", &decisao);
    return decisao;
}

void bubbleSort(int num[], int tam) {
    int i, j, temp;
    for(i = 0; i < tam; i++) {
        for(j = 0; j < tam - 1; j++) {
            if(num[j] > num[j + 1]) {
                temp = num[j];
                num[j] = num[j + 1];
                num[j + 1] = temp;
            }
        }
    }
}

void exibir(int num[], int tam) {
    limparTela();
    printf("Números em ordem ascendente:\n");
    for(int i = 0; i < tam; i++) {
        printf("%d ", num[i]);
    }
    printf("\n");
}

int main() {
    int num[MAX];
    int i = 0;
    int decisao = 1;

    while(decisao == 1 && i < MAX) {
        limparTela();
        printf("Insira um número: ");
        scanf("%d", &num[i]);
        i++;

        if(i < MAX) {
            decisao = menu();
        }
    }

    bubbleSort(num, i);
    exibir(num, i);

    return 0;
}