import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class Servidor {
 public static void main(String[] args) throws IOException
 {
   ServerSocket servidor = new ServerSocket(12345);
   
   /** O servidor espera por 3 segundos por uma mensagem 
   do cliente */
   try {
    servidor.setSoTimeout(3);
   } 
   catch(SocketException e){
    e.printStackTrace();
   }
   System.out.println("Porta 12345 aberta!");
   
   Socket cliente = servidor.accept();
   System.out.println("Nova conexão com o cliente " +   
     cliente.getInetAddress().getHostAddress());
   
    Scanner entrada = new Scanner(cliente.getInputStream());
    while (entrada.hasNextLine()) {
     System.out.println(entrada.nextLine());
   }
   
   entrada.close();
   servidor.close();
 }
}