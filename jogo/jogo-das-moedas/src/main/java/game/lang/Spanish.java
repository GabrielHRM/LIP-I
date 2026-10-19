package game.lang;
import game.ui.IRenderer;
public class Spanish extends Language {
    public Spanish(IRenderer renderer) { super(renderer); }
    public void printStartMessage(String deviceName) { renderer.showMessage("=== Recoge las monedas ($) - control: " + deviceName + " ==="); }
    public void printUnknownCommand() { renderer.showMessage("Comando desconocido."); }
    public void printWall() { renderer.showMessage("Pared! No puedes ir por ahi."); }
    public void printCoinCollected(int score) { renderer.showMessage("Moneda recogida! Puntos: " + score); }
    public void printAllCoinsCollected() { renderer.showMessage("Recogiste todas las monedas!"); }
    public void printFinalScore(int score) { renderer.showMessage("Puntuacion final: " + score); }
    public void printGameOver(int score) { renderer.showMessage("FIN DEL JUEGO - Puntos: " + score); }
    public void printScore(int score) { renderer.showMessage("Puntos: " + score); }
    public void printPrompt() { renderer.showPrompt("Comando (w/a/s/d, q para salir): "); }
}
