package rmi;

import java.rmi.Remote;
import java.rmi.registry.Registry;

public class Servidor {
    public static void main(String[] args) {
        try {
            // Es una interface para proveer los metodos de los objetos
            //Además se define el puerto
            Registry registro = java.rmi.registry.LocateRegistry.createRegistry(1234);
            //  para registrar un objeto remoto con el nombre "conversionInterface".
            registro.rebind("conversionInterface", (Remote) new RMI());
            System.out.println("Servidor iniciado...");
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}