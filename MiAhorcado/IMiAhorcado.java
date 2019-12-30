import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IMiAhorcado extends Remote {
    
    /**
     * Método usado para jugar una letra.
     * @param letra         Letra del intento.
     * @param progreso      Progreso actual del cliente.
     * @return              Progreso tras probar con la letra.
     * @throws RemoteException
     */
    public String enviarLetra(char letra, String progreso) throws RemoteException;

    /**
     * Método usado para jugar una palabra.
     * @param palabra       Palabra del intento.
     * @return              true si la solución es correcta, false si no.
     * @throws RemoteException
     */
    public boolean enviarSolucion(String palabra) throws RemoteException;

    /**
     * Método usado para que el cliente obtenga el progreso inicial del juego.
     * @return  Progreso inicial del juego (un guión por caracter de la solución)
     * @throws RemoteException
     */
    public String progresoInicial() throws RemoteException;

    /**
     * Método usado para comprobar si un progreso es la victoria.
     * @param progreso      Progreso actual del cliente.
     * @return              true si el progreso coincide con la solución, false si no
     * @throws RemoteException
     */
    public boolean comprobarVictoria(String progreso) throws RemoteException;
}