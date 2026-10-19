package game.lang;

import game.ui.IRenderer;

public abstract class Language {

    protected final IRenderer renderer;

    public Language(IRenderer renderer) {
        this.renderer = renderer;
    }

    public abstract void printStartMessage(String deviceName);

    public abstract void printUnknownCommand();

    public abstract void printWall();

    public abstract void printCoinCollected(int score);

    public abstract void printAllCoinsCollected();

    public abstract void printFinalScore(int score);

    public abstract void printGameOver(int score);

    public abstract void printScore(int score);

    public abstract void printPrompt();
}
