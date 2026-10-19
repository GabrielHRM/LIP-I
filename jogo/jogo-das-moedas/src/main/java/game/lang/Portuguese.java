package game.lang;

import game.ui.IRenderer;

public class Portuguese extends Language {

    public Portuguese(IRenderer renderer) {
        super(renderer);
    }

    @Override
    public void printStartMessage(String deviceName) {
        renderer.showMessage("=== Colete as moedas ($) - controle: " + deviceName + " ===");
    }

    @Override
    public void printUnknownCommand() {
        renderer.showMessage("Comando desconhecido.");
    }

    @Override
    public void printWall() {
        renderer.showMessage("Parede! Voce nao pode ir por ai.");
    }

    @Override
    public void printCoinCollected(int score) {
        renderer.showMessage("Moeda coletada! Pontos: " + score);
    }

    @Override
    public void printAllCoinsCollected() {
        renderer.showMessage("Voce coletou todas as moedas!");
    }

    @Override
    public void printFinalScore(int score) {
        renderer.showMessage("Pontuacao final: " + score);
    }

    @Override
    public void printGameOver(int score) {
        renderer.showMessage("FIM DE JOGO - Pontos: " + score);
    }

    @Override
    public void printScore(int score) {
        renderer.showMessage("Pontos: " + score);
    }

    @Override
    public void printPrompt() {
        renderer.showPrompt("Comando (w/a/s/d, q para sair): ");
    }
}
