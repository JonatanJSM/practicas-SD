package rmi;
import java.rmi.Naming;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) {
         try (Scanner scanner = new Scanner(System.in)) {
            try {
                //Para guardar referencia del objeto remoto
                conversionInterface obj = (conversionInterface) Naming.lookup("rmi://localhost:1234/conversionInterface");
                while (true) {
                    System.out.print("Ingrese el valor: ");
                    float value = scanner.nextFloat();
                        
                    System.out.print("Ingrese la unidad de origen (pulgada, pie, yarda, milla): ");
                    String fromUnit = scanner.next();
                    
                    System.out.print("Ingrese la unidad de destino (cm, m, km): ");
                    String toUnit = scanner.next();

                    System.out.println("Resultado: " + obj.conversion(value, fromUnit, toUnit));
                }
                
            } catch (Exception e) {
                System.out.println("Error: " + e.getMessage());
            }
        }
    }
}
