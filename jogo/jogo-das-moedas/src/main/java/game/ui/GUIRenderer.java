package game.ui;

import java.util.List;
import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import java.awt.Font;

import game.world.Grid;
import game.world.Progress;
import game.world.gobjects.Coin;
import game.world.gobjects.Player;

public class GUIRenderer implements IRenderer {

    private final JFrame frame;
    private final JTextArea textArea;

    public GUIRenderer() {
        frame = new JFrame("Game Output");
        frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        
        textArea = new JTextArea(20, 40);
        textArea.setFont(new Font("Monospaced", Font.PLAIN, 16));
        textArea.setEditable(false);
        
        frame.add(new JScrollPane(textArea));
        frame.pack();
        frame.setVisible(true);
    }

    @Override
    public void clear() {
        textArea.setText("");
    }

    @Override
    public void draw(Grid grid, Player player, Progress progress, List<Coin> coins) {
        textArea.append("\n");
        for (int y = 0; y < grid.getHeight(); y++) {
            StringBuilder line = new StringBuilder();
            for (int x = 0; x < grid.getWidth(); x++) {
                line.append(symbolAt(grid, player, coins, x, y));
            }
            textArea.append(line.toString() + "\n");
        }
    }

    private char symbolAt(Grid grid, Player player, List<Coin> coins, int x, int y) {
        if (player.isAt(x, y)) {
            return player.getSymbol();
        }
        for (Coin coin : coins) {
            if (!coin.isCollected() && coin.isAt(x, y)) {
                return coin.getSymbol();
            }
        }
        if (grid.isWall(x, y)) {
            return '#';
        }
        return ' ';
    }

    @Override
    public void showMessage(String message) {
        textArea.append(message + "\n");
    }
    
    @Override
    public void showPrompt(String message) {
        textArea.append(message);
    }
}
