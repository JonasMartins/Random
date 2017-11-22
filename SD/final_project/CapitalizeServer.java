// nice example http://cs.lmu.edu/~ray/notes/javanetexamples/
// 

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * A server program which accepts requests from clients to
 * capitalize strings.  When clients connect, a new thread is
 * started to handle an interactive dialog in which the client
 * sends in a string and the server thread sends back the
 * capitalized version of the string.
 *
 * The program is runs in an infinite loop, so shutdown in platform
 * dependent.  If you ran it from a console window with the "java"
 * interpreter, Ctrl+C generally will shut it down.
 */
public class CapitalizeServer {

    /**
     * Application method to run the server runs in an infinite loop
     * listening on port 9898.  When a connection is requested, it
     * spawns a new thread to do the servicing and immediately returns
     * to listening.  The server keeps a unique client number for each
     * client that connects just to show interesting logging
     * messages.  It is certainly not necessary to do this.
     */
    public static void main(String[] args) throws Exception {
        System.out.println("The capitalization server is running.");
        int clientNumber = 0;
        ServerSocket listener = new ServerSocket(9898);
        try {
            while (true) {
                new Capitalizer(listener.accept(), clientNumber++).start();
            }
        } finally {
            listener.close();
        }
    }

    /**
     * A private thread to handle capitalization requests on a particular
     * socket.  The client terminates the dialogue by sending a single line
     * containing only a period.
     */
    private static class Capitalizer extends Thread {
        private Socket socket;
        private int clientNumber;

        public Capitalizer(Socket socket, int clientNumber) {
            this.socket = socket;
            this.clientNumber = clientNumber;
            log("New connection with client# " + clientNumber + " at " + socket);
        }

        /**
         * Services this thread's client by first sending the
         * client a welcome message then repeatedly reading strings
         * and sending back the capitalized version of the string.
         */
        public void run() {
            try {

                // Decorate the streams so we can send characters
                // and not just bytes.  Ensure output is flushed
                // after every newline.
                BufferedReader in = new BufferedReader(
                        new InputStreamReader(socket.getInputStream()));
                PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

                // Send a welcome message to the client.
                out.println("Hello, you are client #" + clientNumber + ".");
                out.println("Enter a line with only a period to quit\n");

                // Get messages from the client, line by line; return them
                // capitalized
                while (true) {
                    String input = in.readLine();
                    if (input == null || input.equals(".")) {
                        break;
                    }
                    out.println(input.toUpperCase());
                }
            } catch (IOException e) {
                log("Error handling client# " + clientNumber + ": " + e);
            } finally {
                try {
                    socket.close();
                } catch (IOException e) {
                    log("Couldn't close a socket, what's going on?");
                }
                log("Connection with client# " + clientNumber + " closed");
            }
        }

        /**
         * Logs a simple message.  In this case we just write the
         * message to the server applications standard output.
         */
        private void log(String message) {
            System.out.println(message);
        }
    }
}
/*
 run server before

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.io.BufferedReader;
import java.io.InputStreamReader;


 // This class implements a simple single-threaded proxy server.
  
 //  -- javac ProxyServer.java
 //  -- java ProxyServer 192.168.1.10 8080 9999

public class ProxyServer {

	public static void main(String[] args) throws IOException {
		try {
			// Check the number of arguments
			if (args.length != 3)
				throw new IllegalArgumentException("Wrong number of arguments.");
			// Get the command-line arguments: the host and port we are proxy for
			// and the local port that we listen for connections on
			String host = args[0];
			int remoteport = Integer.parseInt(args[1]);
			int localport = Integer.parseInt(args[2]);
			// Print a start-up message
			System.out.println("Starting proxy for " + host + ":" + remoteport + " on port " + localport);
			// And start running the server
			runServer(host, remoteport, localport); // never returns
		} catch (Exception e) {
			System.err.println(e);
			System.err.println("Usage: java SimpleProxyServer " + "<host> <remoteport> <localport>");
		}
	} 
	public static void runServer(String host, int remoteport, int localport) throws IOException {
			// Create a ServerSocket to listen for connections with
			@SuppressWarnings("resource")
			ServerSocket ss = new ServerSocket(localport);
			// Create buffers for client-to-server and server-to-client communication.
			// We make one final so it can be used in an anonymous class below.
			// Note the assumptions about the volume of traffic in each direction...
			final byte[] request = new byte[1024];
			byte[] reply = new byte[4096];
			// This is a server that never returns, so enter an infinite loop.
			while (true) {
				// Variables to hold the sockets to the client and to the server.
				Socket client = null, server = null;
				try {
					// Wait for a connection on the local port
					client = ss.accept();
					// Get client streams. Make them final so they can
					// be used in the anonymous thread below.
					final InputStream from_client = client.getInputStream();
					final OutputStream to_client = client.getOutputStream();
					// Make a connection to the real server
					// If we cannot connect to the server, send an error to the
					// client, disconnect, then continue waiting for another connection.
					try {
						server = new Socket(host, remoteport);
					} catch (IOException e) {
						PrintWriter out = new PrintWriter(new OutputStreamWriter(to_client));
						out.println("Proxy server cannot connect to " + host + ":" + remoteport + ":\n" + e);
						out.flush();
						client.close();
						continue;
					}
					// Get server streams.
					final InputStream from_server = server.getInputStream();
					final OutputStream to_server = server.getOutputStream();
					// Make a thread to read the client's requests and pass them to the
					// server. We have to use a separate thread because requests and
					// responses may be asynchronous.
					new Thread() {
						public void run() {
							int bytes_read;
							try {
								while ((bytes_read = from_client.read(request)) != -1) {
									to_server.write(request, 0, bytes_read);
									System.out
											.println(bytes_read + "to_server--->" + new String(request, "UTF-8") + "<---");
									to_server.flush();
								}
							} catch (IOException e) {
							}
							// the client closed the connection to us, so close our
							// connection to the server. This will also cause the
							// server-to-client loop in the main thread exit.
							try {
								to_server.close();
							} catch (IOException e) {
							}
						}
					}.start();
					// Meanwhile, in the main thread, read the server's responses
					// and pass them back to the client. This will be done in
					// parallel with the client-to-server request thread above.
					int bytes_read;
					try {
						while ((bytes_read = from_server.read(reply)) != -1) {
							try {
								Thread.sleep(1);
								System.out.println(bytes_read + "to_client--->" + new String(request, "UTF-8") + "<---");
							} catch (InterruptedException e) {
								e.printStackTrace();
							}
							to_client.write(reply, 0, bytes_read);
							to_client.flush();
						}
					} catch (IOException e) {
					}
					// The server closed its connection to us, so close our
					// connection to our client. This will make the other thread exit.
					to_client.close();
				} catch (IOException e) {
					System.err.println(e);
				}
				// Close the sockets no matter what happens each time through the loop.
				finally {
					try {
						if (server != null)
							server.close();
						if (client != null)
							client.close();
					} catch (IOException e) {
					}
				}
			} // while(true)
		}
	}
*/
