package game.lang;
import game.ui.IRenderer;
public class English extends Language {
    public English(IRenderer renderer) { super(renderer); }
    public void printStartMessage(String deviceName) { renderer.showMessage("=== Collect the coins ($) - control: " + deviceName + " ==="); }
    public void printUnknownCommand() { renderer.showMessage("Unknown command."); }
    public void printWall() { renderer.showMessage("Wall! You cannot go there."); }
    public void printCoinCollected(int score) { renderer.showMessage("Coin collected! Score: " + score); }
    public void printAllCoinsCollected() { renderer.showMessage("You collected all coins!"); }
    public void printFinalScore(int score) { renderer.showMessage("Final score: " + score); }
    public void printGameOver(int score) { renderer.showMessage("GAME OVER - Score: " + score); }
    public void printScore(int score) { renderer.showMessage("Score: " + score); }
    public void printPrompt() { renderer.showPrompt("Command (w/a/s/d, q to quit): "); }
}
