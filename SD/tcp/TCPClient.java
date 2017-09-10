
import java.net.Socket;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.UnknownHostException;

public class TCPClient {

  static int num1, num2;
  static int porta = 6789;
  static FileInputStream fis = null;
  static ObjectInputStream in = null;
  static FileOutputStream fos = null;
  static ObjectOutputStream out = null;
  static final String filename = "requisicao.ser";

  /**
   * [main description]
   * @param  args                   [description]
   * @throws UnknownHostException   [description]
   * @throws IOException            [description]
   * @throws ClassNotFoundException [description]
   *
   *  INSTRUÇÕES RUN:
   *
   *  COMPILAR TODAS AS CLASSES:
   *
   *  javac *.java
   *
   *  RUN SERVER:
   *
   *  java TCPServer
   *
   *  RUN CLIENT:
   *
   *  java TCPClient 127.0.0.1 5678 10 5 divisao
   * 
   */
  
  public static void main(String[] args) throws UnknownHostException, IOException, ClassNotFoundException {
  
      num1 = num2 = 1;

      if (args.length != 5) { System.out.println("Run: java Client [hostname], [porta], [num1], [num2], [op]");
        System.exit(0);
      }

      try {

        num1 = Integer.parseInt(args[2]);
        num2 = Integer.parseInt(args[3]);
        porta = Integer.parseInt(args[1]);
      
      } catch(NumberFormatException e) { System.out.println("Invalid port number"); 
        e.printStackTrace();
        System.exit(0);
      }

      if(!testOp(args[4])){ System.out.println("Invalid operation"); System.exit(0); }

      
      
      Requisicao r = new Requisicao(num1, num2, args[4]);
       
      
      BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
      Socket clientSocket = new Socket(args[0], porta);

      out = new ObjectOutputStream(clientSocket.getOutputStream());
      
      /* ENVIANDO O OBJETO SERIALIZADO COM AS ENTRADAS DADAS */
      out.writeObject(r);


      /* OPCIONAL */
      //serializeRequisition(r,filename);
      //readRequisition(r,filename);
      

      /* RECEBENDO DO SERVER, JÁ COM O CALCULO FEITO E ARMAZENADO  NO OBJETO */
      in = new ObjectInputStream(clientSocket.getInputStream());
      

      /* LENDO RESPOSTA */
      Requisicao rr = (Requisicao) in.readObject();

      /* PRINTANDO RESPOSTA */

      System.out.println(rr.toString());
      System.out.println("Result:" + rr.getResult());


      /* CLOSE CONNECTION SOCKET */
      clientSocket.close();
  }

  /**
   * [testOp description] : TESTAR SE A ENTRADA DA OPERAÇÃO DE ENTRADA DO PROGRAMA CONFERE COM AS 4 OPERAÇÕES VÁLDAS
   * @param  op [description] : TIPO DE OPERAÇÃO A SER REALIZADA
   * @return    [description] : BOOLEAN COM A POSSIBILIDADE DA ENTRADA ESTAR DENTRO DO ARRAY COM AS OPÇÕES VÁLIDAS
   */
   static boolean testOp(String op){

          String[] operations = {"soma", "subtracao", "divisao", "multiplicacao"};
          boolean flag = false;
          for(int i = 0; i < 4; i++){
              if(op.equals(operations[i]))
                  flag = true;
          }
          return flag;
        }
  
  /**
   * [serializeRequisition description] 
   * @param r        [description] : OBJETO REQUISICAO
   * @param filename [description] : NOME DO ARQUIVO A SER SERIALIDO EM ARQUIVO
   */
   static void serializeRequisition(Requisicao r, String filename) {
       try {
              fos = new FileOutputStream(filename);
              out = new ObjectOutputStream(fos);
              
              // send object to server
              out.writeObject(r);
              
              out.close();
          } catch (Exception ex) {
              ex.printStackTrace();
          }
   }

   /**
   * [readRequisition description] : LER UM OBJETO SERIALIZADO EM UM ARQUIVO
   * @param r        [description] : OBJETO REQUISICAO
   * @param filename [description] : NOME DO ARQUIVO A SER SERIALIDO EM ARQUIVO
   */
   static void readRequisition(Requisicao r, String filename) {
       try {
              fis = new FileInputStream(filename);
              in = new ObjectInputStream(fis);
              r = (Requisicao) in.readObject();
              in.close();
       } catch (Exception ex) { ex.printStackTrace(); }
    System.out.println(r);
  }
}
