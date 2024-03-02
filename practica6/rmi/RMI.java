package rmi;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

//Implementación de las funciones
public class RMI extends UnicastRemoteObject implements conversionInterface{
    public RMI() throws RemoteException{}

    public float conversion(float numero, String unidadPrincipal, String unidadConversion) throws RemoteException {
        Convertible fromConvertible = getConvertible(unidadPrincipal);
        switch (unidadConversion) {
            case "cm":
                return fromConvertible.toCm(numero);
            case "m":
                return fromConvertible.toM(numero);
            case "km":
                return fromConvertible.toKm(numero);
            default:
                throw new RemoteException("Unidad de destino no válida");
        }
    }

    private Convertible getConvertible(String unit) throws RemoteException {
        switch (unit) {
            case "pulgada":
                return new Pulgada();
            case "pie":
                return new Pie();
            case "yarda":
                return new Yarda();
            case "milla":
                return new Milla();
            default:
                throw new RemoteException("Unidad de origen no válida");
        }
    }
    
}
