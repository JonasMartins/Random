#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"./cores.h"

int main(int argc, char **argv){

	Lista *l;
	unsigned short i,n,pc,lim,j,k;

	char cores[6][2] = {{"vm"},{"vd"},{"am"},{"az"},{"mg"},{"ci"}}; // TODAS AS CORES POSSÍVEIS


	Inicializar(&l);

	Start();
	printf("DIGITE O N: TAMANHO DA SENHA: ");
	scanf("%hu",&i);

	fflush(stdin);
    __fpurge(stdin);
	n = Teste_n(i);
	printf("DIGITE O PC: POSSIBILIDADES DE CORES: ");			// ENTRADAS.... E TESTES DE ENTRADAS.

	scanf("%hu",&i);
	fflush(stdin);
    __fpurge(stdin);
	pc = Teste_pc(i);

	printf("DIGITE O LIM: TENTATIVAS DE CHANÇES: ");
	scanf("%hu",&i);
	fflush(stdin);
    __fpurge(stdin);
	lim = Teste_lim(i);

	char combinacao_sorteada[n][2];

	srand((unsigned int)time(NULL));	// SEMENTE DO CLOCK.

	char *comp;
	comp = (char*)malloc(n*2*sizeof(char)); // VARIÁVEIS DINÂMICAS.

	char *Tentativa;
	Tentativa =(char*)malloc(100*sizeof(char));

	char *Tentativa_Limpa;
	Tentativa_Limpa =(char*)malloc(2*n*sizeof(char));//TAMAHO EXATO DE CARCTERES  NECESSÁRIOS.


	for(i=0;i<n;i++){    //TAMANHO DA SENHA;
		j = (int)rand()%pc;  //POSSIBILIDADES DE CORES
		for(k=0;k<2;k++){
			combinacao_sorteada[i][k] = cores[j][k]; // AQUI AS CORES SORTEADAS SÃO ARMAZENADAS;
		}
	}
	k=0;
	for(i=0;i<n;i++){
		for(j=0;j<2;j++,k++){
			comp[k]=combinacao_sorteada[i][j]; // AQUI TEMOS AS COMBINAÇÕES SORTEADAS TAMBÉM COM TAMANHO EXATO.
		}
	}

	while(lim>0){	// ATÉ QUE LIMITE CHEGUE A 0.

		Tentativa_Limpa = Menu(&l,Tentativa,n,pc,lim); // PEGA A TENTATIVA QUE FOI LIMPA DENTRO DO MENU, E RETORNA.
		lim--;
		i = Tentativa_Repetida(&l,Tentativa_Limpa);		// TESTE DE REPETIÇÃO, SE RETORNA 1, ENTRA DENTRO DO LAÇO.
		if(i==TRUE){
			while(i==TRUE){
				Tentativa_Limpa = Menu(&l,Tentativa,n,pc,lim);
				i = Tentativa_Repetida(&l,Tentativa_Limpa);		// ENQUANTO ESTIVER AQUI, O LIMITE NÃO DECRESCE, AO MENOS QUE O TESTE DE REPETIDA RETORNE 0
			}
		}
		Sorteio(&l,Tentativa_Limpa,comp,n,pc,lim);		// SÓ ENTRA PALAVRAS VÁLIDAS, QUE SERÃO GUARDADAS NA LISTA
	}

	return EXIT_SUCCESS;
}
