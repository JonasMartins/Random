import java.net.*;
import java.io.*;

public class DateServer3 implements Runnable{

  public DateServer3(){};/*Constructor*/

  public static void main(String[] args){// parent thread, the main method

    while (true) {

      Thread t = new Thread(new DateServer3());
      t.start(); // criando uma thread para cada chamada
      try{
        t.join(); // esperando o termino de uma thread
      }catch(InterruptedException ie){};
    }
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