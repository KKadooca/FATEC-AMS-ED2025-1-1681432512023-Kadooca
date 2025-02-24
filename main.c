#include <stdio.h>
#include <stdlib.h>

// Declarando variaveis
float produto;
float desconto;
double vFinal;
char porc = '%';

// Declarando ponteiros
float *preco = &produto;
float *promo = &desconto;
double *ValorF = &vFinal;

// Criando a funcao
void aplicar(float *preco, float *promo, double *ValorF) {
	*ValorF = *preco - (*preco * *promo / 100);
}

// Funcao limpar tela
void limparTela() {
#ifdef _WIN32
	system("cls");  // Limpar tela -> Windows
#else
	system("clear");  // Limpar tela -> Linux & MacOS
#endif
}

// Programa principal
void main()
{
	while(1) { // Inicio loop 1

		printf("Insira o valor do produto: R$");
		scanf("%f", preco);

		if (*preco < 0) {
			limparTela();
			printf("Erro: insira um preco valido\n\n");
		}
		else {
			break; // Fim loop 1
		}
	}

	while(1) { // Inicio loop 2

		printf("Insira a porcentagem do desconto: ");
		scanf("%f", promo);

		if (*promo < 0 || *promo > 100) {
			limparTela();
			printf("Insira o valor do produto: R$%.2f\n", *preco);
			printf("\nErro: insira um desconto valido\n\n");
		}
		else {
			break; // Fim loop 2
		}
	}

	aplicar(preco, promo, ValorF);

	limparTela();
	printf("\n|| ------------------------------------- ||");
	printf("\n    Valor inicial do produto: R$%.2f\n", *preco);
	printf("    Desconto aplicado: %.2f%c\n", *promo, porc);
	printf("    Valor final com desconto: R$%.2f\n", *ValorF);
	printf("|| ------------------------------------- ||");
}
