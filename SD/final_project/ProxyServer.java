import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.BufferedOutputStream;
import java.io.PrintWriter;
import java.io.File;
import java.io.InputStream;
import java.io.FileNotFoundException;

import java.net.Socket;
import java.net.ServerSocket;

import java.util.Set;
import java.util.ArrayList;
import java.util.Properties;

import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.Files;
import java.nio.file.StandardOpenOption;
import java.nio.file.NoSuchFileException;
import java.nio.file.DirectoryNotEmptyException;

import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JButton;

import java.awt.Font;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

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
        private JFrame frame = new JFrame("Edit Your File");
        private JTextArea messageArea = new JTextArea(20, 60);
        private JButton doneEdit = new JButton("Done");

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
                    byte aux = safeParse(input);
                    String choice;
                    switch (aux){
                        case 1:
                            String line;
                            choice = choose();
                            out.println("...");
                            JOptionPane.showMessageDialog(null,readFromFile(getFileUrl(choice)));
                            out.println("Reading:" + getFileUrl(choice));
                            break;
                        case 2:
                            choice = choose();
                            out.println("...");
                            writeToFile(getFileUrl(choice));
                            out.println("Editing: " + getFileUrl(choice));
                            break;
                        case 3:
                            choice = choose();
                            out.println("...");
                            if (deleteFile(choice) == 3){
                                JOptionPane.showMessageDialog(null,"File deleted successfully.");
                            } else {
                                JOptionPane.showMessageDialog(null,"Something went Wrong.");
                            }
                            out.println("Deleting:" + getFileUrl(choice));
                            
                            break;
                        default:
                            System.out.println("Invalid entry option");
                    }
                }
                out.close();
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
            
            choices = getCurrentStringFiles();
            
            String[] options = new String[choices.size()];
            int i=0;
            for(String s: choices){
                options[i] = s;
                i++;
            }

            String input = (String) JOptionPane.showInputDialog(null, "Choose from avaliable files",
                    "Select One", JOptionPane.QUESTION_MESSAGE, null,
                    options, // Array of choices
                    options[1]); // Initial choice
        
            return input;
        }
        /* Recieve the file name and Returns file's full path */
        public String getFileUrl(String file){
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
            return prop.getProperty(file)+file;   
        }
        /**
         *
         * Mapping current files from files.properties
         *
         */
        public ArrayList<String> getCurrentStringFiles(){
            ArrayList<String> aux = new ArrayList<String>();
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
                aux.add(key);
                //System.out.println(key+": "+mpc.getPropertyValue(key));
            }
            return aux;
        }
        /**
         *
         * Recebe o path completo do arquivo que foi selecionado
         * pelo JOptionpane, lê esse arquivo e devolve para run() 
         * onde será impresso no frame 
         *
         */
        public String readFromFile(String path){            
            String content = "."; 
            try {
                content = new String(Files.readAllBytes(Paths.get(path)));
            }catch(IOException e) {
                log("Couldn't read file content, what's going on?");
            }
            return content;
        }
        /**
         *
         * Receber o path do arquivo, abrir um pop up para a edição com um botão ok
         * e retornar a salvar o arquivo com o novo texto.
         */
        
        public void writeToFile(String path){
            String currentContent = readFromFile(path);

            messageArea.setEditable(true);
            messageArea.setFont(new Font("Monaco", Font.BOLD, 13));
            messageArea.append(currentContent);
            frame.getContentPane().add(doneEdit, "South");
            frame.getContentPane().add(new JScrollPane(messageArea), "Center");
            frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
            frame.pack();
            frame.setVisible(true);
        
            doneEdit.addActionListener(new ActionListener(){
              public void actionPerformed(ActionEvent e){
                if(saveFileContent(path,messageArea.getText())){
                    frame.dispose(); // when done, edit frame is closed
                } else {
                    System.out.println("Something Wrong when try to edit the file.");
                }
              }
            });            

        }
        /**
         *
         * Gravando a string content no arquivo file
         *
         */
        public boolean saveFileContent(String file, String content){
            //System.out.println(file);
            //System.out.println(content);
            boolean flag = false;
            Path path = Paths.get(file);
            byte data[] = content.getBytes();

            //System.out.println(data);
            
            try (OutputStream out = new BufferedOutputStream(Files.newOutputStream(path))) {
                out.write(data, 0, data.length);
                flag = true;
            } catch (IOException x) {
              System.err.println(x);
            }
            return flag;
        }
        /**
         *
         * Recebe nome do arquivo e remove tanto de properties
         * quanto remove o arquivo., tudo ok: flag = 3;
         *
         */
        public int deleteFile(String file){
            int flag = 0;
            /* DELETE FILE FROM DISK */
            try {
                Files.delete(Paths.get(getFileUrl(file)));
                flag += 1;
            } catch (NoSuchFileException x) {
                System.err.format("%s: no such" + " file or directory%n", getFileUrl(file));
            } catch (DirectoryNotEmptyException x) {
                System.err.format("%s not empty%n", getFileUrl(file));
            } catch (IOException x) {
                // File permission problems are caught here.
                System.err.println(x);
            }

            /* DELETE FILE FROM PROPERTIES */
            InputStream is = null;
            try {
                this.prop = new Properties();
                is = this.getClass().getResourceAsStream("/files.properties");
                prop.load(is);
                flag += 1;
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
            prop.remove(file); // attempt to remove
            
            try (OutputStream out = Files.newOutputStream(Paths.get("files.properties"),StandardOpenOption.TRUNCATE_EXISTING)){
                prop.store(out, null);
                flag += 1;
            }catch (IOException e) {
                e.printStackTrace();
            }
            return flag;
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
