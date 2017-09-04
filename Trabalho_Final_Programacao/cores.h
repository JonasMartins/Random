#ifndef __CORES_TRABALHO

#define COR_NORMAL  	"\x1B[0m"
#define COR_VERMELHO  	"\x1B[31m"
#define COR_VERDE       "\x1B[32m"
#define COR_AMARELO  	"\x1B[33m"
#define COR_AZUL        "\x1B[34m"
#define COR_MAGENTA     "\x1B[35m"
#define COR_CIANO       "\x1B[36m"
#define COR_BRANCO      "\x1B[37m"
#define COR_PRETO       "\x1B[30m"

#define FUNDO_PRETO     "\x1B[40m"
#define FUNDO_VERMELHO	"\x1B[41m"
#define FUNDO_VERDE     "\x1B[42m"
#define FUNDO_AMARELO	"\x1B[43m"
#define FUNDO_AZUL      "\x1B[44m"
#define FUNDO_MAGENTA	"\x1B[45m"
#define FUNDO_CIANO     "\x1B[46m"
#define FUNDO_BRANCO	"\x1B[47m"
#define FUNDO_NORMAL	"\x1B[49m"

#define __CORES_TRABALHO
#endif
#define TRUE 1
#define FALSE 0



typedef struct lista{

	char *tentativa;
	struct lista *prox;

}Lista;

char * Limpa_String(char *string,int n);
char * Menu(Lista **l,char * tentativa,int n,int pc,int lim);
void Imprime_Menu(int indice);
void Start();
void Inicializar(Lista **l);
void Guarda_Tentativas(Lista **l,char *string,int n);
void Exibe(Lista *l);
void Sorteio(Lista **l,char *tentativa,char *comp,int n,int pc,int lim); //
void Colore(char *valor);
int Teste_n(int x);
int Teste_pc(int x);
int Teste_lim(int x);
int Tentativa_Repetida(Lista **l,char *string);



