package game.language;

import game.ui.IRenderer;

public class Portuguese implements ILanguage {
    public void printLevelStart(IRenderer renderer, String deviceName) { renderer.showMessage("=== Colete as moedas ($) - controle: " + deviceName + " ==="); }
    public void printUnknownCommand(IRenderer renderer) { renderer.showMessage("Comando desconhecido."); }
    public void printWall(IRenderer renderer) { renderer.showMessage("Parede! Você não pode ir por ali."); }
    public void printAllCoinsCollected(IRenderer renderer) { renderer.showMessage("Você coletou todas as moedas!"); }
    public void printCoinCollected(IRenderer renderer, int score) { renderer.showMessage("Moeda coletada! Pontuação: " + score); }
    public void printScore(IRenderer renderer, int score) { renderer.showMessage("Pontuação: " + score); }
    public void printCommandPrompt(IRenderer renderer) { renderer.showMessage("Comando (w/a/s/d, q para sair): "); }
    public void printEarlyExit(IRenderer renderer, int score) { renderer.showMessage("Pontuação final: " + score); }
    public void printGameOver(IRenderer renderer, int score) { renderer.showMessage("FIM DE JOGO - Pontuação: " + score); }
}