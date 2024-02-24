package udpmulticast;

import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;


public class Receptor {

    public static void main(String[] args) throws Exception {
        final InetAddress mcGroupDir = InetAddress.getByName(Constantes.DIRECCION);

        //Para la recepción
        final MulticastSocket mcSocket = new MulticastSocket(Constantes.PUERTO);

        //Unirse al grupo
        mcSocket.joinGroup(mcGroupDir);

        System.out.println("RECIBE MULTICAST EN " + mcSocket.getLocalSocketAddress());

        while(true) {
            byte[] buffer = new byte[Constantes.TALLA_BUFFER];

            //Paquete para recibir/recolectar informacion del mensaje
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length);

            //Bloquea el hilo, cuando llegue un paquete continua
            mcSocket.receive(packet);

            //Procesamos lo recibido
            String received = new String(packet.getData()).trim();
            System.out.println(
                    String.format("Mensaje=%s; desde=%s", received, packet.getSocketAddress())
            );

            //Mensaje igual a exit
            if(received.equalsIgnoreCase(Constantes.FIN_MENSAJES)) break;
        }

        //Abandonar grupo
        mcSocket.leaveGroup(mcGroupDir);
        mcSocket.close();
    }
}