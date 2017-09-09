import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

public class TCPServer {
  static boolean flag = true;
  public static void main(String argv[]) throws Exception {
    String clientSentence;
    String capitalizedSentence;
    ServerSocket welcomeSocket = new ServerSocket(6789);
    System.out.println("Running...");
    while (flag) {
      Socket connectionSocket = welcomeSocket.accept();
      BufferedReader inFromClient = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
      DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());
      clientSentence = inFromClient.readLine();
      System.out.println("Received: " + clientSentence);
      capitalizedSentence = clientSentence.toUpperCase() + '\n';
      outToClient.writeBytes(capitalizedSentence);
    }
    welcomeSocket.close();
  }
}