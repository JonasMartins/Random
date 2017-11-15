package br.ufc.dc.sd.main;

import java.rmi.RemoteException;
import java.rmi.Remote;

public interface ChatInterface extends Remote {
    void addClients(ChatInterface ci,String name) throws RemoteException;
    void broadcastMessage(String name,String message) throws RemoteException;
    void sendMessageToClient(String message) throws RemoteException;
}

/**
 *  ===========================================================================
 *
 *  COMO RODAR? 
 *
 *  1. javac *.java 
 *  2. lançar o comando: rmiregistry (não retorna argumentos ) 
 *  3. em outro terminal: java Server
 *  4. em outros terminais: java Client e basta conectar-se, podem ser vários clientes 
 *
 *  ===========================================================================
 */