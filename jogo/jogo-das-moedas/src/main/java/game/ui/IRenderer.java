package game.ui;
import java.util.List;
import game.world.Grid;
import game.world.Progress;
import game.world.gobjects.Coin;
import game.world.gobjects.Player;
public interface IRenderer {
    void clear();
    void showMessage(String message);
    void showPrompt(String message);
    void draw(Grid grid, Player player, Progress progress, List<Coin> coins);
}
