package game;
import java.util.List;
import game.enums.CommandsEnum;
import game.inputs.IInputs;
import game.ui.IRenderer;
import game.lang.Language;
import game.world.Grid;
import game.world.Progress;
import game.world.gobjects.Coin;
import game.world.gobjects.Player;

public class Level {
    private final Grid grid;
    private final Player player;
    private final Progress progress;
    private final List<Coin> coins;
    private final IInputs input;
    private final IRenderer renderer;
    private final Language language;
    private boolean running = true;

    public Level(Grid grid, Player player, Progress progress, List<Coin> coins, IInputs input, IRenderer renderer, Language language) {
        this.grid = grid;
        this.player = player;
        this.progress = progress;
        this.coins = coins;
        this.input = input;
        this.renderer = renderer;
        this.language = language;
    }

    public boolean run() {
        renderer.clear();
        language.printStartMessage(input.getDeviceName());
        renderer.draw(grid, player, progress, coins);
        language.printScore(progress.getScore());
        language.printPrompt();

        while (running) {
            runTurn();
        }
        return allCoinsCollected();
    }

    public void runTurn() {
        CommandsEnum command = input.waitCommand();
        if (command == CommandsEnum.EXIT) { running = false; return; }
        if (command == CommandsEnum.NONE) { language.printUnknownCommand(); return; }

        int destinationX = player.getX() + command.getDeltaX();
        int destinationY = player.getY() + command.getDeltaY();

        if (grid.isWall(destinationX, destinationY)) {
            language.printWall();
            return;
        }

        player.moveTo(destinationX, destinationY);
        collectCoinAtCurrentPosition();
        renderer.draw(grid, player, progress, coins);
        language.printScore(progress.getScore());
        language.printPrompt();

        if (allCoinsCollected()) {
            language.printAllCoinsCollected();
            running = false;
        }
    }

    private void collectCoinAtCurrentPosition() {
        for (Coin coin : coins) {
            if (!coin.isCollected() && coin.isAt(player.getX(), player.getY())) {
                coin.collect();
                progress.addScore(coin.getValue());
                language.printCoinCollected(progress.getScore());
            }
        }
    }

    private boolean allCoinsCollected() {
        for (Coin coin : coins) {
            if (!coin.isCollected()) return false;
        }
        return true;
    }
}
