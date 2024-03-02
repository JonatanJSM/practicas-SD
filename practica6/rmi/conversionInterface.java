package rmi;
import java.rmi.*;

public interface conversionInterface extends Remote {
    public float conversion(float numero, String unidadPrincipal, String unidadConversion) throws RemoteException;
}