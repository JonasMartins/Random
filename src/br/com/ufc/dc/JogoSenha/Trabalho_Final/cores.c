
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"./cores.h"


// TESTES PARA OS LIMITES DAS ENTRADAS.

int Teste_n(int x){
	unsigned short a;
	if(x<4 || x>12){	
		printf("ERRO DEVE SER UM NÚMERO >= 4 e <= 12\nDIGITE NOVAMENTE: ");
		scanf("%hu",&a);
		while(a<4 || a>12){
			printf("ERRO DEVE SER UM NÚMERO >= 4 e <= 12\nDIGITE NOVAMENTE: ");
			scanf("%hu",&a);
			fflush(stdin);
	    __fpurge(stdin);					
			}
			return a;
	}else{return x;}			
}	
int Teste_lim(int x){
	unsigned short a;
	if(x<=0){	
		printf("ERRO DEVE SER UM NÚMERO >= 1\nDIGITE NOVAMENTE: ");
		scanf("%hu",&a);
		while(a<=0){
			printf("ERRO DEVE SER UM NÚMERO >= 1\nDIGITE NOVAMENTE: ");
			scanf("%hu",&a);
			fflush(stdin);
	    __fpurge(stdin);					
			}
			return a;
	}else{return x;}			
}	
int Teste_pc(int x){
	unsigned short a;
	if(x<3 || x>6){	
		printf("ERRO DEVE SER UM NÚMERO >= 3 e <= 6\nDIGITE NOVAMENTE: ");
		scanf("%hu",&a);
		while(a<3 || a>6){
			printf("ERRO DEVE SER UM NÚMERO >= 3 e <= 6\nDIGITE NOVAMENTE: ");
			scanf("%hu",&a);
			fflush(stdin);
	    __fpurge(stdin);
			}
			return a;
	}else{return x;}			
}
void Imprime_Menu(int indice){	//AUXILIAR DO MENU.
	switch (indice){
		case 1:
			printf("%s - vm = VERMELHO\n",COR_VERMELHO);
			break;
		case 2:		
			printf("%s - vd = VERDE\n",COR_VERDE);
			break;		
		case 3:			
			printf("%s - am = AMARELO\n",COR_AMARELO);
			break;
		case 4:
			printf("%s - az = AZUL\n",COR_AZUL);
			break;
		case 5:
			printf("%s - mg = MAGENTA\n",COR_MAGENTA);
			break;
		case 6:
			printf("%s - ci = CIANO\n",COR_CIANO);
			}
}
void Start(){	// PRIMEIRAS INFORMAÇÕES.

	printf("\n\n\t========**JOGO SENHA**==========\n\n");
	printf("======== DIGITE AS SEGUINTES DEFINIÇÕES: =========\n\n(N):\tTAMANHO DA SENHA (4-12).\n\n");
	printf("(PC):\tPOSSIBILIDADES DE CORES (3-6).\n\n(LIM):\tLIMITE DE TENTATIVAS DE ADIVINHAÇÃO.\n\n(OBS: ACIMA DE 1 E SEM LIMITE SUPERIOR).\n\n");
}


void Colore(char *valor){	// COLORE O MENU.


if (strcmp(valor, "vm")==0)
		  printf("%s█  ",COR_VERMELHO); 
		else
		   if (strcmp(valor, "vd")==0)
		   	printf("%s█  ",COR_VERDE);
			  else    
		     if (strcmp(valor, "am")==0)
		       printf("%s█  ",COR_AMARELO);
			    else    
		       if (strcmp(valor, "az")==0)
		       	printf("%s█  ",COR_AZUL);
			      else    
		         if (strcmp(valor, "mg")==0)
		         	printf("%s█  ",COR_MAGENTA);
					   else    
		           if (strcmp(valor, "ci")==0)
		           	printf("%s█  ",COR_CIANO);
			          else 
		              printf ("VALOR INVÁLIDO!\n");       

}

void Sorteio(Lista **l,char *tentativa,char *comp,int n,int pc,int lim){
	int i,j,k,m,m2;
	
	/*
		COMPARA DE 2 EM 2 LETRAS, COM CERTEZA HÁ MEIOS MAIS SIMPLES, E MAIS EFICIENTES MAS, 
		FOI A LÓGICA EM QUE FOQUEI.

	*/


	
	printf("ATENÇÃO: VOCÊ TEM EXATAMENTE %d TENTATIVAS RESTANTES.\n\n",lim);  
	/*
		ANTES, VEMOS SE O USUÁRIO ACERTOU

		printf("Sorteado:  %s\n",comp);		//STRING SORTEADA.
		printf("Tentativa: %s\n",tentativa);	//TENTATIVA DO USUÁRIO.

	*/

	char *buffer;
	buffer = (char*)malloc(2*sizeof(char));

/*=====	TESTE DE ACERTO DEFINITIVO, APENAS UMA APRESENTAÇÃO, E COMPROVAÇÃO DE ACERTO PONDO ASMBAS LADO A LADO. */

	if(strcmp(tentativa, comp)==0){
		printf("PARABENS! VOCÊ ACERTOU!\n");
		for(i=0;i<(2*n);i+=2){
			for(j=0;j<1;j++){
					buffer[j] = tentativa[i];	//TENTEATIVA.
					buffer[j+1] = tentativa[i+1];
					Colore(buffer);
			}
		}
		printf("%s==== ",COR_NORMAL);

		for(i=0;i<(2*n);i+=2){
			for(j=0;j<1;j++){
					buffer[j] = comp[i];	//SORTEADO.
					buffer[j+1] = comp[i+1];
					Colore(buffer);
			}
		}
		printf("%s!!!!!",COR_NORMAL);
		printf("\n");
		exit(0);
	}
//=====  JÁ FAÇO UMA COMPARAÇÃO DE CARA, SE HOUVE ACERTO IMPRIME A MENSSAGEM E SAI DO PROGRAMA.
	
	char *buffer2;
	buffer2 = (char*)malloc(2*n*sizeof(char));

	
	for(i=0;i<(2*n);i+=2){
		for(j=0;j<1;j++){
				buffer[j] = tentativa[i];			//COLORINDO A TENTEATIVA.
				buffer[j+1] = tentativa[i+1];
				Colore(buffer);

			}
		}
		printf("%s----> ",COR_NORMAL);
	
	for(i=0;i<(2*n);i+=2){//INÍCIO.

		for(j=0;j<1;j++){	// FAZ APENAS UM LAÇO, PARA PEGAR DE DUAS EM DUAS LETRAS, BUFFER SÓ TEM 2 BYTES 2*SIZEOF(CHAR).
				m=FALSE;
				buffer[j] = tentativa[i];
				buffer[j+1] = tentativa[i+1];
			
				for(k=0;k<(2*n);k+=2){
					if(buffer[j]==comp[k] && buffer[j+1]==comp[k+1]){	// FICOU ENEROME PARA IMRIMIR APENAS N CARACTERES NA ORDEM CORRETA E
						m2=FALSE;																				// MESMO ASSIM, HÁ "ALÉATORIEDADES" SE FOREM DADAS APENAS 3 CORES.
						if(i == k && i+1 == k+1 && m2==FALSE){
							buffer2[i] = '@';				// DECIDINDO SE IMPRIME @, LETRAS IGUAIS "E" ÍNDICES IGUAIS.
							buffer2[i+1] = ' ';	
							m=TRUE;
							m2=TRUE;		
						}
						if(i != k && i+1 != k+1 && m2==FALSE){
							buffer2[i] = '!';				// SE FOR IGUAL, POREM COM ÍNDICES DIFERENTES DE COMP.
							buffer2[i+1] = ' ';
							m=TRUE;
							m2=TRUE;
						}
					}
				}
				m2=FALSE;
				if(m==FALSE && m2==FALSE){	// SE NÃO FOREM DE FORMA ALGUMA IGUAIS, E NEM FOR ENCONTRADO EM COMP, ENTRA - ,MAIS UMA DICA PARA O USUÁRIO.
					buffer2[i] = '-';				
					buffer2[i+1] = ' ';
					m2=TRUE;
				}
			}
	
		}//FIM
		printf("%-1s\n",buffer2);	// ESCREVENDO MAIS A FRENTE.
		Guarda_Tentativas(l,tentativa,n);//ALOCANDO NA LISTA AS TENTATIVAS UE JÁ FORAM SORTEDAS, LOGO VÁLIDAS.
		printf("VOCÊ NÃO ACERTOU DESTA VEZ, CONTINUE TENTANDO.\n");

	free(buffer);
	free(buffer2);
	free(tentativa);


}
void Guarda_Tentativas(Lista **l,char *string,int n){ // STRUTURA ESCOLHIDA, LISTA ENCADEADA PARA ARMAZENAR AS TENTATIVAS.

	Lista *novo;

	novo = (Lista*)malloc(sizeof(Lista));

	novo->tentativa =(char *)malloc(2*n*sizeof(char));//ALOCANDO A STRING.
	strcpy(novo->tentativa,string);
	novo->prox = NULL;
	
	if((*l) == NULL){	// INSERÇÃO BEM SIMPLES APENAS PÕE AO FINAL DA LISTA.
		(*l) = novo;
	}else{
		novo->prox = (*l);
		(*l) = novo;
	}
	
}


int Tentativa_Repetida(Lista **l,char *string){// TESTE DE REPETIÇÃO, APENAS VERIFICA SE A STRING JÁ ESTÁ LÁ.
	Lista *m;
	int Stop = FALSE;
		m=(*l);

		if((*l)==NULL){	// IMPORTANTE RETORNAR FALSO AQUI.
			return Stop;
		}
		else{
			while(m!=NULL){
				if(strcmp(m->tentativa, string)==0){
					printf("VOCÊ JÁ TENTOU ENTA COMBINAÇÃO ANTES!...TENTE OUTRA.\n");	// SE ENTRAR AQUI RETORNA 1.
					Stop =  TRUE;
					}
				m=m->prox;
			}
		}
	return Stop;  // SE FOR 0, OK, SE 1, JÁ FOI DADO.
}


void Exibe(Lista *l){// EXIBIR ELEMETOS SALVOS NA LISTA.
	Lista *m;
	m=l;
	while(m!=NULL){
		printf("%s\n",m->tentativa);
		m=m->prox;
	}
}


char * Limpa_String(char *string,int n){	// LIMPA STRING, SE FOR INCOMPATÍVEL COM 2*N RESULTA EM ERRO FATAL.
	int i,j=0;
	char *s;

	s = (char*)malloc(n*3*sizeof(char)); // UM CAPRICHO PARA NÃO OCORRER UM OVERFLOW.
	
	for(i=0;i<=strlen(string);i++){
		if(string[i] != ',' && string[i] != ' '){
			s[j] = string[i];
			j++;
		}
	}
	system("clear");
	if(strlen(s) != n*2){
		printf("***********\nERRO FATAL NO NÚMERO DE ARGUMENTOS NECESSÁRIOS PARA O TESTE.\n");
		printf("SEU PALPITE DE TERVE %d CORES, COM DUAS LETRAS PARA REPRESENTAR CADA COR.\n***********\n",n);
		exit(0);
	}else{
		return s;	// RETORNA LIMPA.
	}
	free(s); //**
}

char * Menu(Lista **l,char * tentativa,int n,int pc,int lim){
	
	int i;

	char *tentativa_limpa;
	tentativa_limpa =(char*)malloc(2*n*sizeof(char));//TAMAHO EXATO DE CARCTERES  NECESSÁRIOS.


	printf("\n\n\t*** MENU ***\n\n* ENTRE COM ACOMBINAÇÃO DE  %hu ELEMENTOS DENTRE AS %hu CORES SEGUINTES:\n\n",n,pc);

	for(i=1;i<=pc;i++){
			Imprime_Menu(i);
		}
	printf("%s\n\n* ENTRE COM SUA TENTATIVA, SEPARANDO-AS COM VIRGULAS:\n",COR_NORMAL);		// RECEBE A STRING, COM ESPAÇOS, VIRGULAS ETC.
	scanf("%[^\n]",tentativa);
	fflush(stdin);
	__fpurge(stdin);
	tentativa_limpa = Limpa_String(tentativa,n);	//LIMPA E RETORNA.
	return tentativa_limpa;
	lim--;

}

void Inicializar(Lista **l){
	(*l) = NULL;
}



