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

void g5xy(FILE *arq,FILE *arq2, FILE *arq_saida,matriz*m){

	int i,j,k,l;
	int min,max;
	matriz *n;
	n = malloc(sizeof(matriz));
	fscanf(arq,"%s",m->type);
	fscanf(arq,"%hu%hu%hu",&m->width,&m->height,&m->max); 

	fscanf(arq2,"%s",n->type);
	fscanf(arq2,"%hu%hu%hu",&n->width,&n->height,&n->max); 


	m->data = aloca_cinza(m->height,m->width);
	n->data = aloca_cinza(n->height,n->width);

	arq_saida = fopen("g5xy.pgm","wb+");
	fprintf(arq_saida,"%s\n%hu\n%hu\n%hu ","P5",n->width,n->height,n->max);

	for(i=0;i<m->height;i++){
		for(j=0;j<m->width;j++){
			fread(&m->data[i][j], sizeof(char), 1, arq);
		}
	}
	
	for(i=0;i<n->height;i++){
		for(j=0;j<n->width;j++){
			fread(&n->data[i][j], sizeof(char), 1, arq2);
		}
	}
		
	for(i=0;i<m->height;i++){// soma
		for(j=0;j<m->width;j++){
			*(&n->data[i][j]) *= *(&m->data[i][j]);
		}
	}

	// normalizar
	min = *(&n->data[0][0]);
	max = *(&n->data[0][0]);
	for(i=0;i<n->height; i++){ // min
		for(j=0;j<n->width; j++){
			if(*(&n->data[i][j])<min)
					min = *(&n->data[i][j]);
			}
		}
	for(i=0;i<n->height; i++){ //max
		for(j=0;j<n->width; j++){
			if(*(&n->data[i][j])>max)
					max = *(&n->data[i][j]);
			}
		}	
	max-=min;
	for(i=0;i<n->height; i++){ // diminui tudo pelo min
		for(j=0;j<n->width; j++){
				*(&n->data[i][j])-=min;
			}
		}
	for(i=0;i<n->height; i++){ // passo final da normalização
		for(j=0;j<n->width; j++){
				*(&n->data[i][j])*=(255.0/max);
			}
		}			
	for(i=0;i<m->height; i++){
		for(j=0;j<m->width; j++){
			fwrite(&n->data[i][j], sizeof(char), 1, arq_saida);
		}
	}

	fclose(arq);
	fclose(arq_saida);
}


int main(int argc, char**argv){

	FILE *arq;
	FILE *arq2;
	FILE *arq_saida;

	arq = fopen(argv[1],"rb+");
	arq2 = fopen(argv[2],"rb+");

	matriz *m;  
	m = malloc(sizeof(matriz));
	g5xy(arq,arq2,arq_saida,m);

	return EXIT_SUCCESS;

}
