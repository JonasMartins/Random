
/*
 run server before
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
*/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;


/**
 * Trivial client for the date server.
 */
public class Client {

    /**
     * Runs the client as an application.  First it displays a dialog
     * box asking for the IP address or hostname of a host running
     * the date server, then connects to it and displays the date that
     * it serves.
     */
    public static void main(String[] args) throws IOException {
        String serverAddress = JOptionPane.showInputDialog(
            "Enter IP Address of a machine that is\n" +
            "running the date service on port 9090:");
        Socket s = new Socket(serverAddress, 9090);
        BufferedReader input =
            new BufferedReader(new InputStreamReader(s.getInputStream()));
        String answer = input.readLine();
        System.out.println(answer);
        System.exit(0);
    }
}