#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h> 

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

void gama(FILE *arq, FILE *arq_saida,matriz*m){

	int i,j,min,max;
	double faixa,gama=1.2;

	fscanf(arq,"%s",m->type);
	fscanf(arq,"%hu%hu%hu",&m->height,&m->width,&m->max);			
	m->data = aloca_cinza(m->height,m->width);	

	arq_saida = fopen("g7xy.pgm","wb+");
	fprintf(arq_saida,"%s\n%hu\n%hu\n%hu ",m->type,m->height,m->width,m->max);

	for(i=0; i<m->height; i++){
		for(j=0; j<m->width; j++){
			fread(&m->data[i][j], sizeof(char), 1, arq);
			faixa = pow(*(&m->data[i][j]),gama);
			*(&m->data[i][j]) = (int)faixa;
		}
	}
	// normalizar
	min = *(&m->data[0][0]);
	max = *(&m->data[0][0]);
	for(i=0;i<m->height; i++){ // min
		for(j=0;j<m->width; j++){
			if(*(&m->data[i][j])<min)
					min = *(&m->data[i][j]);
			}
		}
	for(i=0;i<m->height; i++){ //max
		for(j=0;j<m->width; j++){
			if(*(&m->data[i][j])>max)
					max = *(&m->data[i][j]);
			}
		}	
	max-=min;
	for(i=0;i<m->height; i++){ // diminui tudo pelo min
		for(j=0;j<m->width; j++){
				*(&m->data[i][j])-=min;
			}
		}
	for(i=0;i<m->height; i++){ // passo final da normalização
		for(j=0;j<m->width; j++){
				*(&m->data[i][j])*=(255.0/max);
			}
		}		


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
	gama(arq,arq_saida,m);
	return EXIT_SUCCESS;

}
