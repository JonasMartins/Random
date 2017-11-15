package br.ufc.dc.sd.main;


import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.net.MalformedURLException;
import java.util.ArrayList;

public class Server extends UnicastRemoteObject implements ChatInterface {
    private static final long serialVersionUID = 1L;

    private ArrayList < ChatInterface > clientList;

    protected Server() throws RemoteException {
        clientList = new ArrayList < ChatInterface > ();
    }

    /* ESTRUTURA DE ARMAZENAMENTO DE TODOS OS CLIENTES CONECTADOS */
    public void addClients(ChatInterface chatinterface, String name) throws RemoteException {
        this.clientList.add(chatinterface);
    }
    /* BROADCAST A MENSSAGEM PARA TODOS OS CLIENTES */
    public synchronized void broadcastMessage(String clientname, String message) throws RemoteException {
        for (int i = 0; i < clientList.size(); i++) {
            clientList.get(i).sendMessageToClient(clientname.toUpperCase() + " : " + message);
        }
    }

    public synchronized void sendMessageToClient(String message) throws RemoteException {}

    public static void main(String[] arg) throws RemoteException, MalformedURLException {

        // Naming: https://docs.oracle.com/javase/8/docs/api/java/rmi/Naming.html
        System.out.println("Server is up and running!.");
        Naming.rebind("RMIServer", new Server());
    }

}