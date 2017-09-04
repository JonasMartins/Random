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

void threshold(FILE *arq, FILE *arq_saida,matriz*m){

	int i,j;

	fscanf(arq,"%s",m->type);
	fscanf(arq,"%hu%hu%hu",&m->height,&m->width,&m->max);			
	m->data = aloca_cinza(m->height,m->width);	
	
	arq_saida = fopen("threshold.pbm","wb+");
	fprintf(arq_saida,"%s\n%hu\n%hu ","P1",m->height,m->width);

	for(i=0; i<m->height; i++){
		for(j=0; j<m->width; j++){
			fread(&m->data[i][j], sizeof(char), 1, arq);
			if(*(&m->data[i][j]) > 128){
				*(&m->data[i][j]) = 0;}
			else{*(&m->data[i][j]) = 1;}
			}
		}

	for(i=0; i<m->height; i++){
		for(j=0; j<m->width; j++){
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
	m = malloc(sizeof(matriz));// IMPORTANTE....
	
	threshold(arq,arq_saida,m);
	
	return EXIT_SUCCESS;

}
