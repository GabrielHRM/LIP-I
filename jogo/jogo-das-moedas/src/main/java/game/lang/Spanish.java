package game.lang;

import game.ui.IRenderer;

public class Spanish extends Language {

    public Spanish(IRenderer renderer) {
        super(renderer);
    }

    @Override
    public void printStartMessage(String deviceName) {
        renderer.showMessage("=== Recoge las monedas ($) - control: " + deviceName + " ===");
    }

    @Override
    public void printUnknownCommand() {
        renderer.showMessage("Comando desconocido.");
    }

    @Override
    public void printWall() {
        renderer.showMessage("Pared! No puedes ir por ahi.");
    }

    @Override
    public void printCoinCollected(int score) {
        renderer.showMessage("Moneda recogida! Puntos: " + score);
    }

    @Override
    public void printAllCoinsCollected() {
        renderer.showMessage("Recogiste todas las monedas!");
    }

    @Override
    public void printFinalScore(int score) {
        renderer.showMessage("Puntuacion final: " + score);
    }

    @Override
    public void printGameOver(int score) {
        renderer.showMessage("FIN DEL JUEGO - Puntos: " + score);
    }

    @Override
    public void printScore(int score) {
        renderer.showMessage("Puntos: " + score);
    }

    @Override
    public void printPrompt() {
        renderer.showPrompt("Comando (w/a/s/d, q para salir): ");
    }
}
