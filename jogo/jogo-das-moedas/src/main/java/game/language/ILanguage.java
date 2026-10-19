package game.language;

import game.ui.IRenderer;

public interface ILanguage {
    void printLevelStart(IRenderer renderer, String deviceName);
    void printUnknownCommand(IRenderer renderer);
    void printWall(IRenderer renderer);
    void printAllCoinsCollected(IRenderer renderer);
    void printCoinCollected(IRenderer renderer, int score);
    void printScore(IRenderer renderer, int score);
    void printCommandPrompt(IRenderer renderer);
    void printEarlyExit(IRenderer renderer, int score);
    void printGameOver(IRenderer renderer, int score);
}