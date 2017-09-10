import java.net.Socket;
import java.net.ServerSocket;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.BufferedWriter;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

import java.text.DateFormat;
import java.text.SimpleDateFormat;

import java.util.Date;

public class TCPServer {

  static boolean flag = true;
  static ObjectInputStream is = null;
  static String clientSentence = null;
  static Socket connectionSocket = null;
  static String capitalizedSentence = null;
  static ServerSocket welcomeSocket = null;

  static final String logFile = "log.txt";

  private static final DateFormat sdf = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");

  /**
   * [runServer description]
   * @throws IOException            [description]
   * @throws ClassNotFoundException [description]
   */
  
  public void runServer() throws IOException, ClassNotFoundException {

    welcomeSocket = new ServerSocket(5678);
    System.out.println("Running... at port 5678");

    while (flag) {

      connectionSocket = welcomeSocket.accept();
      is = new ObjectInputStream(connectionSocket.getInputStream());
      ObjectOutputStream os = new ObjectOutputStream(connectionSocket.getOutputStream());

      Object r = (Requisicao) is.readObject();

      /* FAZENDO A OPERAÇÃO */
      ((Requisicao) r).doOperation();

      /* ESCREVENDO O OBJETO COM O RESULTADO */
      os.writeObject(r);

      /* REGISTRANDO O LOG DO OBJETO */
      registerLog(r.toString());

      is.close();
    }
    /* CLOSE CONNECTION SOCKET */
    welcomeSocket.close();
  }

  public static void registerLog(String log){

    Date date = new Date();
    String currDate = sdf.format(date);

    log += " [127.0.0.1] ";
    log += currDate;

    File dir = new File("logs");
    dir.mkdirs();

    BufferedWriter bw = null;
    try{
      
      File file = new File(dir,logFile);
      
      if(!file.exists()){ file.createNewFile(); }

      bw = new BufferedWriter(new FileWriter(file, true));
      bw.write(log);
      bw.newLine();
      bw.flush();
    } catch (IOException ioe) {
        ioe.printStackTrace();
    } finally { 
      if (bw != null) {
        try {
          bw.close();
        } catch (IOException ioe2) { /*just ignore it*/ }
      }
    }
  }

  /**
   * [main description]
   * @param  args[]                 [description]
   * @throws ClassNotFoundException [description]
   * @throws IOException            [description]
   */
  public static void main(String args[]) throws ClassNotFoundException, IOException {

    new TCPServer().runServer();
  }
}
