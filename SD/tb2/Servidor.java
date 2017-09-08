import java.io.IOException;

public class Servidor {
  public static void main(String[] args) {
    try {
      new ServerThread().start();
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
}