package udpmulticast;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.Scanner;


public class Emisor {

    public static void main(String[] args) throws Exception {
        //Dirección para estar suscrito
        final InetAddress mcGroupDir = InetAddress.getByName(Constantes.DIRECCION);

        //Crear el socket
        final DatagramSocket udpSocket = new DatagramSocket();

        Scanner teclado = new Scanner(System.in);

        System.out.println("ENVIA MULTICAST DESDE " + udpSocket.getLocalSocketAddress());

        while(true) {
            String enviar = teclado.nextLine();

            byte[] buffer = enviar.getBytes();
            //Empaquetar mensaje para enviar                                  Grupo           Puerto
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length, mcGroupDir, Constantes.PUERTO);
            udpSocket.send(packet);

            if(enviar.equalsIgnoreCase(Constantes.FIN_MENSAJES)) break;
        }
        teclado.close();
        //Cerrar Socket
        udpSocket.close();
    }
}