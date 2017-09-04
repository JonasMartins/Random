import java.net.*;
import java.io.*;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/*
  Conceito de pool: ao invés de criar infinitas threads para cada linha de execução
  um cliente como neste exemplo, podemos usar uma pool de threads onde ficam algumas
  threads em uma pool e podemos solicitar quando o processo precisa de uma e se não
  hoverem threads disponíveis o sistema espera o término de alguma.

  Três tipos de pools Java

  pool de tamanho 1 -> newSingleThreadExecutor()
  pool de tamanho exato passado como argumento -> newFixedThreadPool(int size)
  pool não ligada reusando threads nas instâncias -> newCachedThreadPool()

*/




public class DateServer4 implements Runnable{

  public DateServer4(){};/*Constructor*/

  public static void main(String[] args){/*parent thread, the main method*/

       /* Três tipos de pool */

    //ExecutorService pool = Executors.newFixedThreadPool(5);
    //ExecutorService pool = newSingleThreadExecutor()
    ExecutorService pool = newCachedThreadPool();

   /*Obs: só trocar o tipo de pool para ver o comportamento de cada thread
    "Contando com a participação do DateClient"
   */

    while (true) {

      Thread t = new Thread(new DateServer4());
      pool.execute(t);

    }
    /*finish all tasks*/
    pool.shutdown()
  }
  public void run(){

    try{
        ServerSocket sock = new ServerSocket(6013);
        // listen for connections
        // while(true){// laço infinito

          Socket client =sock.accept(); // criando um novo socket
          PrintWriter pout = new
          PrintWriter(client.getOutputStream(),true);

          //write the data to socket
          pout.println(new java.util.Date().toString());
          // escreve a data no cliente, poderia ser qq ação

          //close the socket and resume
          //listening for connections
          client.close();
      //}
    }
    catch(IOException ioe){
      System.err.println(ioe);
    }

  }

}