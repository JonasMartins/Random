import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;

public class Client {
    
  public static void main(String[] args) {
  
    int porta = 1234;
  
    /**
     * USO, AO RODAR O CLIENTE, ESPERAMOS 3 ARGUMENTOS, O HOSTNAME, A PORTA E A
     * MENSAGEM QUE VAI SER DEVELVIDA INVERTIDA PELO SERVIDOR
     * 
     */
    if (args.length != 3) {
      System.out.println("Run: java Client [hostname], [porta], [msg]");
      return;
    }
    
    try {
      porta = Integer.parseInt(args[1]);
    } catch(NumberFormatException e) {
      System.out.println("Invalid port number");
      e.printStackTrace();
    }
    
    byte[] buf = new byte[256];
    
    buf  = args[2].getBytes();
    
    try {
      
      // send request
      DatagramSocket socket = new DatagramSocket();
      InetAddress address = InetAddress.getByName(args[0]);
      DatagramPacket packet = new DatagramPacket(buf, buf.length, address, porta);
      
      // **********************

      // TIMEOUT 3 SEGUNDOS 
      socket.setSoTimeout(3000);

      // **********************

      
      socket.send(packet);
      
      // get response
          packet = new DatagramPacket(buf, buf.length);
          socket.receive(packet);
      
          // display response
          String received = new String(packet.getData(), 0, packet.getLength());
          System.out.println("From server: " + new String(revertString(received)));
          
      socket.close();
      
    } catch (SocketException e) {
      e.printStackTrace();
    } catch (UnknownHostException e) {
      e.printStackTrace();
    } catch (IOException e) {
      e.printStackTrace();
    }
  }

  public static byte[] revertString(String input) {
    byte [] strAsByteArray = input.getBytes();
    byte [] result = new byte [strAsByteArray.length];
    for (int i = 0; i<strAsByteArray.length; i++){
      result[i] =  strAsByteArray[strAsByteArray.length-i-1];
    }
    return result;
  }

}
