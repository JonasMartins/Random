#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct {
	unsigned short height;
  unsigned short width;
	unsigned short max; 
	char type[5];
	int **data;
	
}matriz;

// CINZA, AFINAL EH UMA IMAGEM CINZA, NÃO PRECISA MULTIPLICAR AS COLUNAS POR 3

int **aloca_cinza( int lin, int col ){
	int **ret, i, j; 
	
  	if( lin ==0 || col ==0 ){
    	printf( "Impossivel alocar espaco\n" );
    	exit( 3 );
  	}
  	ret = malloc( sizeof(int*) * lin );
  	if( ret == NULL  ){
    	printf( "Impossivel alocar espaco" );
    	exit( 3 );
  	}
  	ret[0] = malloc( sizeof(int) * ( lin * col ) );
  	if( ret[0] == NULL  ){
    	printf( "Impossivel alocar espaco" );
    	exit( 3 );
  	}
  	for( i=1; i<lin; i++ )
    	ret[i] = ret[i-1] + col;
 	 return ret; 
}

void histograma(FILE *arq, FILE *arq_saida,matriz*m){

	int i,j,k=0,topo;

	double area,taxa,mxn = 76500; //300*255;	

	unsigned short vetor[256];
	for(i=0;i<256;i++)// IGUALANDO TUDO A 0.
		vetor[i]=0;


	fscanf(arq,"%s",m->type);
	fscanf(arq,"%hu%hu%hu",&m->height,&m->width,&m->max);		
	m->data = aloca_cinza(m->height,m->width);	
	
	area = m->height*m->width;
	
	for(i=0; i<m->height; i++){
		for(j=0; j<m->width; j++){
			fread(&m->data[i][j], sizeof(char), 1, arq);
		}
	}
	// PONDO OS VALORES NO VETOR
	for(i=0;i<m->height; i++){
		for(j=0; j<m->width; j++){
			vetor[*(&m->data[i][j])]++;
		}
	}
	
	//PRIMEIRO AS LINHAS E DEPOIS AS COLUNAS, IMPORTA NA ORDEM QUE EU ESCOLHER NA HORA DO FOR.
	arq_saida = fopen("histograma2.pbm","wb+");
	fprintf(arq_saida,"%s\n%hu\n%hu ","P1",255,300);

	for(i=0;i<300;i++){
		for(j=0;j<255;j++){
			*(&m->data[i][j])=0;	
		}
	}	

	while(k<256){// PREECHER TODOS OS 256.
		taxa = (mxn*vetor[k])/area;
		taxa*=0.4;// DIVIDINDO BASTANTE, MOSTRANDO APENAS 40% DO REAL VALOR DA TAXA.
		if(taxa>290){// UM LIMITE...
			taxa=290;
		}
		topo = 299-(int)taxa; // PARA COMEÇAR DE BAIXO PARA CIMA.
		for(i=299;i>=topo;i--){
			for(j=k;j<k+1;j++){
				*(&m->data[i][j])=1;	
			}
		}
		k++;
	}
	//AGORA SIM PRINTANDO A IMAGEM.
	for(i=0;i<300; i++){
		for(j=0;j<255;j++){
			fprintf(arq_saida,"%d",*(&m->data[i][j]));
		}
	}	

	fclose(arq);
	fclose(arq_saida);


}

int main(int argc, char**argv){

	FILE *arq;
	FILE *arq_saida;

	

	arq = fopen(argv[1],"rb+");
	matriz *m;  
	m = malloc(sizeof(matriz));
	
	histograma(arq,arq_saida,m);


	return EXIT_SUCCESS;

}
