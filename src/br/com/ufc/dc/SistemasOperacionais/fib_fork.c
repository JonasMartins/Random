#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

int fib(int i){

   if(i==0)
    return 0;
  else if(i==1)
    return 1;
  else
    return fib(i-1)+fib(i-2);
}
void seqFib_ForkVersion(int inicio, int fim){
  int i,j;
  printf("First: %d\nLast:%d\n",inicio,fim);
  int pid=fork();
  if(pid==-1)
    printf("Incapable to create any child process\n");
  else if(pid==0){
      printf("I'm a child process called %d\n",getpid());
      for(i=inicio;i<fim;i++){
        for(j=0;j<i;j++){ // subsequence...
          printf("%d,",fib(j));
        }
        printf(" {%d},",fib(i)); // fib atual...
      }
      printf("\n");
  }else{
    sleep(2);
    printf("I'm the parent process called %d\n",getpid());
    for(i=inicio;i<fim;i++){
        printf("%d,",fib(i));
      }
      printf("\n");
  }
}
int main(int argc, char **argv){

seqFib_ForkVersion(0,5);

  return EXIT_SUCCESS;
}