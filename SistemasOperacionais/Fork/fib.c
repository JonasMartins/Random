#include <stdio.h>
#include <stdlib.h>

int fib(int i){ // RETORNA O FIBONACCI DE I (MUITO PRCESSAMENTO!) MÁS ELEGANTE
  if(i==0)
    return 0;
  else if(i==1)
    return 1;
  else
    return fib(i-1)+fib(i-2);
}
void seqFib(int inicio, int fim){ // PARTE A DO EXERCÍCIO
  int i;
  printf("Inicio: %d\nFim:%d\n",inicio,fim);
  for(i=inicio;i<fim;i++){
    printf("%d,",fib(i));
  }
  printf("\n");
}

int main(int argc, char **argv){

 seqFib(0,6);

  return EXIT_SUCCESS;

}