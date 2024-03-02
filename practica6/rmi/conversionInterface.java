package rmi;
import java.rmi.*;


// Interface para las funciones que tendrá el server
public interface conversionInterface extends Remote {
    public float conversion(float numero, String unidadPrincipal, String unidadConversion) throws RemoteException;
}