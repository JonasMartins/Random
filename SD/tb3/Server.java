/**
 *   The implementation class Server implements the remote interface Hello,
 *   providing an implementation for the remote method sayHello. The method
 *   sayHello does not need to declare that it throws any exception because
 *   the method implementation itself does not throw RemoteException nor does it throw any other checked exceptions.
 */
import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class Server implements Hello {

    public Server() {}

    public String sayHello() {
        return "Hello, world!";
    }

    public static void main(String args[]) {

        try {

            /**
             * 
             * [Server description]
             * @return [description]
             * The main method of the server needs to create the remote object that provides the service. Additionally, 
             * the remote object must be exported to the Java RMI runtime so that it may receive incoming remote calls. This can be done as follows:
             * 
             */
            /**
             * The static method UnicastRemoteObject.exportObject exports the supplied remote object to receive 
             * incoming remote method invocations on an anonymous TCP port and returns the stub for the remote 
             * object to pass to clients. As a result of the exportObject call, the runtime may begin to listen 
             * on a new server socket or may use a shared server socket to accept incoming remote calls for the 
             * remote object. The returned stub implements the same set of remote interfaces as the remote object's 
             * class and contains the host name and port over which the remote object can be contacted.
             */
            Server obj = new Server();
            Hello stub = (Hello) UnicastRemoteObject.exportObject(obj, 0);
            
            /**
             *   For a caller (client, peer, or applet) to be able to invoke a method on a remote object, that caller must 
             *   first obtain a stub for the remote object. For bootstrapping, Java RMI provides a registry API for applications
             *   to bind a name to a remote object's stub and for clients to look up remote objects by name in order to obtain their stubs.
             * 
             *   A Java RMI registry is a simplified name service that allows clients to get a reference (a stub) to a remote object. In general, a registry is used (if at all) 
             *   only to locate the first remote object a client needs to use. Then, typically, that first object would in turn provide application-specific support for finding 
             *   other objects. For example, the reference can be obtained as a parameter to, or a return value from, another remote method call. For a discussion on how this works,
             *   please take a look at Applying the Factory Pattern to Java RMI.
             *   
             *   Once a remote object is registered on the server, callers can look up the object by name, obtain a remote object reference, and then invoke remote 
             *   methods on the object. The following code in the server obtains a stub for a registry on the local host and 
             *   default registry port and then uses the registry stub to bind the name "Hello" to the remote object's stub in that registry:
             */
            // Bind the remote object's stub in the registry
            Registry registry = LocateRegistry.getRegistry();
            registry.bind("Hello", stub);

            System.err.println("Server ready");
        } catch (Exception e) {
            System.err.println("Server exception: " + e.toString());
            e.printStackTrace();
        }
    }
}