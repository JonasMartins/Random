#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h> /// USAR -lm PARA PODER USAR ESTA BIBLIOTECA.

typedef struct {
	unsigned short height;
  unsigned short width;
	unsigned short max; 
	char type[5];
	int **data;
	
}matriz;


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

void equaliza_histograma(FILE *arq,FILE *arq_saida,matriz*m){

	int i,j,area;
	double somatoria=0,aux;
	
	unsigned short vetor[256],vetor2[256];// PARA QUE NÃO INTERFERISSE NA SOMATÓRIA, USEI 2 VETORES
	for(i=0;i<256;i++){// IGUALANDO TUDO A 0.
		vetor[i]=0;
		vetor2[i]=0;
	}

	fscanf(arq,"%s",m->type);
	fscanf(arq,"%hu%hu%hu",&m->height,&m->width,&m->max);		
	m->data = aloca_cinza(m->height,m->width);	
	
	arq_saida = fopen("equalizado.pgm","wb+");
	fprintf(arq_saida,"%s\n%hu\n%hu\n%hu ",m->type,m->height,m->width,m->max);



	area = (m->width*m->height);	

	for(i=0; i<m->height; i++){
		for(j=0; j<m->width; j++){
			fread(&m->data[i][j], sizeof(char), 1, arq);
		}
	}
	// ENCHENDO O VETOR COM OS VALORS
	for(i=0;i<m->height; i++){
		for(j=0; j<m->width; j++){
			vetor[*(&m->data[i][j])]++;
		}
	}

	for(i=0;i<256;i++){	
		for(j=i;j>=0;j--){
			aux = ((float)vetor[j])/area;
			somatoria+=aux;					
		}	
		vetor2[i] =(int)(255*somatoria);
		somatoria = 0;	
	}	
		/* MUDANDO OS VALORES DA MATRIZ... 
		*A INENSICADE ORIGINAL VAI RECEBER A INTENCIDADE EQUALIZADA
	 *QUE ESTÁ NO VETOR2 PREENCHIDO NO BLOCO ANTERIROR.
	*UM BLOCK PARA QUE OS PIXELS NÃO PASSEM DE 255 COMO NA IMPLEMENTAÇÃO DO
 *GAMMA CORRECTION.	
*/
	for(i=0;i<m->height; i++){
		for(j=0; j<m->width; j++){
			*(&m->data[i][j]) = vetor2[*(&m->data[i][j])];
			if(*(&m->data[i][j]) > 255){	// SE PASSAR DE 255 É IGUAL A 255.
				*(&m->data[i][j]) = 255;
			}		
		}
	}
	//APENAS ESCREVO COM OS VALORES ALTERADOS NA IMAGEM DE SAÍDA.
	for(i=0; i<m->height; i++){
		for(j=0; j<m->width; j++){
			fwrite(&m->data[i][j], sizeof(char), 1, arq_saida);
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
	m = malloc(sizeof(matriz));// IMPORTANTE....
	
	equaliza_histograma(arq,arq_saida,m);	

	return EXIT_SUCCESS;
	

}
