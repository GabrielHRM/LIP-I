package game.language;

import game.ui.IRenderer;

public class Spanish implements ILanguage {
    public void printLevelStart(IRenderer renderer, String deviceName) { renderer.showMessage("=== Recoge las monedas ($) - control: " + deviceName + " ==="); }
    public void printUnknownCommand(IRenderer renderer) { renderer.showMessage("Comando desconocido."); }
    public void printWall(IRenderer renderer) { renderer.showMessage("¡Pared! No puedes ir allí."); }
    public void printAllCoinsCollected(IRenderer renderer) { renderer.showMessage("¡Has recogido todas las monedas!"); }
    public void printCoinCollected(IRenderer renderer, int score) { renderer.showMessage("¡Moneda recogida! Puntuación: " + score); }
    public void printScore(IRenderer renderer, int score) { renderer.showMessage("Puntuación: " + score); }
    public void printCommandPrompt(IRenderer renderer) { renderer.showMessage("Comando (w/a/s/d, q para salir): "); }
    public void printEarlyExit(IRenderer renderer, int score) { renderer.showMessage("Puntuación final: " + score); }
    public void printGameOver(IRenderer renderer, int score) { renderer.showMessage("FIN DEL JUEGO - Puntuación: " + score); }
}