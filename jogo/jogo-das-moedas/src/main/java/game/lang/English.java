package game.lang;

import game.ui.IRenderer;

public class English extends Language {

    public English(IRenderer renderer) {
        super(renderer);
    }

    @Override
    public void printStartMessage(String deviceName) {
        renderer.showMessage("=== Collect the coins ($) - control: " + deviceName + " ===");
    }

    @Override
    public void printUnknownCommand() {
        renderer.showMessage("Unknown command.");
    }

    @Override
    public void printWall() {
        renderer.showMessage("Wall! You cannot go there.");
    }

    @Override
    public void printCoinCollected(int score) {
        renderer.showMessage("Coin collected! Score: " + score);
    }

    @Override
    public void printAllCoinsCollected() {
        renderer.showMessage("You collected all coins!");
    }

    @Override
    public void printFinalScore(int score) {
        renderer.showMessage("Final score: " + score);
    }

    @Override
    public void printGameOver(int score) {
        renderer.showMessage("GAME OVER - Score: " + score);
    }

    @Override
    public void printScore(int score) {
        renderer.showMessage("Score: " + score);
    }

    @Override
    public void printPrompt() {
        renderer.showPrompt("Command (w/a/s/d, q to quit): ");
    }
}
