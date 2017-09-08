import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class ServerThread extends Thread {

  private DatagramSocket socket = null;
  private String message;
  
  public ServerThread() throws IOException {
      this("Server is running at port 1234");
      System.out.println("running");
    }
  
  public ServerThread(String message) {
    super(message);
    this.setMessage(message);
    try {
      this.socket = new DatagramSocket(1234);
    } catch (SocketException e) {
      e.printStackTrace();
    }
  }

  public void run() {
   while(true) {
      try {
        byte[] buf = new byte[256];
            // receive request
        buf = getMessage().getBytes();

        DatagramPacket packet = new DatagramPacket(buf, buf.length);
        socket.receive(packet);
          
        // send the response to the client at "address" and "port"
        InetAddress address = packet.getAddress();
        int port = packet.getPort();
        packet = new DatagramPacket(buf, buf.length, address, port);
        socket.send(packet);
              
      } catch (IOException e) {
        e.printStackTrace();
      }
    }
  }

  public byte[] revertString(String input) {
    byte [] strAsByteArray = input.getBytes();
    byte [] result = new byte [strAsByteArray.length];
    for (int i = 0; i<strAsByteArray.length; i++){
      result[i] =  strAsByteArray[strAsByteArray.length-i-1];
    }
    return result;
  }

  public String getMessage() {
    return message;
  }

  public void setMessage(String message) {
    this.message = message;
  }
}
