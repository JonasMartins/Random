
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
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

/**
 * A simple Swing-based client for the capitalization server.
 * It has a main frame window with a text field for entering
 * strings and a textarea to see the results of capitalizing
 * them.
 */
public class CapitalizeClient {

    private BufferedReader in;
    private PrintWriter out;
    private JFrame frame = new JFrame("Capitalize Client");
    private JTextField dataField = new JTextField(40);
    private JTextArea messageArea = new JTextArea(8, 60);

    /**
     * Constructs the client by laying out the GUI and registering a
     * listener with the textfield so that pressing Enter in the
     * listener sends the textfield contents to the server.
     */
    public CapitalizeClient() {

        // Layout GUI
        messageArea.setEditable(false);
        frame.getContentPane().add(dataField, "North");
        frame.getContentPane().add(new JScrollPane(messageArea), "Center");

        // Add Listeners
        dataField.addActionListener(new ActionListener() {
            /**
             * Responds to pressing the enter key in the textfield
             * by sending the contents of the text field to the
             * server and displaying the response from the server
             * in the text area.  If the response is "." we exit
             * the whole application, which closes all sockets,
             * streams and windows.
             */
            public void actionPerformed(ActionEvent e) {
                out.println(dataField.getText());
                   String response;
                try {
                    response = in.readLine();
                    if (response == null || response.equals("")) {
                          System.exit(0);
                      }
                } catch (IOException ex) {
                       response = "Error: " + ex;
                }
                messageArea.append(response + "\n");
                dataField.selectAll();
            }
        });
    }

    /**
     * Implements the connection logic by prompting the end user for
     * the server's IP address, connecting, setting up streams, and
     * consuming the welcome messages from the server.  The Capitalizer
     * protocol says that the server sends three lines of text to the
     * client immediately after establishing a connection.
     */
    public void connectToServer() throws IOException {

        // Get the server address from a dialog box.
        String serverAddress = JOptionPane.showInputDialog(
            frame,
            "Enter IP Address of the Server:",
            "Welcome to the Capitalization Program",
            JOptionPane.QUESTION_MESSAGE);

        // Make connection and initialize streams
        Socket socket = new Socket(serverAddress, 9898);
        in = new BufferedReader(
                new InputStreamReader(socket.getInputStream()));
        out = new PrintWriter(socket.getOutputStream(), true);

        // Consume the initial welcoming messages from the server
        for (int i = 0; i < 3; i++) {
            messageArea.append(in.readLine() + "\n");
        }
    }

    /**
     * Runs the client application.
     */
    public static void main(String[] args) throws Exception {
        CapitalizeClient client = new CapitalizeClient();
        client.frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        client.frame.pack();
        client.frame.setVisible(true);
        client.connectToServer();
    }
}