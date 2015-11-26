#include <iostream>
#include <string>

// Required by for routine
#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>   // Declaration for exit()

using namespace std;

int globalVariable = 2;

/*
  FONT: http://www.yolinux.com/TUTORIALS/ForkExecProcesses.html

  APENAS MOSTRANDO COMO O PROCESSO É DIVIDIDO, OU SEJA  É EXECUTADO DUAS VESES
  ONDE PARA DIFERENCIAR QUANDO O PID = 0 FILHO 2 VARIÁVEIS SÃO INCREMENTADAS PARA
  QUE SEJA VERIFICADA A DIFERENÇA.
*/


main()
{
   string sIdentifier;
   int    iStackVariable = 20;

   pid_t pID = fork(); // fork retorna o pid do processo, e  cria um filho e ambos serão executados a sguir
   // pid_t é um tipo da biblioteca <sys/types.h> e esse pid é um inteiro podemos usar tbm getpid();

   if (pID == 0)                // child
   {
      // Code only executed by child process

      sIdentifier = "Child Process: ";
      globalVariable++;
      iStackVariable++;
    }
    else if (pID < 0)            // failed to fork
    {
        cerr << "Failed to fork" << endl;
        exit(1);
        // Throw exception
    }
    else                                   // parent
    {
      // Code only executed by parent process

      sIdentifier = "Parent Process:";
    }

    // Code executed by both parent and child.

    cout << sIdentifier;
    cout << " Global variable: " << globalVariable;
    cout << " Stack variable: "  << iStackVariable << endl;
}
