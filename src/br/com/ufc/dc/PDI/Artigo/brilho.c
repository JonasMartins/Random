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

void contraste(FILE *arq, FILE *arq_saida,matriz*m){

	int i,j,k,l;
	//int min,max;
	//matriz *n;
	//n = malloc(sizeof(matriz));
	fscanf(arq,"%s",m->type);
	fscanf(arq,"%hu%hu%hu",&m->width,&m->height,&m->max); 
	//n->height=m->height;
	//n->width=m->width;
	//n->max=m->max;
	//m->height+=2;
	//m->width+=2;
	m->data = aloca_cinza(m->height,m->width);
	//n->data = aloca_cinza(n->height,n->width);
	arq_saida = fopen("brilhoPosMedia.pgm","wb+");
	fprintf(arq_saida,"%s\n%hu\n%hu\n%hu ","P5",m->width,m->height,m->max);

	for(i=0;i<m->height;i++){
		for(j=0;j<m->width;j++){
			fread(&m->data[i][j], sizeof(char), 1, arq);
		}
	}
	for(i=0;i<m->height;i++){
		for(j=0;j<m->width;j++){
			if(*(&m->data[i][j])>190 )
				*(&m->data[i][j])=255;
			}
		}

	for(i=0;i<m->height; i++){
		for(j=0;j<m->width; j++){	
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
	m = malloc(sizeof(matriz));
	contraste(arq,arq_saida,m);

	return EXIT_SUCCESS;

}
