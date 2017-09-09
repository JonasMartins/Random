import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.UnknownHostException;
import java.io.InputStreamReader;
import java.net.Socket;

public class TCPClient {
  public static void main(String args[]) throws UnknownHostException, IOException {

    int porta = 6789;
    int num1, num2;
    num1 = num2 = 1;



    if (args.length != 5) {
      System.out.println("Run: java Client [hostname], [porta], [num1], [num2], [op]");
      System.exit(0);
    }

    try {

      porta = Integer.parseInt(args[1]);
      num1 = Integer.parseInt(args[2]);
      num2 = Integer.parseInt(args[3]);
    
    } catch(NumberFormatException e) {
      System.out.println("Invalid port number");
      e.printStackTrace();
      System.exit(0);
    }

    if(!testOp(args[4])){
        System.out.println("Invalid operation");
        System.exit(0);   
    }

    String sentence;
    String modifiedSentence;
    BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
   
    Socket clientSocket = new Socket("127.0.0.1", 6789);
    DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
    
    BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
    sentence = inFromUser.readLine();

    outToServer.writeBytes(sentence + '\n');
    modifiedSentence = inFromServer.readLine();
    System.out.println("FROM SERVER: " + modifiedSentence);
    clientSocket.close();
  }

  static boolean testOp(String op){
    System.out.println(op);
    String[] operations = {"soma", "subtracao", "divisao", "multiplicacao"};
    boolean flag = false;
    for(int i = 0; i < 4; i++){
        if(op.equals(operations[i]))
            flag = true;
    }
    return flag;
  }
}
