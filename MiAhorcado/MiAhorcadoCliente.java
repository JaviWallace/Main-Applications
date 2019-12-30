import java.rmi.Naming;
import java.util.Scanner;

public class MiAhorcadoCliente {

    private static void mostrarAhorcado(int fallos) {
        switch(fallos) {
            case 0:
                System.out.println();
                System.out.println(" ------");
                System.out.println(" |/   |");
                System.out.println(" |");
                System.out.println(" |");
                System.out.println(" |");
                System.out.println(" |");
                System.out.println("---");
                System.out.println();
                break;
            case 1:
                System.out.println();
                System.out.println(" ------");
                System.out.println(" |/   |");
                System.out.println(" |    O");
                System.out.println(" |");
                System.out.println(" |");
                System.out.println(" |");
                System.out.println("---");
                System.out.println();
                break;
            case 2:
                System.out.println();
                System.out.println(" ------");
                System.out.println(" |/   |");
                System.out.println(" |    O");
                System.out.println(" |    |");
                System.out.println(" |");
                System.out.println(" |");
                System.out.println("---");
                System.out.println();
                break;
            case 3:
                System.out.println();
                System.out.println(" ------");
                System.out.println(" |/   |");
                System.out.println(" |    O");
                System.out.println(" |   /|");
                System.out.println(" |");
                System.out.println(" |");
                System.out.println("---");
                System.out.println();
                break;
            case 4:
                System.out.println();
                System.out.println(" ------");
                System.out.println(" |/   |");
                System.out.println(" |    O");
                System.out.println(" |   /|\\");
                System.out.println(" |");
                System.out.println(" |");
                System.out.println("---");
                System.out.println();
                break;
            case 5:
                System.out.println();
                System.out.println(" ------");
                System.out.println(" |/   |");
                System.out.println(" |    O");
                System.out.println(" |   /|\\");
                System.out.println(" |   /");
                System.out.println(" |");
                System.out.println("---");
                System.out.println();
                break;
            default:
                System.out.println();
                System.out.println(" ------");
                System.out.println(" |/   |");
                System.out.println(" |    O");
                System.out.println(" |   /|\\");
                System.out.println(" |   / \\");
                System.out.println(" |");
                System.out.println("---");
                System.out.println();
                break;
        }
    }

    private static String intros = "";
    private static void limpiarPantalla() {
        System.out.println(intros);
    }

    public static void main(String[] args) throws Exception {               // habría que capturar las excepciones

        IMiAhorcado ORemoto = (IMiAhorcado)Naming.lookup("MiAhorcado");     // se le hace casting porque lookup devuelve un objeto remoto
        Scanner sc = new Scanner(System.in);

        for(int i = 0; i < 50; ++i)
            intros += "\n";

        // Obtenemos el progreso inicial
        String progreso = ORemoto.progresoInicial();

        boolean victoria = false;
        int fallos = 0;
        do {
            
            // Mostramos el ahorcado y el progreso en cada turno
            limpiarPantalla();
            mostrarAhorcado(fallos);
            System.out.println("\t" + progreso + "\n");

            System.out.print("Introduzca una letra o palabra: ");
            String entrada = sc.nextLine();
            if(entrada.length() == 1) {     // si se introduce solo un carácter
                String progresoAux = ORemoto.enviarLetra(entrada.charAt(0), progreso);
                if(progreso.equals(progresoAux))
                    fallos++;       // si no se modifica el progreso, ha sido un fallo
                else {
                    progreso = progresoAux;
                    victoria = ORemoto.comprobarVictoria(progreso);     // cada vez que acertamos, comprobamos si hemos ganado
                }
            } else {                        // si se introduce una palabra
                if(ORemoto.enviarSolucion(entrada))
                    victoria = true;
                else
                    fallos = 100;       // si fallamos al probra con una palabra, perdemos instantáneamente
            }

        } while(!victoria && fallos < 6);       // el juego acaba cuando acumulamos 6 fallos o cuando ganamos

        limpiarPantalla();
        mostrarAhorcado(fallos);
        System.out.println("\t" + progreso + "\n");

        if(victoria)
            System.out.println("¡Has ganado!");
        else
            System.out.println("GAME OVER ;(");

        sc.close();
    }
}