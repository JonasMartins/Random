package br.ufc.dc.sd.main;

import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.net.MalformedURLException;
import java.util.Scanner;

public class Client extends UnicastRemoteObject implements ChatInterface, Runnable {
    private static final long serialVersionUID = 1L;
    private ChatInterface server;
    private String ClientName;
    boolean chkExit = true;

    protected Client(ChatInterface chatinterface, String clientname) throws RemoteException {
        this.server = chatinterface;
        this.ClientName = clientname;
        server.addClients(this, clientname);
    }
    
    /* APENAS IMPRIME A MENSSAGEM */
    public void sendMessageToClient(String message) throws RemoteException {
        System.out.println(message);
    }
    
    /* MÉTODO IMPLEMENTADO PELO SERVIDOR */
    public void broadcastMessage(String clientname, String message) throws RemoteException {}

    /* MÉTODO IMPLEMENTADO PELO SERVIDOR */
    public void addClients(ChatInterface ci, String name) throws RemoteException {
        return;
    };
    /* COMO O CLIENTE É UMA INTERFAÇE QUE IMPLEMENTA RUNNABLE, TAMBÉM É UMA THREAD, E 
    AO CONNECTAR COM O SERVIÇO, APENAS LANÇAMOS UMA NOVA THREAD COM AS DEFINIÇÕES DESSA CLASSE (LINHA 66)*/
    public void run() {
        System.out.println("Conectado corretamenete ao RMI Server");
        System.out.println("Obs : Digite EXIT para sair do serviço");
        System.out.println("Voçê está online ao chat\n");
        @SuppressWarnings("resource")
        Scanner scanner = new Scanner(System.in);
        String message = "-";
        while (chkExit) {
            message = scanner.nextLine();
            if (message.equals("EXIT")) {
                chkExit = false;
            } else {
                try {
                    server.broadcastMessage(ClientName, message);
                } catch (RemoteException e) {
                    e.printStackTrace();
                }
            }
        }
        System.out.println("\nVoçê saiu corretamente do RMI Chat\nObrigado pelo uso...");
        System.exit(0);
    }

    public static void main(String[] args) throws MalformedURLException, RemoteException, NotBoundException {
        @SuppressWarnings("resource")
        Scanner scanner = new Scanner(System.in);
        String clientName = "";
        System.out.println("\n~~ Bem vindo ao RMI Chat ~~\n");
        System.out.print("Entre com o seu nome : ");
        clientName = scanner.nextLine();
        System.out.println("\nConnecting To RMI Server...\n");
        ChatInterface chatinterface = (ChatInterface) Naming.lookup("rmi://localhost/RMIServer");
        new Thread(new Client(chatinterface, clientName)).start();
    }

}