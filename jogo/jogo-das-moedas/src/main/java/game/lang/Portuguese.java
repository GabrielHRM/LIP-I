package game.lang;
import game.ui.IRenderer;
public class Portuguese extends Language {
    public Portuguese(IRenderer renderer) { super(renderer); }
    public void printStartMessage(String deviceName) { renderer.showMessage("=== Colete as moedas ($) - controle: " + deviceName + " ==="); }
    public void printUnknownCommand() { renderer.showMessage("Comando desconhecido."); }
    public void printWall() { renderer.showMessage("Parede! Voce nao pode ir por ai."); }
    public void printCoinCollected(int score) { renderer.showMessage("Moeda coletada! Pontos: " + score); }
    public void printAllCoinsCollected() { renderer.showMessage("Voce coletou todas as moedas!"); }
    public void printFinalScore(int score) { renderer.showMessage("Pontuacao final: " + score); }
    public void printGameOver(int score) { renderer.showMessage("FIM DE JOGO - Pontos: " + score); }
    public void printScore(int score) { renderer.showMessage("Pontos: " + score); }
    public void printPrompt() { renderer.showPrompt("Comando (w/a/s/d, q para sair): "); }
}
