import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class MiAhorcadoServidor extends UnicastRemoteObject implements IMiAhorcado {

    private String solucion = "Electroencefalografista";
    private String progreso_inicial = solucion.replaceAll(".", "-");

    public MiAhorcadoServidor() throws RemoteException {        // el constructor siempre hay que declararlo y que lance RemoteException
        solucion = solucion.toLowerCase();
    }

    public String enviarLetra(char letra, String progreso) throws RemoteException {
        System.out.println("Comprobando letra " + letra);
        char[] progresoAux = progreso.toCharArray();
        int indice = -1,
            encontrada = solucion.indexOf(("" + letra).toLowerCase(), indice+1);
        while(encontrada >= 0) {
            progresoAux[encontrada] = letra;
            indice = encontrada;
            encontrada = solucion.indexOf(("" + letra).toLowerCase(), indice+1);
        }
        progreso = String.valueOf(progresoAux);
        return progreso;
    }

    public boolean enviarSolucion(String palabra) throws RemoteException {
        System.out.println("Comprobando palabra " + palabra);
        return solucion.equals(palabra.toLowerCase());          // solucion == palabra COMPARA PUNTEROS
    }

    public String progresoInicial() throws RemoteException {
        return progreso_inicial;
    }

    public boolean comprobarVictoria(String progreso) throws RemoteException {
        return solucion.equals(progreso);
    }

    

    public static void main(String[] args) throws Exception {   // deberíamos capturar la excepción realmente

        IMiAhorcado ORemoto = new MiAhorcadoServidor();
        // también serviría: MiAhorcadoServidor ORemoto = new MiAhorcadoServidor();

        Naming.rebind("MiAhorcado", ORemoto);     // se traduce a "rmi://127.0.0.1:1099/MiAhorcado"
        // bind reserva un puerto de la máquina para el objeto
        // con rebind, si el puerto estaba ya en uso, se cerrará y se volverá a abrir
        // útil para testear la aplicación, para no tener que cerrar manualmente el puerto cada vez que la ejecutemos

        System.out.println("Servidor MiAhorcado preparado.");
    }
}