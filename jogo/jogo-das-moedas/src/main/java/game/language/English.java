package game.language;

import game.ui.IRenderer;

public class English implements ILanguage {
    public void printLevelStart(IRenderer renderer, String deviceName) { renderer.showMessage("=== Collect the coins ($) - control: " + deviceName + " ==="); }
    public void printUnknownCommand(IRenderer renderer) { renderer.showMessage("Unknown command."); }
    public void printWall(IRenderer renderer) { renderer.showMessage("Wall! You cannot go there."); }
    public void printAllCoinsCollected(IRenderer renderer) { renderer.showMessage("You collected all coins!"); }
    public void printCoinCollected(IRenderer renderer, int score) { renderer.showMessage("Coin collected! Score: " + score); }
    public void printScore(IRenderer renderer, int score) { renderer.showMessage("Score: " + score); }
    public void printCommandPrompt(IRenderer renderer) { renderer.showMessage("Command (w/a/s/d, q to exit): "); }
    public void printEarlyExit(IRenderer renderer, int score) { renderer.showMessage("Final score: " + score); }
    public void printGameOver(IRenderer renderer, int score) { renderer.showMessage("GAME OVER - Score: " + score); }
}