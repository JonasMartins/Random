// nice example http://cs.lmu.edu/~ray/notes/javanetexamples/
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

import javax.swing.JOptionPane;

import java.io.File;
import java.io.InputStream;
import java.io.FileNotFoundException;

import java.util.Set;
import java.util.ArrayList;
import java.util.Properties;

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
public class ProxyServer {

    /**
     * Application method to run the server runs in an infinite loop
     * listening on port 9898.  When a connection is requested, it
     * spawns a new thread to do the servicing and immediately returns
     * to listening.  The server keeps a unique client number for each
     * client that connects just to show interesting logging
     * messages.  It is certainly not necessary to do this.
     */
    public static void main(String[] args) throws Exception {
        System.out.println("The Server is running.");
        int clientNumber = 0;
        ServerSocket listener = new ServerSocket(9898);
        try {
            while (true) {
                new Server(listener.accept(), clientNumber++).start();
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
    private static class Server extends Thread {
        private Socket socket;
        private int clientNumber;
        private Properties prop = null;
        private ArrayList<String> choices;

        public Server(Socket socket, int clientNumber) {
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
                out.println("Hello, you are client #" + (clientNumber+1) + ".");
                out.println("All options of actions...");
                out.println("1> Read");
                out.println("2> Write");
                out.println("3> Delete");
                out.println("---------------------------");

                // Get messages from the client, line by line; return them
                // capitalized
                while (true) {
                    String input = in.readLine();
                    if (input == null || input.equals(".")) {
                        break;
                    }
                    //out.println(input.toUpperCase());
                    byte aux = safeParse(input);
                    String choice;
                    switch (aux){
                        case 1:
                            //out.println(aux+10);
                            choice = choose();
                            out.println(choice);
                            break;
                        case 2:
                            //out.println(aux+10);
                            choice = choose();
                            out.println(choice);
                            break;
                        case 3:
                            //out.println(aux+10);
                            choice = choose();
                            out.println(choice);
                            break;
                        default:
                            out.println("Invalid entry option");
                    }
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

        private byte safeParse(String entry){
            byte entryParsed = 0;
            try {
                entryParsed = Byte.parseByte(entry);
            }catch(NumberFormatException e){
                e.printStackTrace();
            }
            return entryParsed;
        }
        /* return all keys from properties as set */
        public Set<Object> getAllKeys(Properties prop){
            Set<Object> keys = prop.keySet();
            return keys;
        }

        public String getPropertyValue(String key){
            return this.prop.getProperty(key);
        }

        /**
         *
         * Show options based on files.properties file keeping track of possible
         * deleted files, even when a file was deleted from user, the propertie file
         * is used to show this options.
         *
         */
        public String choose(){
            
            choices = new ArrayList<String>();
            InputStream is = null;
            try {
                this.prop = new Properties();
                is = this.getClass().getResourceAsStream("/files.properties");
                prop.load(is);
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }

            Set<Object> keys = getAllKeys(prop);
            for(Object k:keys){
                String key = (String)k;
                choices.add(key);
                //System.out.println(key+": "+mpc.getPropertyValue(key));
            }
            String[] options = new String[choices.size()];
            int i=0;
            for(String s: choices){
                options[i] = s;
                i++;
            }

            String input = (String) JOptionPane.showInputDialog(null, "Choose now...",
                    "The Choice of a Lifetime", JOptionPane.QUESTION_MESSAGE, null,
                    options, // Array of choices
                    options[1]); // Initial choice
        
            return input;
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
