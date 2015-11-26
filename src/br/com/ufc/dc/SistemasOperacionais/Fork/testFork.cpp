#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{

  /*
    font: http://lia.ufc.br/~vinipires/testfork.cpp
  */

int pid ;
   printf("Eu sou o pai %d e eu vou criar um filho \n",getpid()) ; // pega o pid do programa como um todo
   pid=fork() ; /* criacao do filho */
   if(pid==-1) /* erro */
   {
      perror("impossivel de criar um filho\n") ;
   }
   else if(pid==0) /* acoes do filho */
   {
      printf("\tOi, eu sou o processo %d, o filho\n",getpid()) ;
      printf("\tO dia esta otimo hoje, nao acha?\n") ;
      printf("\tBom, desse jeito vou acabar me instalando para sempre\n");
      printf("\tOu melhor, assim espero!\n") ;
      for(;;) ; /* o filho se bloqueia num loop infinito */ // temos que usar o kill -9 <pid> para matar o filho
   }
   else /* acoes do pai */
   {
       sleep(1) ; /* para separar bem as saidas do pai e do filho */
       printf("As luzes comecaram a se apagar para mim, %d\n",getpid()) ;
       printf("Minha hora chegou : adeus, %d, meu filho\n",pid) ;
       /* e o pai morre de causas naturais */
    }
    exit(0);
}