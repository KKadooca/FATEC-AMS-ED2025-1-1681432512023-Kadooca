/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: Atividade B1-2                          */
/*                  Objetivo: <<  Manipular arrays com um desafio prático  >>       */
/*                                                                                  */
/*                                  Autor: Kauan A. Kadooca Bastos                  */
/*                                                                   Data:12/03/2025*/
/*----------------------------------------------------------------------------------*/

#include <stdio.h>

#define MAX_CANDIDATOS 50
#define MAX_NOME 100

typedef struct {
    char nome[MAX_NOME];
    float pe[4];
    float ac[5];
    float pp[10];
    float eb[3];
    float nota_final;
} Candidato;

void ler_notas(float *notas, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        float nota;
        do {
            printf("Nota %d: ", i + 1);
            scanf("%f", &nota);
            if (nota < 0.0 || nota > 10.0) {
                printf("Nota inválida. Digite uma nota entre 0.0 e 10.0.\n");
            }
        } while (nota < 0.0 || nota > 10.0);
        notas[i] = nota;
    }
}

float calcular_nota_central(float *notas, int quantidade) {
    float maior = notas[0], menor = notas[0], soma = 0;
    for (int i = 0; i < quantidade; i++) {
        if (notas[i] > maior) maior = notas[i];
        if (notas[i] < menor) menor = notas[i];
        soma += notas[i];
    }
    return (soma - maior - menor) / (quantidade - 2);
}

float calcular_nota_final(Candidato candidato) {
    float nota_pe = calcular_nota_central(candidato.pe, 4);
    float nota_ac = calcular_nota_central(candidato.ac, 5);
    float nota_pp = calcular_nota_central(candidato.pp, 10);
    float nota_eb = calcular_nota_central(candidato.eb, 3);
    return (nota_pe * 0.3) + (nota_ac * 0.1) + (nota_pp * 0.4) + (nota_eb * 0.2);
}

void ordenar_candidatos(Candidato *candidatos, int quantidade) {
    for (int i = 0; i < quantidade - 1; i++) {
        for (int j = 0; j < quantidade - i - 1; j++) {
            if (candidatos[j].nota_final < candidatos[j + 1].nota_final) {
                Candidato temp = candidatos[j];
                candidatos[j] = candidatos[j + 1];
                candidatos[j + 1] = temp;
            }
        }
    }
}

int comparar_strings(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

void copiar_string(char *destino, const char *origem) {
    while (*origem) {
        *destino = *origem;
        destino++;
        origem++;
    }
    *destino = '\0';
}

void imprimir_classificacao(Candidato *candidatos, int quantidade) {
    printf("\nClassificação dos 5 melhores candidatos:\n");
    int limite = (quantidade < 5) ? quantidade : 5;
    for (int i = 0; i < limite; i++) {
        printf("%d. %s - Nota Final: %.2f\n", i + 1, candidatos[i].nome, candidatos[i].nota_final);
    }
}

int main() {
    Candidato candidatos[MAX_CANDIDATOS];
    int quantidade_candidatos = 0;

    printf("Digite os dados dos candidatos (máximo %d):\n", MAX_CANDIDATOS);

    while (quantidade_candidatos < MAX_CANDIDATOS) {
        printf("\nCandidato %d:\n", quantidade_candidatos + 1);

        printf("Nome: ");
        scanf(" %[^\n]s", candidatos[quantidade_candidatos].nome);

        printf("Notas da Prova Escrita (PE):\n");
        ler_notas(candidatos[quantidade_candidatos].pe, 4);

        printf("Notas da Análise Curricular (AC):\n");
        ler_notas(candidatos[quantidade_candidatos].ac, 5);

        printf("Notas da Prova Prática (PP):\n");
        ler_notas(candidatos[quantidade_candidatos].pp, 10);

        printf("Notas da Entrevista em Banca Avaliadora (EB):\n");
        ler_notas(candidatos[quantidade_candidatos].eb, 3);

        candidatos[quantidade_candidatos].nota_final = calcular_nota_final(candidatos[quantidade_candidatos]);

        quantidade_candidatos++;

        char continuar;
        printf("Deseja inserir outro candidato? (s/n): ");
        scanf("%c", &continuar);
        if (continuar != 's' && continuar != 'S') {
            break;
        }
    }

    ordenar_candidatos(candidatos, quantidade_candidatos);
    imprimir_classificacao(candidatos, quantidade_candidatos);

    if (quantidade_candidatos > 0) {
        printf("\nDemonstração de memória - Primeiro candidato:\n");
        printf("Nome: %s\n", candidatos[0].nome);
        printf("Notas EB: %.2f, %.2f, %.2f\n", candidatos[0].eb[0], candidatos[0].eb[1], candidatos[0].eb[2]);
    }

    return 0;
}