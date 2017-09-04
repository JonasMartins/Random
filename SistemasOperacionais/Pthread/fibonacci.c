#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


typedef struct {
  int value;
  int index;
}structShared;


/*Prototicos*/
int fib(int i);
void *RunFib(void *args);
void *ShowFib();
/*---------------*/

int array2[10]; //array global

void *RunFib(void *args){
  int j;
  structShared *i = (structShared *) args; /*casting*/

  printf("Comecou a thread %d\n", i->index);
  for(j=0;j<i->value;j++){/*thread executando o fibonacci*/
    array2[j]=fib(j); // colocando a primeira sequencia no array
  }
  printf("Terminou a thread %d\n", i->index);
//  pthread_exit(NULL);
}
void *ShowFib(void *args){// seunda thread imprime a sequencia
  int i;
  structShared *j = (structShared *) args;
  for (i = 0; i < j->value; ++i)
    printf("%d",array2[i]);
  printf("\n");
}

int fib(int i){

  if(i==0)
    return 0;
  else if(i==1)
    return 1;
  else
   return fib(i-1)+fib(i-2);
}



int main(int argc, char**argv){

  int i,j;
  int flag;
  pthread_t thread1,thread2;
  structShared s1,s2;
  printf("%s\n","Digite o número de termos da série fibonacci");
  scanf("%d",&j);

  s1.value = j;
  s1.index = 2;

  s2.value = j;
  s2.index = 1;


  pthread_create(&(thread2),NULL,RunFib,(void *)&(s1));
  pthread_create(&(thread1),NULL,ShowFib,(void *)&(s2));

  pthread_join(thread1,NULL);
  pthread_join(thread2,NULL);

  pthread_exit(NULL);

  return EXIT_SUCCESS;

}


/*
    A chamada à função pthread_create() tem quatro argumentos. O primeiro é usado para guardar informação
  sobre a thread criada. O segundo especifica algumas propriedades da thread a criar, utilizaremos o valor NULL
  para significar os valores por defeito. O Terceiro é a função que a nova thread vai executar e o ultimo é usado
  para representar argumentos a esta função.
  A chamada à função pthread_exit() provoca a terminação da thread e a libertação dos recursos que esta está a
  consumir. Aqui não há realmente necessidade para usar esta função porque quando a função da thread termine
  a thread seria destruída. A função é apenas útil se for necessário destruir a thread no meio da sua execução.
  A função a ser executada por uma nova thread tem sempre o formato:
  void * funcao ( void * argumentos ) ;


*/
