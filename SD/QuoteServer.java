import java.io.*;

public class QuoteServer {
	public static void main(String[] args) throws IOException {
		/*
			When created, the QuoteServerThread creates a DatagramSocket 
			on port 4445 (arbitrarily chosen). This is the DatagramSocket through
			which the server communicates with all of its clients.
		*/	
    new QuoteServerThread().start();
	}
}


/* 
	source and comments
	https://docs.oracle.com/javase/tutorial/networking/datagrams/clientServer.html
*/