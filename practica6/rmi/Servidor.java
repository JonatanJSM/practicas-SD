package rmi;

import java.rmi.Remote;
import java.rmi.registry.Registry;

public class Servidor {
    public static void main(String[] args) {
        try {
            Registry registro = java.rmi.registry.LocateRegistry.createRegistry(1234);
            registro.rebind("conversionInterface", (Remote) new RMI());
            System.out.println("Servidor iniciado...");
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}