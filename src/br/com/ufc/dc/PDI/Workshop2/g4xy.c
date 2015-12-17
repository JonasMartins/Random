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
int calcula(matriz*m, int x, int y){	
	int i,j,k,l;	
	int matrix[5][5];
	double result=0;
	
	for(k=0,i=(x-2);i<=(x+2);i++,k++){
		for(l=0,j=(y-2);j<=(y+2);j++,l++){
				matrix[k][l] = *(&m->data[i][j]);
		}
	}		
	for(i=0;i<5;i++){
		for(j=0;j<5;j++){
			result+=(matrix[i][j]);
		}	
	}
	result/=25;
	return (int)result;

}


void media(FILE *arq, FILE *arq_saida,matriz*m){

	int i,j,k,l;

	matriz *n;
	n = malloc(sizeof(matriz));

	fscanf(arq,"%s",m->type);
	fscanf(arq,"%hu%hu%hu",&m->width,&m->height,&m->max); 
	n->height=m->height;
	n->width=m->width;
	n->max=m->max;

	m->height+=4;
	m->width+=4;

	m->data = aloca_cinza(m->height,m->width);
	n->data = aloca_cinza(n->height,n->width); 

	arq_saida = fopen("g4xy.pgm","wb+");
	fprintf(arq_saida,"%s\n%hu\n%hu\n%hu ","P5",n->width,n->height,n->max);
	
	for(i=0;i<m->height; i++){
		for(j=0;j<m->width; j++){
			*(&m->data[i][j]) = 0;
		}
	}
	
	for(i=2;i<m->height-2;i++){
		for(j=2;j<m->width-2;j++){
			fread(&m->data[i][j], sizeof(char), 1, arq);
		}
	}
	
	for(k=0,i=2;k<n->height;k++,i++){ 
		for(l=0,j=2;l<n->width;l++,j++){
			*(&n->data[k][l]) = calcula(m,i,j);
		}
	}
	for(i=0;i<n->height; i++){
		for(j=0;j<n->width; j++){		
			fwrite(&n->data[i][j], sizeof(char), 1, arq_saida);
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
	
	media(arq,arq_saida,m);
	
	return EXIT_SUCCESS;

}
